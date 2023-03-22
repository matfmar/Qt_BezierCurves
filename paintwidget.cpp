#include "paintwidget.h"

PaintWidget::PaintWidget(MMarzec::TBezierPoint* l, bool iS, bool si, QColor color, QString nf, QWidget *parent) : pointList(l), ifSaved(iS), saveImage(si), realColor(color), newfilename(nf), QWidget(parent)
{
    setFixedSize(800,800);
    statusL = new QLabel(this);
    statusL -> setText("STATUS");
    statusL -> setAlignment(Qt::AlignBottom | Qt::AlignRight);
    statusL -> move(400,0);
    setMouseTracking(true);

    int bezierPointCount = MMarzec::countBezierPoints(pointList);
    curve = new MMarzec::TBezierCurve(pointList, bezierPointCount);

    MMarzec::TBezierPoint* runner(pointList);
    TPaintedPoint* newEl(nullptr);
    while (runner != nullptr) {
        newEl = new TPaintedPoint;
        newEl -> next = paintedPointList;
        newEl -> point = new QPointF(runner-> x, runner -> y);
        newEl -> color = Qt::blue;
        newEl -> bpoint = runner;
        paintedPointList = newEl;
        runner = runner -> next;
    }
    newWeight = new double(0.0);
}

void PaintWidget::paintCurveBezier(QPainter* p) {

    if (ifSaved)
        MMarzec::createFile();
    QPointF* startingPoint = new QPointF(pointList -> x, pointList -> y);
    QPointF* endingPoint = new QPointF(0.0, 0.0);
    MMarzec::TMyPoint tempPoint(0.0, 0.0);
    for (double u = 0.0; u <= 1.0; u += 0.005) {
        tempPoint = curve -> produceNextPoint(u);
        endingPoint -> setX(tempPoint.x);
        endingPoint -> setY(tempPoint.y);
        p -> drawLine(*startingPoint, *endingPoint);
        startingPoint -> setX(endingPoint -> x());
        startingPoint -> setY(endingPoint -> y());
        if (ifSaved)
            MMarzec::saveCurve(startingPoint -> x(), endingPoint -> y());
    }
    delete startingPoint;
    delete endingPoint;

}

void PaintWidget::paintPoint(TPaintedPoint* point, QPainter* p, QPen* pen) {

    pen -> setColor(point -> color);
    p -> setPen(*pen);
    p -> drawPoint(*(point -> point));
    point -> color = Qt::blue;

}

void PaintWidget::paintEvent(QPaintEvent *event) {

    QPainter p(this);
    QPen pen;

    pen.setColor(realColor);
    pen.setWidth(10);
    p.setPen(pen);

    paintCurveBezier(&p);

    pen.setColor(Qt::black);
    pen.setWidth(10);
    p.setPen(pen);

    TPaintedPoint* runner(paintedPointList);
    while (runner != nullptr) {
        paintPoint(runner, &p, &pen);
        runner = runner -> next;
    }

    if (saveImage) {
        QImage image(QSize(this -> width(), this -> height()), QImage::Format_ARGB32);
        QPainter p2(&image);
        QPen pen2;

        pen2.setColor(realColor);
        pen2.setWidth(10);
        p2.setPen(pen2);

        paintCurveBezier(&p2);

        pen2.setColor(Qt::black);
        pen2.setWidth(10);
        p2.setPen(pen2);

        TPaintedPoint* runner(paintedPointList);
        while (runner != nullptr) {
            paintPoint(runner, &p2, &pen2);
            runner = runner -> next;
        }
        if (newfilename == "")
            newfilename = "obraz.png";
        image.save(newfilename);

   }
}

bool wpoblizu(double x, double dana) {
    if ((x > (dana - 6)) && (x < (dana + 6)))
        return true;
}

bool PaintWidget::ifOnThePoint(double x, double y) {
    TPaintedPoint* runner(paintedPointList);
    while (runner != nullptr) {
        if (wpoblizu(x, runner->point->x()) && wpoblizu(y, runner -> point -> y())) {
            repaintedPoint = runner;
            return true;
        }
        runner = runner -> next;
    }
    return false;
}

void PaintWidget::changeThePointColor() {
    repaintedPoint -> color = Qt::red;
    requiresRepainting = true;
}

void PaintWidget::leftMouseActionOnceMore(double x, double y) {

    AddPoint* changeWindow = new AddPoint(newWeight);
    changeWindow -> exec();

    TPaintedPoint* changedPoint = clickedLeftOncePoint;
    clickedLeftOncePoint = nullptr;
    changedPoint -> point -> setX(x);
    changedPoint -> point -> setY(y);
    changedPoint -> bpoint -> x = x;
    changedPoint -> bpoint -> y = y;
    changedPoint -> bpoint -> w = *newWeight;

    int newCount = MMarzec::countBezierPoints(pointList);
    MMarzec::TCurve* newCurve = new MMarzec::TBezierCurve(pointList, newCount);
    MMarzec::TCurve* doDeleteCv = curve;
    curve = newCurve;
    delete doDeleteCv;

    this -> repaint();

}

void PaintWidget::leftMouseAction(double x, double y) {

    TPaintedPoint* runner(paintedPointList),* givenPoint(nullptr);
    while (runner != nullptr) {
        if (wpoblizu(x, runner->point->x()) && wpoblizu(y, runner -> point -> y())) {
            givenPoint = runner;
            break;
        }
        runner = runner -> next;
    }
    clickedLeftOncePoint = givenPoint;

}

void PaintWidget::rightMouseAction(double x, double y) {

    AddPoint* addPoint = new AddPoint(newWeight);
    addPoint -> exec();

    MMarzec::TBezierPoint* newEl(nullptr);
    newEl = new MMarzec::TBezierPoint(x, y, *newWeight);
    newEl -> next = pointList;
    pointList = newEl;

    TPaintedPoint* el(paintedPointList),* newEl2(nullptr);
    while (el -> next != nullptr)
        el = el -> next;

    newEl2 = new TPaintedPoint();
    el -> next = newEl2;
    newEl2 -> next = nullptr;
    newEl2 -> point = new QPointF(x, y);
    newEl2 -> color = Qt::blue;
    newEl2 -> bpoint = newEl;

    int newCount = MMarzec::countBezierPoints(pointList);
    MMarzec::TCurve* newCurve = new MMarzec::TBezierCurve(pointList, newCount);
    MMarzec::TCurve* toBeDeleted = curve;
    curve = newCurve;
    delete toBeDeleted;

    this -> repaint();
    *newWeight = 0.0;

}

void PaintWidget::middleMouseAction(double x, double y) {
    TPaintedPoint* runner(paintedPointList),* changedPoint(nullptr);
    while (runner != nullptr) {
        if (wpoblizu(x, runner->point->x()) && wpoblizu(y, runner -> point -> y())) {
            changedPoint = runner;
            break;
        }
        runner = runner -> next;
    }

    AddPoint* changeWindow = new AddPoint(newWeight);
    changeWindow -> exec();

    changedPoint -> bpoint -> w = *newWeight;

    int newCount = MMarzec::countBezierPoints(pointList);
    MMarzec::TCurve* newCurve = new MMarzec::TBezierCurve(pointList, newCount);
    MMarzec::TCurve* toBeDeleted = curve;
    curve = newCurve;
    delete toBeDeleted;

    this -> repaint();

}

void PaintWidget::destroyNode(TPaintedPoint *givenPoint) {

    MMarzec::TBezierPoint* givenBezierPoint = givenPoint -> bpoint;

    TPaintedPoint* runner(paintedPointList),* prevPoint(nullptr);
    if (runner == givenPoint) {
        paintedPointList = givenPoint -> next;
        runner = paintedPointList;
        delete givenPoint;
    }
    else {
        while (runner != nullptr) {
            if (runner == givenPoint) {
                prevPoint -> next = runner -> next;
                delete runner;
                break;
            }
            prevPoint = runner;
            runner = runner -> next;
        }
    }

    MMarzec::TBezierPoint* bprunner(pointList),* bpprevPoint(nullptr);
    if (bprunner == givenBezierPoint) {
        pointList = givenBezierPoint -> next;
        bprunner = pointList;
        delete givenBezierPoint;
    }
    else {
        while (bprunner != nullptr) {
            if (bprunner == givenBezierPoint) {
                bpprevPoint -> next = bprunner -> next;
                delete bprunner;
                break;
            }
            bpprevPoint = bprunner;
            bprunner = bprunner -> next;
        }
    }

    int newCount = MMarzec::countBezierPoints(pointList);
    MMarzec::TCurve* newCurve = new MMarzec::TBezierCurve(pointList, newCount);
    MMarzec::TCurve* toBeDeleted = curve;
    curve = newCurve;
    delete toBeDeleted;

    this -> repaint();

}

void PaintWidget::destroyMouseAction(double x, double y) {
    TPaintedPoint* runner(paintedPointList),* givenPoint(nullptr);
    while (runner != nullptr) {
        if (wpoblizu(x, runner->point->x()) && wpoblizu(y, runner -> point -> y())) {
            givenPoint = runner;
            break;
        }
        runner = runner -> next;
    }
    int pointNumber = MMarzec::countBezierPoints(pointList);
    if (pointNumber < 4) {
        QMessageBox::warning(this, tr("Błąd!"), tr("Brak możliwości usunięcia węzła!!!"), QMessageBox::Ok);
        return;
    }
    PaintWidget::destroyNode(givenPoint);
}

void PaintWidget::mousePressEvent(QMouseEvent *event) {
    int xCord = event -> pos().x();
    int yCord = event -> pos().y();

    if (ifOnThePoint(xCord, yCord)) {
        clickedLeftOncePoint = nullptr;
        if (event -> button() == Qt::LeftButton)
            leftMouseAction(xCord, yCord);
        else if (event -> button() == Qt::MiddleButton)
            middleMouseAction(xCord, yCord);
    }
    else {
        if (event -> button() == Qt::RightButton) {
            rightMouseAction(xCord, yCord);
            clickedLeftOncePoint = nullptr;
        }
        else if (event -> button() == Qt::LeftButton) {
            if (clickedLeftOncePoint != nullptr) {
                leftMouseActionOnceMore(xCord, yCord);
            }
        }
    }

}

void PaintWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    int xCord = event -> pos().x();
    int yCord = event -> pos().y();
    if (ifOnThePoint(xCord, yCord)) {
        if (event -> button() == Qt::LeftButton)
            destroyMouseAction(xCord, yCord);
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event) {
    int xCord = event -> pos().x();
    int yCord = event -> pos().y();

    if (ifOnThePoint(xCord, yCord)) {
        changeThePointColor();
        this -> repaint();
    }
    else {
        if (requiresRepainting) {
            repaintedPoint -> color = Qt::blue;
            repaintedPoint = nullptr;
            this -> repaint();
            requiresRepainting = false;
        }
    }

    QString text = "\t\t\t\t\tPozycja X: " + QString::number(xCord) + "; Pozycja Y: " + QString::number(yCord);
    statusL -> setText(text);
    statusL -> adjustSize();
}

PaintWidget::~PaintWidget() {
    TPaintedPoint* pointRunner(paintedPointList);
    TPaintedPoint* PPtoDelete(nullptr);
    while (pointRunner != nullptr) {
        PPtoDelete = pointRunner;
        pointRunner = pointRunner -> next;
        delete PPtoDelete;
    }
    if (newWeight != nullptr)
        delete newWeight;
    MMarzec::TBezierPoint* runner(pointList);
    MMarzec::TBezierPoint* toDelete(nullptr);
    while (runner != nullptr) {
        toDelete = runner;
        runner = runner -> next;
        delete toDelete;
        toDelete = nullptr;
    }
    if (curve != nullptr)
        delete curve;
}
