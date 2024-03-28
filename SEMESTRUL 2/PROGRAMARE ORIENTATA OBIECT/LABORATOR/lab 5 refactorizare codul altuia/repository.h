//#pragma once
#ifndef LAB_2_REPOSITORY_H
#define LAB_2_REPOSITORY_H
#include "domain.h"
/*Creeaza o entitate*/
typedef void* Entitate;

typedef void(*DestroyFn)(Entitate);
typedef Entitate(*CopyFn)(Entitate);

typedef struct {
    Entitate* oferte;
    int dimensiune;
    int capacitate;
    DestroyFn destroy;
    CopyFn copy;
}Offerte;

/*Adauga o oferta noua.*/
void addEntitate(Offerte*, Entitate);

/* Sterge o entitate cu id-ul dat */
int deleteEntitate(Offerte*, int);

/*Dubleaza capacitatea vectorului*/
void asiguraCapacitate(Offerte*);

/* Creeaza o Oferta noua */
Offerte* creeazaOfferte();

/* Sterge Oferta */
void destroyOfferte(Offerte*);

/* Modifica oferta */
int updateOferta(Offerte*, Oferta*);

/* Returneaza entitatea de pe o pozitie data */
Entitate get(Offerte*, int);

/* Pune pe o pozitie data Entitatea data.*/
Entitate set(Offerte*, int, Entitate);

/*Cauta o oferta cu un id dat*/
int cauta(Offerte*, int);

/*Creeaza o copie la oferta data*/
Offerte* copy(Offerte*);

#endif
