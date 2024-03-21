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
Oferta* creeazaOferta(char* tip, char* destinatie, char* data_plecarii, int pret, int id)
{
    Oferta* p =(Oferta*) malloc(sizeof(Oferta));


    p->id = id;

    int nr = (int)strlen(tip) + 1;
    p->tip = (char*)malloc(sizeof(char)*nr);
    strcpy(p->tip, tip);

    nr = (int)strlen(destinatie) + 1;
    p->destinatie = (char*)malloc(sizeof(char)*nr);
    strcpy(p->destinatie, destinatie);
    nr = (int)strlen(data_plecarii) + 1;
    p->data_plecarii = (char*)malloc(sizeof(char)*nr);
    strcpy(p->data_plecarii, data_plecarii);
    p->pret = pret;
    p->id = id;

    return p;
}
//Copiaza oferta
Oferta* copyOferta(Oferta* o)
{
    Oferta* p =(Oferta*) malloc(sizeof(Oferta));

    p->id = o->id;

    p->tip = (char*)malloc(sizeof(char)*(strlen(o->tip)+1));
    strcpy(p->tip,o->tip);

    p->destinatie = (char*)malloc(sizeof(char)*(strlen(o->destinatie)+1));
    strcpy(p->destinatie,o->destinatie);

    p->data_plecarii = (char*)malloc(sizeof(char)*(strlen(o->data_plecarii)+1));
    strcpy(p->data_plecarii,o->data_plecarii);

    p->pret = o->pret;

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
    free(o->data_plecarii);
    free(o->tip);
    free(o->destinatie);
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
    if((strcmp(o->tip,"mare") != 0) && (strcmp(o->tip,"MUNTE") != 0))
        return -1;
    if(strlen(o->destinatie)<1)
        return -1;
    if(strlen(o->data_plecarii)<1)
        return -1;

    return 1;
}
