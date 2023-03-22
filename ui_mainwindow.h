/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QCheckBox *savingCB;
    QCheckBox *saveImageCB;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *xLE;
    QLabel *label_2;
    QLineEdit *yLE;
    QLabel *label_3;
    QLineEdit *wLE;
    QLabel *resultL;
    QLabel *result2L;
    QPushButton *addButton;
    QPushButton *drawButton;
    QPushButton *closeButton;
    QPushButton *openPB;
    QComboBox *comboBox;
    QLabel *label_4;
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(876, 511);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 851, 491));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        savingCB = new QCheckBox(widget);
        savingCB->setObjectName(QString::fromUtf8("savingCB"));

        gridLayout_2->addWidget(savingCB, 7, 0, 1, 1);

        saveImageCB = new QCheckBox(widget);
        saveImageCB->setObjectName(QString::fromUtf8("saveImageCB"));

        gridLayout_2->addWidget(saveImageCB, 6, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        xLE = new QLineEdit(widget);
        xLE->setObjectName(QString::fromUtf8("xLE"));

        gridLayout->addWidget(xLE, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        yLE = new QLineEdit(widget);
        yLE->setObjectName(QString::fromUtf8("yLE"));

        gridLayout->addWidget(yLE, 1, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        wLE = new QLineEdit(widget);
        wLE->setObjectName(QString::fromUtf8("wLE"));

        gridLayout->addWidget(wLE, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 2, 1);

        resultL = new QLabel(widget);
        resultL->setObjectName(QString::fromUtf8("resultL"));

        gridLayout_2->addWidget(resultL, 3, 0, 1, 1);

        result2L = new QLabel(widget);
        result2L->setObjectName(QString::fromUtf8("result2L"));

        gridLayout_2->addWidget(result2L, 4, 0, 1, 1);

        addButton = new QPushButton(widget);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout_2->addWidget(addButton, 2, 0, 1, 1);

        drawButton = new QPushButton(widget);
        drawButton->setObjectName(QString::fromUtf8("drawButton"));

        gridLayout_2->addWidget(drawButton, 8, 0, 1, 1);

        closeButton = new QPushButton(widget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        gridLayout_2->addWidget(closeButton, 10, 0, 1, 1);

        openPB = new QPushButton(widget);
        openPB->setObjectName(QString::fromUtf8("openPB"));

        gridLayout_2->addWidget(openPB, 9, 0, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_2->addWidget(comboBox, 5, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 3, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 1, 1, 1);

        textEdit = new QTextEdit(widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        textEdit->setReadOnly(true);

        gridLayout_3->addWidget(textEdit, 1, 1, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_3->addWidget(pushButton, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        savingCB->setText(QApplication::translate("MainWindow", "Zapisz wsp\303\263\305\202rz\304\231dne krzywej", nullptr));
        saveImageCB->setText(QApplication::translate("MainWindow", "Zapisz obraz krzywej", nullptr));
        label->setText(QApplication::translate("MainWindow", "Wsp. X:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Wsp. y:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Waga:", nullptr));
        resultL->setText(QApplication::translate("MainWindow", "Jako\305\233\304\207 dodanego punktu", nullptr));
        result2L->setText(QApplication::translate("MainWindow", "Dodajesz now\304\205 krzyw\304\205", nullptr));
        addButton->setText(QApplication::translate("MainWindow", "Dodaj Punkt", nullptr));
        drawButton->setText(QApplication::translate("MainWindow", "Rysuj", nullptr));
        closeButton->setText(QApplication::translate("MainWindow", "Zamknij", nullptr));
        openPB->setText(QApplication::translate("MainWindow", "Odczytaj wsp\303\263\305\202rz\304\231dne z pliku", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "czerwony", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "zielony", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "niebieski", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "czarny", nullptr));

        label_4->setText(QApplication::translate("MainWindow", "Wsp\303\263\305\202rz\304\231dne krzywej odczytane z pliku:", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "INSTRUKCJA OBS\305\201UGI PROGRAMU + O PROGRAMIE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
