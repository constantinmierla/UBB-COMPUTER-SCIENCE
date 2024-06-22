#include "tractor.h"
#include "gui.h"
#include "serv.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo r{ "input.txt" };
    Validator v{ r };
    Service serv{ r, v };
    GUI g{ serv };
    g.show();
    return a.exec();
}
