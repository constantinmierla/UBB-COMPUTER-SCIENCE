#include "practic.h"
#include <QtWidgets/QApplication>
#include"service.h"
#include"gui.h"
#include<teste.h>
int main(int argc, char* argv[])
{
    test();
    QApplication a(argc, argv);
    Repo repo{ "produse.txt" };
    Validator val{ repo };
    Service service{ repo,val };
    GUI gui{ service };
    gui.show();
    return a.exec();
}