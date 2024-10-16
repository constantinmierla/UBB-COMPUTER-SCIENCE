//
// Created by Costi on 29-Mar-24.
//
/*
    9 Închiriere mașini

    Creați o aplicație care permite:
    · gestiunea unei liste de mașini. Mașina: nrInmatriculare, producător, model, tip
    · adăugare, ștergere, modificare și afișare mașini
    · căutare mașina
    · filtrare mașini după: producător, tip
    · sortare mașini după: nrInmatriculare, tip, producator + model
 */
#include "ui.h"
#include "service.h"
#include "repository.h"
#include "tests.h"
int main() {

    MasinaRepo repo;
    MasinaService srv{repo};
    UI ui{srv};
    test_total();
    ui.run();
    return 0;
}
