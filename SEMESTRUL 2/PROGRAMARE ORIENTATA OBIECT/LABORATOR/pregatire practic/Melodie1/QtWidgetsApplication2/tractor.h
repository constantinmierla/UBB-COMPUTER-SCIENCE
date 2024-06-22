#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_tractor.h"

class tractor : public QMainWindow
{
    Q_OBJECT

public:
    tractor(QWidget *parent = nullptr);
    ~tractor();

private:
    Ui::tractorClass ui;
};
