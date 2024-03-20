//
// Created by Costi on 20-Mar-24.
//

#ifndef LAB_2_SORT_H
#define LAB_2_SORT_H
#include "repository.h"
#include <stdlib.h>


/*
   Tipul functie de comparare pentru 2 elemente
   returneaza 0 daca sunt egale, 1 daca o1>o2, -1 altfel
*/

typedef int(*FunctieComparare)(oferta* o1, oferta* o2);

/**
* Sorteaza in place
* cmpf - relatia dupa care se sorteaza
*/
void funcSortC(List* l, FunctieComparare cmpF);
void funcSortD(List* l, FunctieComparare cmpF);

#endif //LAB_2_SORT_H