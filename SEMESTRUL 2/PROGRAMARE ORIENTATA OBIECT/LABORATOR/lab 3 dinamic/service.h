
#ifndef OOP_LAB2_4_SERVICE_H
#define OOP_LAB2_4_SERVICE_H
//#pragma once
#include "domain.h"
#include "repository.h"




typedef struct{
    Offerte* lista;
} BigList;

/*
	Functie care creaza o lista ce contine o lista de oferte
*/
BigList createBigList();

/*Functie care dealoca lista ce contine lista de oferte*/
void destroyBigList(BigList* );

/*Functie care adauga o entitate*/
int addEnt(BigList* list, char*, char*, char*, int, int);

/*Functie care sterge o entitate*/
int deleteEnt(BigList* list,int );

/*Functie care face update la o oferta*/
int updateEnt(BigList* , char*, char*, char*, int, int);

/*Cauta un id in lista*/
int checkId(BigList* list,int);


/*Distruge tot*/
void destroyAll(BigList* list);

int cmpPret(Oferta* m1, Oferta* m2);

int cmpPretD(Oferta* m1, Oferta* m2);

int cmpDestinatie(Oferta* m1, Oferta* m2);

int cmpDestinatieD(Oferta* m1, Oferta* m2);
/*Sorteaza ofertele dupa pret.*/
BigList* sortPret(BigList* l);

BigList* sortPretD(BigList* l);

/*Sorteaza ofertele alfabetic*/
BigList* sortDestinatie(BigList* l);

BigList* sortDestinatieD(BigList* l);

/*Filtreaza ofertele care au pretul mai mic decat o valoare data*/
Offerte* filterPret(BigList* list, int);

/*Filtreaza ofertele dupa tip*/
Offerte* filterTip(BigList* list, char);

#endif //OOP_LAB2_4_SERVICE_H
