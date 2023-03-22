#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include "paintwidget.h"
#include "core.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

static const int MAX_CURVES = 5;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadPoint();
    void showPaintWidget();
    void openFile();
    void about();

private:
    bool flag[MAX_CURVES];
    MMarzec::TBezierPoint* bpTab[MAX_CURVES];
    Ui::MainWindow *ui;
    PaintWidget* paintWidget;
    int pointCount = 0;
    int curveCount = 0;
    bool checkIfPointAdded(double x, double y);

};
#endif // MAINWINDOW_H
