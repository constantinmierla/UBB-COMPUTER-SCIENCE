//
// Created by Costi on 20-Mar-24.
//

#ifndef LAB_2_SORT_H
#define LAB_2_SORT_H
#include "repository.h"
#include <stdlib.h>
#include "domain.h"

/*
   Tipul functie de comparare pentru 2 elemente
   returneaza 0 daca sunt egale, 1 daca o1>o2, -1 altfel
*/

typedef int (*CompareFct)(Oferta* el1, Oferta* el2);
void sort(Offerte* l, CompareFct cmpF);

void sortbubble(Offerte* l, CompareFct cmpF);

#endif //LAB_2_SORT_H*