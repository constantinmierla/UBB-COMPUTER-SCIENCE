//
// Created by Costi on 11-Mar-24.
//

#include "repository.h"

List createEmpty()
{
    List v;
    v.length = 0;
    return v;
}

void destroy(List* v)
{
    v->length = 0;
}

void add(List *v, ElemType el)
{
    v->elements[v->length] = el;
    v->length++;
}

void addOferta(List *v, ElemType el, int poz)
{
    v->elements[poz] = el;
}

ElemType delete(List *v, int poz)
{
    ElemType el = v->elements[poz];
    for (int i = poz; i < v-> length - 1; i++)
    {
        v->elements[i] = v->elements[i+1];
    }
    v->length--;
    return el;
}

ElemType get(List *v, int poz)
{
    return v->elements[poz];
}

int size(List *v)
{
    return v->length;
}