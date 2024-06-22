/********************************************************************************
** Form generated from reading UI file 'tractor.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACTOR_H
#define UI_TRACTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tractorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *tractorClass)
    {
        if (tractorClass->objectName().isEmpty())
            tractorClass->setObjectName("tractorClass");
        tractorClass->resize(600, 400);
        menuBar = new QMenuBar(tractorClass);
        menuBar->setObjectName("menuBar");
        tractorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(tractorClass);
        mainToolBar->setObjectName("mainToolBar");
        tractorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(tractorClass);
        centralWidget->setObjectName("centralWidget");
        tractorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(tractorClass);
        statusBar->setObjectName("statusBar");
        tractorClass->setStatusBar(statusBar);

        retranslateUi(tractorClass);

        QMetaObject::connectSlotsByName(tractorClass);
    } // setupUi

    void retranslateUi(QMainWindow *tractorClass)
    {
        tractorClass->setWindowTitle(QCoreApplication::translate("tractorClass", "tractor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tractorClass: public Ui_tractorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACTOR_H
