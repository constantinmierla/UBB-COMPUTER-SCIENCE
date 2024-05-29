#include "teste.h"
#include "ui.h"
#include "service.h"
#include "repository.h"

using namespace std;

int main() {
    allTests();
    MasinaRepo repo;
    ServiceMasina service(repo);
    UI ui(service);
    ui.run();
    return 0;
}