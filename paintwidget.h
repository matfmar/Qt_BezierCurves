#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPointF>
#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <QPen>
#include "core.h"
#include <QColor>
#include <QMessageBox>
#include <QImage>
#include <QFileDialog>

#include "addpoint.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(MMarzec::TBezierPoint* l, bool iS, bool si, QColor color, QString nf, QWidget *parent = nullptr);
    ~PaintWidget();

    double* newWeight = nullptr;


signals:

private:

    MMarzec::TBezierPoint* pointList = nullptr;

    class TPaintedPoint {
        public:
            TPaintedPoint() {}
            QPointF* point = nullptr;
            MMarzec::TBezierPoint* bpoint = nullptr;
            TPaintedPoint* next = nullptr;
            QColor color = Qt::black;
            ~TPaintedPoint() {
                if (point != nullptr) {
                    delete point;
                    point = nullptr;
                }
            }
    };
    bool ifSaved;
    bool saveImage;
    QString newfilename;
    QColor realColor;

    TPaintedPoint* paintedPointList = nullptr;
    MMarzec::TCurve* curve = nullptr;

    bool requiresRepainting = false;
    TPaintedPoint* repaintedPoint = nullptr;
    void paintPoint(TPaintedPoint* point, QPainter* p, QPen* pen);
    void changeThePointColor();
    void paintCurveBezier(QPainter* p);
    bool ifOnThePoint(double x, double y);
    void leftMouseAction(double x, double y);
    void leftMouseActionOnceMore(double x, double y);
    void rightMouseAction(double x, double y);
    void middleMouseAction(double x, double y);
    void destroyMouseAction(double x, double y);
    void destroyNode(TPaintedPoint* givenNode);
    QLabel* statusL;
    TPaintedPoint* clickedLeftOncePoint = nullptr;
    double weightToChange = 0.0;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

};

#endif // PAINTWIDGET_H
