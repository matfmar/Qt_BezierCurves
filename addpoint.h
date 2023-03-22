#ifndef ADDPOINT_H
#define ADDPOINT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class AddPoint : public QDialog
{
    Q_OBJECT
public:
    explicit AddPoint(double* iw, QWidget *parent = nullptr);
    QLabel* addPointL;

signals:

private slots:
    void submit();

private:
    QVBoxLayout* addPointLayout;
    QLineEdit* addPointLE;
    QPushButton* addPointB;
    double* inputWeight;
    double realWeight;
};

#endif // ADDPOINT_H
