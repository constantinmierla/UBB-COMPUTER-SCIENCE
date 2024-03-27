//
// Created by Costi on 06-Mar-24.
//

#ifndef LAB_2_DOMAIN_H
#define LAB_2_DOMAIN_H
#include <stdlib.h>

typedef struct{
    char *model;
    char *tip;
    char *producer;
    int pret;
    int id;
} Oferta;

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
Oferta* creeazaOferta(char* tip,char* model, char* producer, int pret,int id);

void destroyOferta(Oferta*);

/*Primeste o entitate Oferta si ii returneaza numele.*/

/*Primeste o entitate Oferta si ii returneaza id-ul.*/
int getId(Oferta*);

/*Primeste o entitate Oferta si ii returneaza stocul.*/
int getPret(Oferta*);

/*Incrementeaza stocul unui oferte.*/
void setPret(Oferta*,int);

/*Valideaza o oferta dat*/
int valideazaOferta(Oferta*);

//Copiaza oferta
Oferta* copyOferta(Oferta*);

#endif //LAB_2_DOMAIN_H