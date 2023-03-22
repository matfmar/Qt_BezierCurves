#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Program do rysowania krzywych Beziera"));
    setFixedSize(876, 511);

    connect(ui->drawButton,SIGNAL(clicked()), this, SLOT(showPaintWidget()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(loadPoint()));
    connect(ui->openPB, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(about()));

    for (int i=0; i<MAX_CURVES; ++i) {
        bpTab[i] = nullptr;
        flag[i] = false;
     }

}

void MainWindow::showPaintWidget() {
    if (pointCount < 3) {
        QMessageBox::warning(this, tr("Uwaga!"), tr("Za mało punktów!"), QMessageBox::Ok);
        return;
    }
    bool ifSaved(false);
    if (ui -> savingCB -> checkState() == Qt::Checked) {
        ifSaved = true;
        MMarzec::createFile();
    }
    bool saveImage(false);
    QString newfilename = "";
    if (ui -> saveImageCB -> checkState() == Qt::Checked) {
        saveImage = true;
        newfilename = QFileDialog::getSaveFileName(this, tr("Pokaż miejsce zapisu pliku"), tr("*.png"));
    }
    else
        ifSaved = false;
    int index = ui -> comboBox -> currentIndex();
    QColor realColor;
    switch (index) {
        case 0: realColor = Qt::red; break;
        case 1: realColor = Qt::green; break;
        case 2: realColor = Qt::blue; break;
        case 3: realColor = Qt::black; break;
        default: realColor = Qt::black;
    }

    paintWidget = new PaintWidget(bpTab[curveCount], ifSaved, saveImage, realColor, newfilename);
    flag[curveCount] = false;
    paintWidget -> update();
    paintWidget -> show();
    paintWidget -> update();
    ui -> resultL -> setText(tr("Krzywa skasowana. Dodajesz nową."));
    ui -> result2L -> setText(tr("Aktualna krzywa ma zero punktów."));
    curveCount++;
    if (curveCount == MAX_CURVES) {
        ui -> addButton -> setEnabled(false);
        ui -> drawButton -> setEnabled(false);
        QMessageBox::warning(this, tr("Koniec rysowania"), tr("Koniec rysowania"), QMessageBox::Ok);
    }
    ui -> xLE -> clear();
    ui -> yLE -> clear();
    ui -> wLE -> clear();
    newfilename = "";
    pointCount = 0;

}

bool MainWindow::checkIfPointAdded(double x, double y) {
    MMarzec::TBezierPoint* runner(bpTab[curveCount]);
    while (runner != nullptr) {
        if (runner -> x == x && runner -> y == y)
            return true;
        runner = runner -> next;
    }
    return false;
}

void MainWindow::loadPoint() {
    double x = ui -> xLE -> text().toDouble();
    if (x <= 0 || x >= 800) {
        ui -> resultL -> setText(tr("Zły punkt! Wartość ma być > 0 i < 800"));
        return;
    }
    double y = ui -> yLE -> text().toDouble();
    if (y <= 0 || y >= 800) {
        ui -> resultL -> setText(tr("Zły punkt! Wartość ma być > 0 i < 800"));
        return;
    }
    double w = ui -> wLE -> text().toDouble();
    if (w <= 0 || w >= 1000) {
        ui -> resultL -> setText(tr("Zły punkt! Wartość ma być > 0 i < 1000"));
        return;
    }
    if (checkIfPointAdded(x, y)) {
        ui -> resultL -> setText(tr("Ten punkt już był. Dodaj inny."));
        return;
    }
    MMarzec::TBezierPoint* newEl = new MMarzec::TBezierPoint(x, y, w);
    flag[curveCount] = true;
    newEl -> next = bpTab[curveCount];
    bpTab[curveCount] = newEl;
    pointCount++;
    ui -> resultL -> setText(tr("Punkt dodany."));
    ui -> result2L -> setText("W aktualnej krzywej masz " + QString::number(pointCount) + " punkt/y.");

}

void MainWindow::openFile() {
    QString newfilename = QFileDialog::getOpenFileName(this, tr("Otwórz plik"), tr("Pliki tekstowe (*.txt);;Wszystkie pliki (*.*)"));
    if (newfilename.isEmpty())
        return;
    QFile file(newfilename);
    file.open(QFile::ReadOnly | QFile::Text);
    if (!file.isOpen()) {
        QMessageBox::warning(this, tr("Krytyczny problem"), tr("Błąd otwarcia pliku!"), QMessageBox::Ok);
        return;
    }
    ui -> textEdit -> clear();
    QTextStream readFile(&file);
    ui -> textEdit -> setText(readFile.readAll());
    file.close();
}

void MainWindow::about() {
    QDialog* dialog = new QDialog;
    dialog -> setFixedSize(400, 400);
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    QString instrukcja = "Prawy przycisk tworzy nowy punkt.\nPodwójne kliknięcie usuwa punkt.\nŚrodkowy przycisk zmienia wagę\nPojedyncze kliknięcie lewym przyciskiem wybiera punkt,\na następnie ponowne kliknięcie w innym miejscu go\nprzesuwa\n\nZ pozdrowieniami,\nautor - Mateusz Marzec.";
    QLabel* label = new QLabel(instrukcja, dialog);
    layout -> addWidget(label);
    label -> setAlignment(Qt::AlignCenter);
    dialog -> setLayout(layout);
    dialog -> exec();
}

MainWindow::~MainWindow()
{
    for (int i=0; i<MAX_CURVES; ++i) {
        if (flag[i]) {
            MMarzec::TBezierPoint* runner(bpTab[i]);
            MMarzec::TBezierPoint* toDelete(nullptr);
            while (runner != nullptr) {
                toDelete = runner;
                runner = runner -> next;
                delete toDelete;
                toDelete = nullptr;
            }
        }
    }
    delete ui;
}

