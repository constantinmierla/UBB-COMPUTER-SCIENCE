#include "practic.h"
#include <QtWidgets/QApplication>
#include"teste.h"
#include"service.h"
#include"gui.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    teste();
    Repo repo{ "tractoare.txt" };
    Validator val{ repo };
    Service service{ repo,val };
    GUI gui{ service };
    gui.show();
    return a.exec();
}