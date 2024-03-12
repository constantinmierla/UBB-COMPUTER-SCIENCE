//
// Created by Costi on 11-Mar-24.
//

#include "repository.h"

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
    return v;
}

/*
 * Distruge o lista.
 *
 * Parametri:
 *   - v: adresa listei de distrus (List*)
 */
void destroy(List* v)
{
    v->length = 0;
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
    v->elements[v->length] = el;
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
    for (int i = poz; i < v-> length - 1; i++)
    {
        v->elements[i] = v->elements[i+1];
    }
    v->length--;
    return el;
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