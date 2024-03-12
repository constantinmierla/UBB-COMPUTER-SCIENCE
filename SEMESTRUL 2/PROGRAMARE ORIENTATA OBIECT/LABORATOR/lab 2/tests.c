//
// Created by Costi on 12-Mar-24.
//
#include <assert.h>
#include <string.h>
#include "tests.h"


// teste DOMAIN
void test_creeazaOferta() {
    oferta o = creeazaOferta("munte", "Busteni", "2024-03-15", 150.0);
    assert(strcmp(o.tip, "munte") == 0);
    assert(strcmp(o.destinatie, "Busteni") == 0);
    assert(strcmp(o.data_plecarii, "2024-03-15") == 0);
    assert(o.pret == 150.0);
}

void test_destroyOferta() {
    oferta o = creeazaOferta("munte", "Busteni", "2024-03-15", 150.0);
    distrugeOferta(&o);
    assert(strcmp(o.tip, "") == 0);
    assert(strcmp(o.destinatie, "") == 0);
    assert(strcmp(o.data_plecarii, "") == 0);
    assert(o.pret == -1);
}

void test_ValideazaOferta() {

    oferta o1 = creeazaOferta("munte", "Busteni", "2024-03-15", 150.0);
    assert(valideazaOferta(o1) == 1);

    oferta o2 = creeazaOferta("mare", "Busteni", "2024-03-15", 150.0);
    assert(valideazaOferta(o2) == 1);

}


// teste REPOSITORY

void test_createEmpty() {
    List v = createEmpty();
    assert(v.length == 0);
}

void testAddAndGet() {
    List v = createEmpty();
    oferta el1 = creeazaOferta("mare", "destinatie1", "01-01-2025", 100.0);
    oferta el2 = creeazaOferta("mare", "destinatie2", "01-01-2026", 200.0);
    add(&v, el1);
    add(&v, el2);
    assert(size(&v) == 2);
    assert(strcmp(get(&v, 0).tip, el1.tip) == 0);
    assert(strcmp(get(&v, 0).destinatie, el1.destinatie) == 0);
    assert(strcmp(get(&v, 0).data_plecarii, el1.data_plecarii) == 0);
    assert(get(&v, 0).pret == el1.pret);

    assert(strcmp(get(&v, 1).tip, el2.tip) == 0);
    assert(strcmp(get(&v, 1).destinatie, el2.destinatie) == 0);
    assert(strcmp(get(&v, 1).data_plecarii, el2.data_plecarii) == 0);
    assert(get(&v, 1).pret == el2.pret);
}

void test_addCantitate() {
    List v = createEmpty();
    oferta el1 = creeazaOferta("mare", "destinatie1", "01-01-2025", 100.0);
    oferta el2 = creeazaOferta("mare", "destinatie2", "01-01-2026", 200.0);
    oferta el3 = creeazaOferta("mare", "destinatie3", "01-01-2027", 300.0);
    add(&v, el1);
    add(&v, el2);
    assert(size(&v) == 2);


    addOferta(&v, el3, 1);


    assert(strcmp(get(&v, 0).tip, el1.tip) == 0);
    assert(strcmp(get(&v, 1).tip, el3.tip) == 0); // el3 is now at index 1
}


void test_delete() {
    List v = createEmpty();
    oferta el1 = creeazaOferta("mare", "destinatie1", "01-01-2025", 100.0);
    oferta el2 = creeazaOferta("mare", "destinatie2", "01-01-2026", 200.0);
    add(&v, el1);
    add(&v, el2);
    assert(size(&v) == 2);

    sterge(&v, 0);
    assert(size(&v) == 1);

    assert(strcmp(get(&v, 0).tip, el2.tip) == 0);
    assert(strcmp(get(&v, 0).destinatie, el2.destinatie) == 0);
    assert(strcmp(get(&v, 0).data_plecarii, el2.data_plecarii) == 0);
    assert(get(&v, 0).pret == el2.pret);
}


void test_size() {
    List v = createEmpty();

    oferta el1 = creeazaOferta("mare", "destinatie1", "01-01-2025", 100.0);
    oferta el2 = creeazaOferta("munte", "destinatie2", "01-01-2026", 200.0);
    oferta el3 = creeazaOferta("mare", "destinatie3", "01-01-2027", 300.0);
    add(&v, el1);
    add(&v, el2);
    add(&v, el3);


    assert(size(&v) == 3);
}

//teste SERVICE

void test_adaugaService() {
    List v = createEmpty();
    char tip[] = "munte";
    char destinatie[] = "Bucegi";
    char data_plecarii[] = "2024-05-15";
    float pret = 150.0;


    int result = adaugaOferta(&v, tip, destinatie, data_plecarii, pret);
    assert(result == 1);
    assert(size(&v) == 1);
}

void test_modificaService() {
    List v = createEmpty();
    char tip[] = "munte";
    char destinatie[] = "Bucegi";
    char data_plecarii[] = "2024-05-15";
    float pret = 150.0;


    adaugaOferta(&v, tip, destinatie, data_plecarii, pret);


    float pret_nou = 200.0;
    int result = modificaOferta(&v, tip, destinatie, data_plecarii, pret_nou);
    assert(result == 1);
}

void test_stergeService() {
    List v = createEmpty();
    char tip[] = "munte";
    char destinatie[] = "Bucegi";
    char data_plecarii[] = "2024-05-15";
    float pret = 150.0;


    adaugaOferta(&v, tip, destinatie, data_plecarii, pret);


    int result = stergeOferta(&v, tip, destinatie, data_plecarii);
    assert(result == 1);
    assert(size(&v) == 0);
}

void test_filtru() {


}

void test_sort() {

}