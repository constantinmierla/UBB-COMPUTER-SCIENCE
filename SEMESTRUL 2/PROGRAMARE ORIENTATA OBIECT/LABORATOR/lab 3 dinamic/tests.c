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
void testValideazaOferta()
{
    int idRau = -1;
    char* tip = "mere";
    int pretRau = -1;
    char* destinatie = "";
    char* data_plecarii = "";

    Oferta* o = creeazaOferta(tip,"paris","28.05.2004",15,10);
    assert(valideazaOferta(o)==-1);

    Oferta* o1 = creeazaOferta("mare",destinatie,"28.05.2004",15,1);
    assert(valideazaOferta(o1)==-1);

    Oferta* o2 = creeazaOferta("mare","paris",data_plecarii,15,2);
    assert(valideazaOferta(o2)==-1);


    Oferta* o3 = creeazaOferta("mare","paris","28.05.2004",pretRau,3);
    assert(valideazaOferta(o3)==-1);

    Oferta* o4 = creeazaOferta("mare","paris","28.05.2004",15,idRau);
    assert(valideazaOferta(o4)==-1);

    Oferta* o5 = creeazaOferta("mare","paris","28.05.2004",15,5);
    assert(valideazaOferta(o5)==1);

    destroyOferta(o);
    destroyOferta(o1);
    destroyOferta(o2);
    destroyOferta(o3);
    destroyOferta(o4);
    destroyOferta(o5);
}

void testUpdate()
{
    BigList list = createBigList();
    Offerte* f = list.lista;
    Oferta* m = creeazaOferta("mare","paris","28.05.2004",15,5);
    setPret(m,12);
    addEntitate(f,m);

    assert(updateEnt(&list,"mare","paris","28.05.2004",15,6)==-1);
    assert(updateEnt(&list,"mare","paris","28.05.2004",12,5)==0);

    destroyAll(&list);

}
void testCauta()
{
    BigList list = createBigList();
    Offerte* f = list.lista;
    Oferta * m = creeazaOferta("mare","paris","28.05.2004",15,5);
    addEntitate(f,m);
    assert(checkId(&list,5)==1);
    assert(checkId(&list,6)==0);

    destroyAll(&list);
}

void testAddEntitate()
{
    BigList list = createBigList();

    addEnt(&list,"mare","paris1","28.05.2004",15,5);
    addEnt(&list,"mare","paris2","28.05.2004",15,6);
    addEnt(&list,"mare","paris3","28.05.2004",15,7);
    assert(list.lista->dimensiune==3);
    Oferta* p = get(list.lista,0);

    assert(5 == p->id);
    assert(15 == p->pret);

    assert(addEnt(&list,"lac","paris1","28.05.2004",15,5)==0);

    destroyAll(&list);

}

void testDeleteEntitate()
{
    BigList list = createBigList();
    Offerte* f = list.lista;
    Oferta* m = creeazaOferta("mare","paris","28.05.2004",15,5);
    Oferta* m1 = creeazaOferta("mare","paris","28.05.2004",14,6);
    Oferta* m2 = creeazaOferta("mare","paris","28.05.2004",13,7);
    Oferta* m3 = creeazaOferta("mare","paris","28.05.2004",12,8);

    addEntitate(f,m);
    addEntitate(f,m1);
    addEntitate(f,m2);
    addEntitate(f,m3);
    assert(deleteEnt(&list,4)==0);
    assert(deleteEnt(&list,5)==1);
    destroyAll(&list);
}

void testAsiguraCapacitate()
{
    Offerte * f = creeazaOfferte();
    Oferta* m = creeazaOferta("mare","paris","28.05.2004",15,5);
    Oferta* m1 = creeazaOferta("mare","paris","28.05.2004",14,6);
    Oferta* m2 = creeazaOferta("mare","paris","28.05.2004",13,7);
    addEntitate(f,m);
    addEntitate(f,m1);
    assert(f->capacitate==2);
    addEntitate(f,m2);
    assert(f->capacitate==4);
    assert(f->dimensiune==3);
    destroyOfferte(f);

}


/*void testSortareStoc()
{
    BigList list = createBigList();

    addEnt(&list,19,"nurofen",3,10);
    addEnt(&list,21,"ceva",8,100);
    addEnt(&list,22,"ceva",8,1);
    addEnt(&list,26,"ceva",8,3);
    addEnt(&list,23,"ceva",8,9);

    Farmacie* f1 = sortareStoc(&list);

    assert(f1->dimensiune==5);

    for(int i=0; i<f1->dimensiune-1;i++)
    {
        Medicament* m1 = get(f1,i);
        Medicament* m2 = get(f1,i+1);
        assert(m1->stoc <= m2->stoc);

    }

    destroyFarmacie(f1);
    destroyAll(&list);
}*/


void testFilterPret()
{
    BigList list = createBigList();

    addEnt(&list,"mare","paris","28.05.2004",15,5);
    addEnt(&list,"mare","paris","28.05.2004",160,6);
    addEnt(&list,"mare","paris","28.05.2004",20,7);
    addEnt(&list,"mare","paris","28.05.2004",140,8);
    addEnt(&list,"mare","paris","28.05.2004",30,9);

    Offerte * f1 = filterPret(&list,100);

    assert(f1->dimensiune == 3);
    assert(getPret(f1->oferte[0]) == 15);
    assert(getPret(f1->oferte[1]) == 20);
    assert(getPret(f1->oferte[2]) == 30);

    destroyOfferte(f1);
    destroyAll(&list);
}

void testFilterTip()
{
    BigList list = createBigList();

    addEnt(&list,"mare","paris","28.05.2004",15,5);
    addEnt(&list,"MUNTE","paris","28.05.2004",160,6);
    addEnt(&list,"MUNTE","paris","28.05.2004",20,7);
    addEnt(&list,"mare","paris","28.05.2004",140,8);
    addEnt(&list,"mare","paris","28.05.2004",30,9);

    Offerte * f1 = filterTip(&list,'m');

    assert(f1->dimensiune == 3);
    assert(getPret(f1->oferte[0]) == 15);
    assert(getPret(f1->oferte[1]) == 140);
    assert(getPret(f1->oferte[2]) == 30);

    destroyOfferte(f1);
    destroyAll(&list);
}
void testdinsort() {
    BigList list = createBigList();
    Offerte* f = list.lista;
    Oferta* m = creeazaOferta("mare","paris","28.05.2004",15,5);
    Oferta* m1 = creeazaOferta("mare","paris","28.05.2004",14,6);
    Oferta* m2 = creeazaOferta("mare","paris","28.05.2004",13,7);
    Oferta* m3 = creeazaOferta("mare","paris","28.05.2004",12,8);

    addEntitate(f,m);
    addEntitate(f,m1);
    addEntitate(f,m2);
    addEntitate(f,m3);
    sort(f, cmpPret);

    // Assert that the resulting list is sorted
    assert(getPret(f->oferte[0]) == 12); // First element should have price 12
    assert(getPret(f->oferte[1]) == 13); // Second element should have price 13
    assert(getPret(f->oferte[2]) == 14); // Third element should have price 14
    assert(getPret(f->oferte[3]) == 15); // Fourth element should have price 15
    destroyAll(&list);
}
void testSortingFunctions() {
    // Test cmpPret function
    Oferta oferta1 = {"paris", "dest1", "2024-01-01", 20, 1};
    Oferta oferta2 = {"roma", "dest2", "2024-01-01", 15, 2};
    assert(cmpPret(&oferta1, &oferta2) > 0);
    assert(cmpPret(&oferta2, &oferta1) < 0);
    assert(cmpPret(&oferta1, &oferta1) == 0);

    // Test cmpPretD function
    assert(cmpPretD(&oferta1, &oferta2) < 0);
    assert(cmpPretD(&oferta2, &oferta1) > 0);
    assert(cmpPretD(&oferta1, &oferta1) == 0);

    // Test cmpDestinatie function
    assert(cmpDestinatie(&oferta1, &oferta2) < 0);
    assert(cmpDestinatie(&oferta2, &oferta1) > 0);
    assert(cmpDestinatie(&oferta1, &oferta1) == 0);


    // Test cmpDestinatieD function
    assert(cmpDestinatieD(&oferta1, &oferta2) > 0);
    assert(cmpDestinatieD(&oferta2, &oferta1) < 0);
    assert(cmpDestinatieD(&oferta1, &oferta1) == 0);

}
void testesortpret()
{
    BigList list = createBigList();

    Offerte* f = list.lista;
    Oferta* m = creeazaOferta("mare","paris","28.05.2004",15,5);
    Oferta* m1 = creeazaOferta("mare","paris","28.05.2004",14,6);
    Oferta* m2 = creeazaOferta("mare","paris","28.05.2004",13,7);
    Oferta* m3 = creeazaOferta("mare","paris","28.05.2004",12,8);

    addEntitate(f,m);
    addEntitate(f,m1);
    addEntitate(f,m2);
    addEntitate(f,m3);
    BigList* sortedList = sortPret(&list);
    assert(getPret(sortedList->lista->oferte[0]) == 12);
    destroyAll(&list);
}
void testesortpretd()
{
    BigList list = createBigList();

    Offerte* f = list.lista;
    Oferta* m = creeazaOferta("mare","paris","28.05.2004",15,5);
    Oferta* m1 = creeazaOferta("mare","paris","28.05.2004",14,6);
    Oferta* m2 = creeazaOferta("mare","paris","28.05.2004",13,7);
    Oferta* m3 = creeazaOferta("mare","paris","28.05.2004",12,8);

    addEntitate(f,m);
    addEntitate(f,m1);
    addEntitate(f,m2);
    addEntitate(f,m3);
    BigList* sortedList = sortPretD(&list);
    assert(getPret(sortedList->lista->oferte[0]) == 15);
    destroyAll(&list);
}
void testesortdest()
{
    BigList list = createBigList();

    Offerte* f = list.lista;
    Oferta* m = creeazaOferta("mare","paris2","28.05.2004",15,5);
    Oferta* m1 = creeazaOferta("mare","paris1","28.05.2004",14,6);
    Oferta* m2 = creeazaOferta("mare","paris3","28.05.2004",13,7);
    Oferta* m3 = creeazaOferta("mare","paris4","28.05.2004",12,8);

    addEntitate(f,m);
    addEntitate(f,m1);
    addEntitate(f,m2);
    addEntitate(f,m3);
    BigList* sortedList = sortDestinatie(&list);
    assert(getPret(sortedList->lista->oferte[0]) == 14);
    destroyAll(&list);
}
void testesortdestd()
{
    BigList list = createBigList();

    Offerte* f = list.lista;
    Oferta* m = creeazaOferta("mare","paris2","28.05.2004",15,5);
    Oferta* m1 = creeazaOferta("mare","paris1","28.05.2004",14,6);
    Oferta* m2 = creeazaOferta("mare","paris3","28.05.2004",13,7);
    Oferta* m3 = creeazaOferta("mare","paris4","28.05.2004",12,8);

    addEntitate(f,m);
    addEntitate(f,m1);
    addEntitate(f,m2);
    addEntitate(f,m3);
    BigList* sortedList = sortDestinatieD(&list);
    assert(getPret(sortedList->lista->oferte[0]) == 12);
    destroyAll(&list);
}
void repotestadd()
{
    BigList list = createBigList();
    Offerte* f = list.lista;
    Oferta * m = creeazaOferta("mare","paris","28.05.2004",15,5);
    addEntitate(f,m);
    assert(getPret(f->oferte[0]) == 15);

    destroyAll(&list);
}
void repotestdelete()
{
    BigList list = createBigList();
    Offerte* f = list.lista;
    Oferta * m = creeazaOferta("mare","paris","28.05.2004",15,5);
    addEntitate(f,m);
    assert(getPret(f->oferte[0]) == 15);
    assert(deleteEntitate(f,5) == 0);
    destroyAll(&list);
}
void runAllTests()
{
    repotestadd();
    repotestdelete();
    testValideazaOferta();
    testCauta();
    testAddEntitate();
    testDeleteEntitate();
    testUpdate();
    testAsiguraCapacitate();
    testFilterPret();
    testFilterTip();
    testdinsort();
    testSortingFunctions();
    testesortdestd();
    testesortpretd();
    testesortpret();
    testesortdest();
}
