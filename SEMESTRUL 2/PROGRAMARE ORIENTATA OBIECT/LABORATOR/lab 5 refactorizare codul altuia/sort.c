//
// Created by Costi on 20-Mar-24.
//
#include <stdlib.h>
#include "sort.h"
#include "repository.h"
#include "service.h"
#include "string.h"
/**
* Sorteaza in place
* cmpf - relatia dupa care se sorteaza
*/

void sort(Offerte* l, CompareFct cmpF)
{
    int i, j;
    for (i = 0; i < l->dimensiune - 1; i++) {
        for (j = i + 1; j < l->dimensiune; j++) {
            if (cmpF(l->oferte[i], l->oferte[j]) > 0) {
                // Swap elements l->lista[i] and l->lista[j]
                Entitate temp = l->oferte[i];
                l->oferte[i] = l->oferte[j];
                l->oferte[j] = temp;
            }
        }
    }
}