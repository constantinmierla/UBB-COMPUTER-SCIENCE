//
// Created by Costi on 11-Mar-24.
//
#ifndef LAB_2_REPOSITORY_H
#define LAB_2_REPOSITORY_H
#include "domain.h"
#include <stdlib.h>

typedef oferta ElemType;

typedef struct {
    oferta* elements;
    int length;
    int capacity;
}List;

/*
 * Creeaza o lista vida.
 *
 * Returneaza:
 *   List - o lista vida
 */
List createEmpty();

/*
 * Distruge o lista.
 *
 * Parametri:
 *   - v: adresa listei de distrus (List*)
 */
void destroy(List* v);

/*
 * Adauga un element la sfarsitul listei.
 *
 * Parametri:
 *   - v: lista in care se adauga elementul (List*)
 *   - el: elementul de adaugat (ElemType)
 */
void ensureCapacity(List* v);//de comentat
void add(List *v, ElemType);

/*
 * Adauga un element la o pozitie specificata in lista.
 *
 * Parametri:
 *   - v: lista in care se adauga elementul (List*)
 *   - el: elementul de adaugat (ElemType)
 *   - poz: pozitia la care se adauga elementul (int)
 */
void addOferta(List *v, ElemType el, int poz);

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
ElemType sterge(List *v, int poz);

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
ElemType get(List *v, int poz);

/*
 * Returneaza numarul de elemente din lista.
 *
 * Parametri:
 *   - v: lista pentru care se calculeaza dimensiunea (List*)
 *
 * Returneaza:
 *   int - numarul de elemente din lista
 */
int size(List *v);

ElemType setElem(List* v, int poz, oferta o);

List copyList(List* v);
#endif //LAB_2_REPOSITORY_H