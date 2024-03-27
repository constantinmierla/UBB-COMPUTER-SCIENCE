//
// Created by Costi on 06-Mar-24.
//

#include "domain.h"

#include <stdlib.h>
#include <string.h>

/*
 * Creeaza o oferta noua.
 *
 * Parametri:
 *   - tip: tipul ofertei (char*)
 *   - destinatie: destinatia ofertei (char*)
 *   - data_plecarii: data plecarii (char*)
 *   - pret: pretul ofertei (float)
 *
 * Returneaza:
 *   oferta - o structura reprezentand o oferta cu specificatiile date
 */
Oferta* creeazaOferta(char* tip,char* model, char* producer, int pret,int id, int stoc)
{
    Oferta* p =(Oferta*) malloc(sizeof(Oferta));


    p->id = id;

    int nr = (int)strlen(tip) + 1;
    p->tip = (char*)malloc(sizeof(char)*nr);
    strcpy(p->tip, tip);

    nr = (int)strlen(model) + 1;
    p->model = (char*)malloc(sizeof(char)*nr);
    strcpy(p->model, model);
    nr = (int)strlen(producer) + 1;
    p->producer = (char*)malloc(sizeof(char)*nr);
    strcpy(p->producer, producer);
    p->pret = pret;
    p->id = id;
    p->stoc = stoc;
    return p;
}
//Copiaza oferta
Oferta* copyOferta(Oferta* o)
{
    Oferta* p =(Oferta*) malloc(sizeof(Oferta));

    p->id = o->id;

    p->tip = (char*)malloc(sizeof(char)*(strlen(o->tip)+1));
    strcpy(p->tip,o->tip);

    p->model = (char*)malloc(sizeof(char)*(strlen(o->model)+1));
    strcpy(p->model,o->model);

    p->producer = (char*)malloc(sizeof(char)*(strlen(o->producer)+1));
    strcpy(p->producer,o->producer);

    p->pret = o->pret;
    p->stoc = o->stoc;
    return p;
}

/*
 * Distruge o oferta.
 *
 * Parametri:
 *   - o: oferta de distrus (oferta*)
 */
void destroyOferta(Oferta* o)
{
    free(o->producer);
    free(o->tip);
    free(o->model);
    free(o);
}

//Primeste ID
int getId(Oferta* o)
{
    return o->id;
}

//Primeste pret
int getPret(Oferta* p)
{
    return p->pret;
}


//Seteaza pret
void setPret(Oferta* o,int pret_nou) //pt modificare
{
    o->pret = pret_nou;
}


/*
 * Valideaza o oferta.
 *
 * Parametri:
 *   - o: oferta de validat (oferta)
 *
 * Returneaza:
 *   int - 1 daca oferta este valida, 0 altfel
 */
int valideazaOferta(Oferta* o)
{
    if(o->id<=0)
        return -1;
    if(o->pret<=0)
        return -1;
    if(o->stoc<=0)
        return -1;
    if(strlen(o->tip)<1)
        return -1;
    if(strlen(o->model)<1)
        return -1;
    if(strlen(o->producer)<1)
        return -1;

    return 1;
}
