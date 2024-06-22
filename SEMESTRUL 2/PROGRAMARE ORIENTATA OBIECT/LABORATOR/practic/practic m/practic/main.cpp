#include "practic.h"
#include<QtWidgets/QApplication>
#include"service.h"
#include"gui.h"
#include"teste.h"
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    test();
    Repo repo{ "melodie.txt" };
    Validator val;
    Service service{ repo,val };
    GUI gui{ service };
    gui.show();
    return a.exec();
}