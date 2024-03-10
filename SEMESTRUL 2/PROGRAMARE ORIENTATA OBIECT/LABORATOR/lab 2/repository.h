//
// Created by Costi on 11-Mar-24.
//
#include "domain.h"
#ifndef LAB_2_REPOSITORY_H
#define LAB_2_REPOSITORY_H

#endif //LAB_2_REPOSITORY_H

typedef oferta ElemType;

typedef struct {
    ElemType elements[100];
    int length;
}List;

List createEmpty();

void destroy(List* v);

void add(List *v, ElemType);

void addOferta(List *v, ElemType el, int poz);

ElemType delete(List *v, int poz);

ElemType get(List *v, int poz);

int size(List *v);

