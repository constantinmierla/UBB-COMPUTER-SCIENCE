//
// Created by david on 3/6/24.
// modified by costi on 3/24/24
//

/*
 * 8. Magazin electronice

        Creati o aplicatie care permite gestiunea stocului de produse intr-un magazin de electronice.
    Fiecare produs are un identificator unic, tip (laptop, frigider, televizor,etc), producator, model,
    pret, cantitate.
    Aplicatia permite:
     a) Adaugarea de noi produse. Daca produsul este deja in stoc trebuie actualizat cantitatea
     b) Actualizare produse (modificare pret sau cantitate)
     c) Stergere produs
     d) Vizualizare produse din stoc, ordonat dupa pret, cantitate (crescator/descrescator)
     e) Vizualizare lista de produse filtrate dupa un criteriu (producator, pret, cantitate)
 */
#include <stdlib.h>
#include "./Domain/product.h"
#include "./Repository/repository.h"
#include "./UI/ui.h"
#include "./Tests/test.h"


int main() {
    testAll();



    Repository repo;
    Validator vali;
    Service service;
    Console console;
    service.repository = &repo;
    service.validator = &vali;
    console.service = &service;

    initRepository(&repo, 11);
    setUp(&service);

    run(console);

    free(repo.products);
}