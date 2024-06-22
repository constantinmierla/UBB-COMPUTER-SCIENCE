#include "GUI.h"
#include <QtWidgets/QApplication>
#include "ui.h"
#include "serv.h"
#include "repo.h"
#include "domain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RepoFile repo("file.txt");
    Service serv(repo);
    gui w(serv);
    w.show();
    return a.exec();
}
