//
// Created by Costi on 12-Mar-24.
//
#ifndef LAB_2_UI_H
#define LAB_2_UI_H

#endif //LAB_2_UI_H

#include "service.h"
#include <stdlib.h>

//Ruleaza toate testele definite pentru functionalitatile aplicatiei.
void testAll();

/*
 * Afiseaza meniul pentru adaugarea unei noi oferte si solicita utilizatorului sa introduca datele.
 * Parametri:
 *   - v: lista de oferte in care se adauga oferta (List*)
 */
void uiAdd(List *v);

/*
 * Afiseaza meniul pentru modificarea unei oferte si solicita utilizatorului sa introduca noile date.
 * Parametri:
 *   - v: lista de oferte in care se modifica oferta (List*)
 */
void uiModify(List *v);

/*
 * Afiseaza meniul pentru stergerea unei oferte si solicita utilizatorului sa introduca datele ofertei de sters.
 * Parametri:
 *   - v: lista de oferte din care se sterge oferta (List*)
 */
void uiDelete(List *v);

/*
 * Afiseaza meniul pentru sortarea ofertelor.
 * Parametri:
 *   - v: lista de oferte care urmeaza sa fie sortata (List*)
 */
void uiSort(List *v);

/*
 * Afiseaza meniul pentru filtrarea ofertelor si solicita utilizatorului sa introduca criteriile de filtrare.
 * Parametri:
 *   - v: lista de oferte care urmeaza sa fie filtrata (List*)
 */
void uiFilter(List *v);

/*
 * Afiseaza toate ofertele din lista.
 * Parametri:
 *   - v: lista de oferte care urmeaza sa fie afisata (List*)
 */
void getAll(List *v);

/*
 * Afiseaza meniul principal al aplicatiei.
 */
void menu();

/*
 * Porneste executia aplicatiei.
 */
void run();