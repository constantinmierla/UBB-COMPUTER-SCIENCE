//
// Created by Costi on 20-Mar-24.
//
#include <stdlib.h>

#include "sort.h"
#include "repository.h"

/**
* Sorteaza in place
* cmpf - relatia dupa care se sorteaza
*/
void funcSortC(List* l, FunctieComparare cmpF) {
    int i, j;
    for (i = 0; i < size(l); i++) {
        for (j = i + 1; j < size(l); j++) {
            oferta o1 = get(l, i);
            oferta o2 = get(l, j);
            if (cmpF(&o1, &o2) > 0) {
                //interschimbam
                setElem(l, i, o2);
                setElem(l, j, o1);
            }
        }
    }
}

void funcSortD(List* l, FunctieComparare cmpF) {
    int i, j;
    for (i = 0; i < size(l); i++) {
        for (j = i + 1; j < size(l); j++) {
            oferta o1 = get(l, i);
            oferta o2 = get(l, j);
            if (cmpF(&o1, &o2) < 0) {
                //interschimbam
                setElem(l, i, o2);
                setElem(l, j, o1);
            }
        }
    }
}