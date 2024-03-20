//
// Created by Costi on 11-Mar-24.
//

#include "repository.h"
#include <stdlib.h>
#include <string.h>
/*
 * Creeaza o lista vida.
 *
 * Returneaza:
 *   List - o lista vida
 */
List createEmpty()
{
    List v;
    v.length = 0;
    v.capacity = 4; //de mod
    v.elements = (oferta*)malloc(sizeof(oferta) * v.capacity);
    return v;
}

void ensureCapacity(List* v)
{
    if(v->length < v->capacity)
        return;

    int newCap = v->capacity*2;
    oferta* n = (oferta*)malloc(sizeof(oferta)*newCap);

    for(int i = 0; i < v->length; i++)
        n[i] = v->elements[i];

    free(v->elements);
    v->elements = n;
    v->capacity=newCap;
}
/*
 * Distruge o lista.
 *
 * Parametri:
 *   - v: adresa listei de distrus (List*)
 */
void destroy(List* v)
{
    if (v == NULL)
        return;
    for (int i = 0; i < v->length; i++){
        distrugeOferta(&v->elements[i]);
    }
    free(v->elements);
    v->elements = NULL;
    v->length = 0;
    v->capacity = 0;
    //free(v);
}

/*
 * Adauga un element la sfarsitul listei.
 *
 * Parametri:
 *   - v: lista in care se adauga elementul (List*)
 *   - el: elementul de adaugat (ElemType)
 */
void add(List *v, ElemType el)
{
    ensureCapacity(v);
    v->elements[v->length] = copyOferta(&el); // = el
    v->length++;
}

/*
 * Adauga un element la o pozitie specificata in lista.
 *
 * Parametri:
 *   - v: lista in care se adauga elementul (List*)
 *   - el: elementul de adaugat (ElemType)
 *   - poz: pozitia la care se adauga elementul (int)
 */
void addOferta(List *v, ElemType el, int poz)
{
    v->elements[poz] = el;
}

/*
 * Sterge un element din lista de pe o pozitie specificata.
 *
 * Parametri:
 *   - v: lista din care se sterge elementul (List*)
 *   - poz: pozitia de unde se sterge elementul (int)
 *
 * Returneaza:
 *   ElemType - elementul sters
 */
ElemType sterge(List *v, int poz)
{
    ElemType el = v->elements[poz];
    free(v->elements[poz].tip);
    free(v->elements[poz].destinatie);
    free(v->elements[poz].data_plecarii);
    for (int i = poz; i < v-> length - 1; i++)
    {
        v->elements[i] = v->elements[i+1];
    }
    v->length--;
    return el;
}

List copyList(List* v)
{
    List rez = createEmpty();
    for(int i = 0; i < size(v); i++)
    {
        ElemType el = get(v,i);
        add(&rez, copyOferta(&el));
    }
    return rez;
}
/*
 * Returneaza elementul de pe o anumita pozitie din lista.
 *
 * Parametri:
 *   - v: lista din care se extrage elementul (List*)
 *   - poz: pozitia de unde se extrage elementul (int)
 *
 * Returneaza:
 *   ElemType - elementul de pe pozitia data
 */
ElemType get(List *v, int poz)
{
    return v->elements[poz];
}

/*
 * Returneaza numarul de elemente din lista.
 *
 * Parametri:
 *   - v: lista pentru care se calculeaza dimensiunea (List*)
 *
 * Returneaza:
 *   int - numarul de elemente din lista
 */
int size(List *v)
{
    return v->length;
}
ElemType setElem(List* v, int poz, oferta o)
{
    ElemType rez = v->elements[poz];
    v->elements[poz] = o;
    return rez;
}