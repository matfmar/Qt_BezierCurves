#include "addpoint.h"

AddPoint::AddPoint(double* iw, QWidget *parent) : inputWeight(iw), QDialog(parent)
{
    addPointLayout = new QVBoxLayout(this);
    addPointL = new QLabel(tr("Podaj wagę:"), this);
    addPointLE = new QLineEdit(this);
    addPointB = new QPushButton("Ok", this);
    addPointLayout -> addWidget(addPointL);
    addPointLayout -> addWidget(addPointLE);
    addPointLayout -> addWidget(addPointB);
    setLayout(addPointLayout);

    connect(addPointB, SIGNAL(clicked()), this, SLOT(submit()));

}

void AddPoint::submit() {
    realWeight = addPointLE -> text().toDouble();
    *inputWeight = realWeight;
    close();
}
