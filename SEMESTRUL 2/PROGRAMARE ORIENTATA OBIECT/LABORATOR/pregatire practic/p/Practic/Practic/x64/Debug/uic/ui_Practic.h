/********************************************************************************
** Form generated from reading UI file 'Practic.ui'
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

class Ui_PracticClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PracticClass)
    {
        if (PracticClass->objectName().isEmpty())
            PracticClass->setObjectName("PracticClass");
        PracticClass->resize(600, 400);
        menuBar = new QMenuBar(PracticClass);
        menuBar->setObjectName("menuBar");
        PracticClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PracticClass);
        mainToolBar->setObjectName("mainToolBar");
        PracticClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PracticClass);
        centralWidget->setObjectName("centralWidget");
        PracticClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PracticClass);
        statusBar->setObjectName("statusBar");
        PracticClass->setStatusBar(statusBar);

        retranslateUi(PracticClass);

        QMetaObject::connectSlotsByName(PracticClass);
    } // setupUi

    void retranslateUi(QMainWindow *PracticClass)
    {
        PracticClass->setWindowTitle(QCoreApplication::translate("PracticClass", "Practic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PracticClass: public Ui_PracticClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRACTIC_H
