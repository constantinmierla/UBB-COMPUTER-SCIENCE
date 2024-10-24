/********************************************************************************
** Form generated from reading UI file 'practic.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRACTIC_H
#define UI_PRACTIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_practicClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *practicClass)
    {
        if (practicClass->objectName().isEmpty())
            practicClass->setObjectName("practicClass");
        practicClass->resize(600, 400);
        menuBar = new QMenuBar(practicClass);
        menuBar->setObjectName("menuBar");
        practicClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(practicClass);
        mainToolBar->setObjectName("mainToolBar");
        practicClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(practicClass);
        centralWidget->setObjectName("centralWidget");
        practicClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(practicClass);
        statusBar->setObjectName("statusBar");
        practicClass->setStatusBar(statusBar);

        retranslateUi(practicClass);

        QMetaObject::connectSlotsByName(practicClass);
    } // setupUi

    void retranslateUi(QMainWindow *practicClass)
    {
        practicClass->setWindowTitle(QCoreApplication::translate("practicClass", "practic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class practicClass: public Ui_practicClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRACTIC_H
