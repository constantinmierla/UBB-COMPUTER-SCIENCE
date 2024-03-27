#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include "service.h"
#include "domain.h"
#include "repository.h"
#include "sort.h"
BigList createBigList()
{
    BigList listaMeds;
    listaMeds.lista = creeazaOfferte();
    return listaMeds;
}

void destroyBigList(BigList* list)
{
    destroyOfferte(list->lista);
}

/*Adauga  o oferta in lista.
 * Pre: list- de tip BigList*
 * Post: 0 daca entitatea exista deja in lista, 1 altfel
 */
int addEnt(BigList* list, char* tip, char* model, char* producer, int pret, int id)
{
    Oferta* e = creeazaOferta(tip, model, producer, pret, id);
    if(valideazaOferta(e) == 1)
    {
        addEntitate(list->lista,e);
        return 1;
    }
    else
    {
        destroyOferta(e);
        return 0;
    }
}
/*Functie care sterge o entitate
 *Pre:list de tip BigList*, id de tip int
 * Post: 1 daca id-ul este in lista si a fost sters, 0 altfel
 */
int deleteEnt(BigList* list,int id)
{
    if(checkId(list,id))
    {
        deleteEntitate(list->lista,id);
        return 1;
    }
    return 0;
}

/*Face update .
 * Pre: list- de tip BigList*
 * Post: 0 daca entitatea exista deja in lista si s-a facut modificarea, 1 altfel
 */
int updateEnt(BigList* list, char* tip, char* model, char* producer, int pret, int id)
{
    for(int i=0;i<list->lista->dimensiune;i++)
    {
        if(getId(get(list->lista,i))==id)
        {
            Entitate e = creeazaOferta(tip, model, producer, pret, id);
            updateOferta(list->lista,e);
            return 0;
        }

    }
    return -1;
}

/*Cauta daca un id este in lista*/
int checkId(BigList* list,int id)
{
    if(cauta(list->lista,id) != -1)
        return 1;
    return 0;
}


/*Dealoca tot*/
void destroyAll(BigList* list)
{
    destroyBigList(list);
}

int cmpPret(Oferta* m1, Oferta* m2) {
    if (m1->pret == m2->pret)
        return 0;
    if (m1->pret > m2->pret)
        return 1;
    else
        return -1;
}

int cmpPretD(Oferta* m1, Oferta* m2) {
    if (m1->pret == m2->pret)
        return 0;
    if (m1->pret < m2->pret)
        return 1;
    else
        return -1;
}

int cmpDestinatie(Oferta* m1, Oferta* m2) {
    /*if (strcmp(m1->destinatie, m2->destinatie) > 0)
        return 1;
    if (strcmp(m1->destinatie, m2->destinatie) < 0)
        return -1;
    else
        return 0;*/
}

int cmpDestinatieD(Oferta* m1, Oferta* m2) {
    /*if (strcmp(m1->destinatie, m2->destinatie) > 0)
        return -1;
    if (strcmp(m1->destinatie, m2->destinatie) < 0)
        return 1;
    else
        return 0;*/
}

BigList* sortPret(BigList* l) {
    sort(l->lista, cmpPret);
    return l;
}

BigList* sortPretD(BigList* l) {
    sort(l->lista, cmpPretD);
    return l;
}

BigList* sortDestinatie(BigList* l) {
    sort(l->lista, cmpDestinatie);
    return l;
}
BigList* sortDestinatieD(BigList* l) {
    sort(l->lista, cmpDestinatieD);
    return l;
}

/*Filtreaza ofertele care au pretul mai mic decat o valoare data*/
Offerte* filterPret(BigList* list, int val)
{
    Offerte* f = copy(list->lista);

    for(int i=0; i<f->dimensiune;i++)
    {
        Oferta* m = get(f,i);
        if(m->pret > val)
            deleteEntitate(f,m->id), i--;
    }
    return f;
}

/*Filtreaza ofertele dupa tip*/
Offerte* filterTip(BigList* list, char litera)
{
    Offerte* f = copy(list->lista);

    for(int i=0; i<f->dimensiune;i++)
    {
        Oferta* m = get(f,i);
        if(m->tip[0] != litera)
            deleteEntitate(f,m->id), i--;
    }

    return f;
}
