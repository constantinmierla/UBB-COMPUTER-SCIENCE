//
// Created by Costi on 12-Mar-24.
//
#include "tests.h"
#include "domain.h"
#include "repository.h"
#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void testValideazaOferta() {
    int idRau = -1;
    char* tip = "laptop";
    int pretRau = -1;
    char* producator = "lenovo";
    char* model = "g5";

    Oferta* o = creeazaOferta(tip, producator, model, 15, -1, 10);
    assert(valideazaOferta(o) == -1);

    Oferta* o1 = creeazaOferta("", producator, model, 15, -1, 10);
    assert(valideazaOferta(o1) == -1);

    Oferta* o2 = creeazaOferta(tip, "", "", 15, 1, 10);
    assert(valideazaOferta(o2) == -1);

    Oferta* o3 = creeazaOferta(tip, producator, model, pretRau, 1, 10);
    assert(valideazaOferta(o3) == -1);

    Oferta* o4 = creeazaOferta(tip, producator, model, 15, idRau, 10);
    assert(valideazaOferta(o4) == -1);

    Oferta* o5 = creeazaOferta(tip, producator, model, 15, 1, -1);
    assert(valideazaOferta(o5) == -1);

    Oferta* o6 = creeazaOferta("", producator, model, 15, 1, 10);
    assert(valideazaOferta(o6) == -1);

    Oferta* o7 = creeazaOferta(tip, producator, "", 15, 1, 10);
    assert(valideazaOferta(o7) == -1);

    Oferta* o8 = creeazaOferta(tip, producator, model, 15, 1, 10);
    assert(valideazaOferta(o8) == 1);
    destroyOferta(o);
    destroyOferta(o1);
    destroyOferta(o2);
    destroyOferta(o3);
    destroyOferta(o4);
    destroyOferta(o5);
    destroyOferta(o6);
    destroyOferta(o7);
    destroyOferta(o8);
}

void testCopyOferta() {
    Oferta* o = creeazaOferta("laptop", "Lenovo", "ThinkPad", 1500, 1, 5);
    Oferta* copy = copyOferta(o);

    // Verificăm că adresa de memorie a obiectului copiat este diferită de adresa obiectului original
    assert(copy != o);

    // Verificăm că obiectul copiat are aceleași valori ca obiectul original
    assert(strcmp(copy->tip, o->tip) == 0);
    assert(strcmp(copy->model, o->model) == 0);
    assert(strcmp(copy->producer, o->producer) == 0);
    assert(copy->pret == o->pret);
    assert(copy->stoc == o->stoc);

    assert(getId(copy) == getId(o));
    assert(getPret(copy) == getPret(o));
    setPret(o, 2000);
    assert(getPret(o) == 2000);
    destroyOferta(o);
    destroyOferta(copy);
}

void testAddEntitate() {
    // Cream o structură de date Offerte
    Offerte* f = creeazaOfferte((DestroyFn)destroyOferta, (CopyFn) copyOferta);

    // Adăugăm oferte noi
    Oferta* o1 = creeazaOferta("laptop", "Lenovo", "ThinkPad", 1500, 1, 10);
    addEntitate(f, o1);

    // Verificăm că dimensiunea a crescut și că oferta a fost adăugată corect
    assert(sizeList(f) == 1);
    assert(getElement(f, 0) == o1);

    // Adăugăm o a doua ofertă
    Oferta* o2 = creeazaOferta("telefon", "Samsung", "Galaxy S20", 1200, 2, 5);
    addEntitate(f, o2);

    // Verificăm că dimensiunea a crescut și că a doua ofertă a fost adăugată corect
    assert(sizeList(f) == 2);
    assert(getElement(f, 1) == o2);

    // Eliberăm memoria
    destroyOfferte(f);
}

void testAsiguraCapacitate() {
    // Cream o structură de date Offerte cu o capacitate inițială mică
    Offerte* f = creeazaOfferte((DestroyFn)destroyOferta, (CopyFn) copyOferta);

    // Adăugăm oferte până când capacitatea inițială este depășită
    for (int i = 0; i < 5; i++) {
        Oferta* o = creeazaOferta("laptop", "Lenovo", "ThinkPad", 1500, i + 1, 10);
        addEntitate(f, o);
    }

    // Verificăm că dimensiunea și capacitatea au crescut corect
    assert(sizeList(f) == 5);
    assert(f->capacitate == 8); // Capacitatea ar trebui să fie dublul valorii inițiale (2)

    // Eliberăm memoria
    destroyOfferte(f);
}

void testDeleteEntitate() {
    // Cream o structură de date Offerte cu oferte adăugate
    Offerte* f = creeazaOfferte((DestroyFn)destroyOferta, (CopyFn) copyOferta);
    Oferta* o1 = creeazaOferta("laptop", "Lenovo", "ThinkPad", 1500, 1, 10);
    Oferta* o2 = creeazaOferta("telefon", "Samsung", "Galaxy S20", 1200, 2, 5);
    addEntitate(f, o1);
    addEntitate(f, o2);

    // Ștergem prima ofertă
    int result1 = deleteEntitate(f, 1);
    // Verificăm că prima ofertă a fost ștearsă corect
    assert(result1 == 0); // Întoarce 1 dacă ștergerea a fost cu succes
    assert(sizeList(f) == 1); // Dimensiunea trebuie să fie acum 1

    // Ștergem o ofertă care nu există
    int result2 = deleteEntitate(f, 3);
    // Verificăm că ștergerea unei oferte inexistente returnează 0
    assert(result2 == 1); // Întoarce 0 dacă oferta nu a fost găsită

    // Eliberăm memoria
    destroyOfferte(f);
}
void testUpdateOferta()
{
    Offerte* f = creeazaOfferte((DestroyFn)destroyOferta, (CopyFn) copyOferta);

    // Adăugare entitate pentru testare
    addEntitate(f, creeazaOferta("laptop", "Lenovo", "ThinkPad", 1500, 10,2));

    // Testare actualizare entitate existentă
    Oferta* oferta_actualizata = creeazaOferta("laptop", "Dell", "XPS 13", 1800, 8,1);
    assert(updateOferta(f, oferta_actualizata) == -1);

    assert(updateOferta(f, creeazaOferta("laptop", "Dell", "XPS 13", 1800, 10,2)) == 0);

    destroyOfferte(f);
    destroyOferta(oferta_actualizata);
}

void testCauta()
{
    Offerte* f = creeazaOfferte((DestroyFn)destroyOferta, (CopyFn) copyOferta);

    // Testare căutare într-o listă goală
    assert(cauta(f, 1) == -1);

    // Adăugare câteva entități pentru testare
    addEntitate(f, creeazaOferta("laptop", "Lenovo", "ThinkPad", 1500, 10, 1));
    addEntitate(f, creeazaOferta("telefon", "Samsung", "Galaxy S20", 1000, 5, 3));
    addEntitate(f, creeazaOferta("smartwatch", "Apple", "Watch Series 6", 400, 3, 2));

    // Testare căutare ID inexistent
    assert(cauta(f, 4) == -1);

    // Testare căutare ID valid
    assert(cauta(f, 3));

    destroyOfferte(f);
}

void testCopy()
{
    // Creăm o listă de oferte pentru test
    Offerte* originalList = creeazaOfferte((DestroyFn)destroyOferta, (CopyFn) copyOferta);
    addEntitate(originalList, creeazaOferta("laptop", "Lenovo", "ThinkPad", 1500, 10, 1));
    addEntitate(originalList, creeazaOferta("telefon", "Samsung", "Galaxy S20", 1000, 5, 2));
    addEntitate(originalList, creeazaOferta("smartwatch", "Apple", "Watch Series 6", 400, 3, 3));

    // Copiem lista
    Offerte* copiedList = copy(originalList);

    // Verificăm că dimensiunea și capacitatea sunt aceleași
    assert(sizeList(originalList) == sizeList(copiedList));
    assert(originalList->capacitate == copiedList->capacitate);


    // Eliberăm memoria
    destroyOfferte(originalList);
    destroyOfferte(copiedList);
}

void testPopElement()
{
    // Creăm o listă de oferte pentru test
    Offerte* listaOferte = creeazaOfferte((DestroyFn)destroyOferta, (CopyFn) copyOferta);
    addEntitate(listaOferte, creeazaOferta("laptop", "Lenovo", "ThinkPad", 1500, 10, 1));
    addEntitate(listaOferte, creeazaOferta("telefon", "Samsung", "Galaxy S20", 1000, 5, 2));
    addEntitate(listaOferte, creeazaOferta("smartwatch", "Apple", "Watch Series 6", 400, 3, 3));

    // Extragem ultimul element din listă
    Entitate ultimulElement = popElement(listaOferte);

    // Verificăm că dimensiunea listei a scăzut cu 1
    assert(sizeList(listaOferte) == 2);

    // Eliberăm memoria
    destroyOferta(ultimulElement);
    destroyOfferte(listaOferte);
}

void service_tests() {
    BigList* newService = createBigList();
    Offerte* undo = newService->undo_lista;
    Offerte* elements = newService->lista;
    assert(newService->undo_lista->dimensiune == 0);
    assert(newService->lista->dimensiune == 0);
    addEnt(newService, "type", "model", "producer", 100, 1, 10);

    assert(elements->dimensiune == 1);
    assert(undo->dimensiune == 1);

    Oferta* oferta1 = getElement(elements, 0);
    assert(strcmp(oferta1->tip, "type") == 0);
    assert(strcmp(oferta1->model, "model") == 0);
    assert(strcmp(oferta1->producer, "producer") == 0);
    assert(oferta1->pret == 100);
    assert(oferta1->stoc == 10);


    assert(updateEnt(newService, "type", "model", "producer", 100, 59, 10) == -1);

    addEnt(newService, "type", "model", "producer", 100, 2, 10);
    assert(elements->dimensiune == 2);
    assert(undo->dimensiune == 2);

    assert(updateEnt(newService, "type", "model", "producer", 100, 1, 10) == 0);

    assert(undo->dimensiune == 3);

    addEnt(newService, "type", "model", "producer", 100, 3, 10);
    assert(elements->dimensiune == 3);
    assert(undo->dimensiune == 4);

    int length = elements->dimensiune;
        assert(deleteEnt(newService, 3) == 1);
    assert(deleteEnt(newService, 5) == 0);
    int i;
    for (i = 0; i < length; i++)
    {
        assert(undo_service(newService) == 0);
    }

    //undo_service
    int ok;
    ok = undo_service(newService);
    assert(ok == 0);
    assert(undo_service(newService) == 0);
    assert(undo->dimensiune == 0);
    assert(undo_service(newService) == 1);

    assert(addEnt(newService,"","","", -1,-1,5) == 0);

    destroyBigList(newService);

}
void testFilterPret()
{
    BigList* newService = createBigList();
    Offerte* undo = newService->undo_lista;
    Offerte* elements = newService->lista;

    addEnt(newService,"type", "model", "producer", 100, 59, 10);
    addEnt(newService,"type", "model", "producer", 40, 40, 10);
    addEnt(newService,"type", "model", "producer", 160, 23, 10);

    Offerte * f1 = filterPret(newService, 50);

    assert(f1->dimensiune == 1);

    int ok = undo_service(newService);
    ok = undo_service(newService);
    ok = undo_service(newService);
    destroyOfferte(f1);
    destroyBigList(newService);
}

void testFilterTip()
{
    BigList* newService = createBigList();
    Offerte* undo = newService->undo_lista;
    Offerte* elements = newService->lista;

    addEnt(newService,"type", "model", "producer", 100, 59, 10);
    addEnt(newService,"type", "model", "producer", 40, 40, 10);
    addEnt(newService,"type", "model", "producer", 160, 23, 10);

    Offerte * f2 = filterTip(newService, 'r');
    assert(f2->dimensiune == 0);
    Offerte * f1 = filterTip(newService, 't');
    assert(f1->dimensiune == 3);

    int ok = undo_service(newService);
    ok = undo_service(newService);
    ok = undo_service(newService);
    destroyOfferte(f1);
    destroyOfferte(f2);
    destroyBigList(newService);
}

void testsortingfunctions()
{
    Oferta oferta1 = {"type", "model", "producer", 100, 59, 10};
    Oferta oferta2 = {"type", "model", "producer", 40, 40, 12};
    assert(cmpPret(&oferta1, &oferta2) > 0);
    assert(cmpPret(&oferta2, &oferta1) < 0);
    assert(cmpPret(&oferta1, &oferta1) == 0);

    // Test cmpPretD function
    assert(cmpPretD(&oferta1, &oferta2) < 0);
    assert(cmpPretD(&oferta2, &oferta1) > 0);
    assert(cmpPretD(&oferta1, &oferta1) == 0);

    // Test cmpDestinatie function
    assert(cmpStoc(&oferta1, &oferta2) < 0);
    assert(cmpStoc(&oferta2, &oferta1) > 0);
    assert(cmpStoc(&oferta1, &oferta1) == 0);


    // Test cmpDestinatieD function
    assert(cmpStocD(&oferta1, &oferta2) > 0);
    assert(cmpStocD(&oferta2, &oferta1) < 0);
    assert(cmpStocD(&oferta1, &oferta1) == 0);

}

void testesort()
{
    BigList *list = createBigList();

    Offerte* f = list->lista;
    Oferta* m = creeazaOferta("type", "model", "producer", 100, 59, 15);
    Oferta* m1 = creeazaOferta("type", "model", "producer", 50, 59, 13);
    Oferta* m2 = creeazaOferta("type", "model", "producer", 60, 59, 18);

    addEntitate(f,m);
    addEntitate(f,m1);
    addEntitate(f,m2);
    BigList* sortedList = sortPret(list);
    assert(getPret(sortedList->lista->oferte[0]) == 50);
    BigList* sortedListB = sortPretb(list);
    assert(getPret(sortedListB->lista->oferte[0]) == 50);
    BigList* sortedListD = sortPretD(list);
    assert(getPret(sortedListD->lista->oferte[0]) == 100);
    BigList* sortedListDB = sortPretDb(list);
    assert(getPret(sortedListDB->lista->oferte[0]) == 100);

    BigList* sortedListS = sortStoc(list);
    assert(getStoc(sortedListS->lista->oferte[0]) == 13);
    BigList* sortedListSB = sortStocb(list);
    assert(getStoc(sortedListSB->lista->oferte[0]) == 13);
    BigList* sortedListSD = sortStocD(list);
    assert(getStoc(sortedListSD->lista->oferte[0]) == 18);

    Oferta* m3 = creeazaOferta("type", "model", "producer", 60, 59, 20);
    addEntitate(f, m3);
    BigList* sortedListSDB = sortStocDb(list);
    assert(getStoc(sortedListSDB->lista->oferte[0]) == 20);

    destroyAll(list);

}

void runAllTests()
{
    testValideazaOferta();
    testCopyOferta();
    testAddEntitate();
    testAsiguraCapacitate();
    testDeleteEntitate();
    testUpdateOferta();
    testCauta();
    testCopy();
    testPopElement();
    service_tests();
    testFilterPret();
    testFilterTip();
    testsortingfunctions();
    testesort();

}