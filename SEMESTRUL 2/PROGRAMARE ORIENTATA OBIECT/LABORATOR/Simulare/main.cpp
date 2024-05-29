#include "Simulare.h"
#include <QtWidgets/QApplication>
#include "gui.h"
#include "qwidget.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Repo r("input.txt");
    Service s(r);
    
    gui g(s);
    Simulare w;
    g.show();

    return a.exec();
}
