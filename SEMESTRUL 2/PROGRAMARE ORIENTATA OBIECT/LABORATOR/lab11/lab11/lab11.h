#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab11.h"

class lab11 : public QMainWindow
{
    Q_OBJECT

public:
    lab11(QWidget *parent = nullptr);
    ~lab11();

private:
    Ui::lab11Class ui;
};
