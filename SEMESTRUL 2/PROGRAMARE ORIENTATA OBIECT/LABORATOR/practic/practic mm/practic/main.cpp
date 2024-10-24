#include "practic.h"
#include <QtWidgets/QApplication>
#include"service.h"
#include"repo.h"
#include"teste.h"
#include"gui.h"
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    teste();
    string file = "melodie.txt";
    Repo repo{ file };
    Validator val;
    Service service{ repo,val };
    GUI gui{ service };
    gui.show();
    return a.exec();
}
