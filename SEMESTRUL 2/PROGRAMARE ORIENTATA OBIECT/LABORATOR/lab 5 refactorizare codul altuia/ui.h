/*
#ifndef OOP_LAB2_4_UI_H
#define OOP_LAB2_4_UI_H

#endif //OOP_LAB2_4_UI_H
*/
#include "service.h"
#include "repository.h"
#include "domain.h"

/*Citeste atributele unui medicament si il adauga in farmacie.*/
void readOfe(BigList* list);

/*Afiseaza toata farmacia*/
void printOfferte(BigList* list);

/*sterge un medicament*/
void deleteOfe(BigList* list);

/*Modifica un medicament */
void updateOfe(BigList* list);

void sortare(BigList *list);

void destroy(BigList *list);

/*Afiseaza medicamentele dupa filtrare dupa stoc*/
void filtrarePret(BigList* list);

/*Afiseaza medicamentele dupa filtrare dupa nume*/
void filtrareTip(BigList* list);

void run();