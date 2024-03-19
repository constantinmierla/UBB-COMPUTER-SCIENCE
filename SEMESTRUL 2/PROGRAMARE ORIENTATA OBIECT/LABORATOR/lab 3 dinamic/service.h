//
// Created by Costi on 11-Mar-24.
//
#ifndef LAB_2_SERVICE_H
#define LAB_2_SERVICE_H
#include "domain.h"
#include "repository.h"
#endif //LAB_2_SERVICE_H

/*
 * Adauga o noua oferta in lista de oferte.
 *
 * Parametri:
 *   - v: lista de oferte in care se adauga oferta (List*)
 *   - tip: tipul ofertei (char*)
 *   - destinatie: destinatia ofertei (char*)
 *   - data_plecarii: data plecarii (char*)
 *   - pret: pretul ofertei (float)
 *
 * Returneaza:
 *   int - 1 daca oferta a fost adaugata cu succes, altfel 0
 */
int adaugaOferta(List *v, char *tip, char *destinatie, char *data_plecarii, float pret);

/*
 * Sterge o oferta din lista de oferte.
 *
 * Parametri:
 *   - v: lista de oferte din care se sterge oferta (List*)
 *   - tip: tipul ofertei de sters (char*)
 *   - destinatie: destinatia ofertei de sters (char*)
 *   - data_plecarii: data plecarii a ofertei de sters (char*)
 *
 * Returneaza:
 *   int - 1 daca oferta a fost stearsa cu succes, altfel 0
 */
int stergeOferta(List *v, char *tip, char *destinatie, char *data_plecarii);

/*
 * Modifica pretul unei oferte din lista de oferte.
 *
 * Parametri:
 *   - v: lista de oferte in care se modifica pretul (List*)
 *   - tip: tipul ofertei de modificat (char*)
 *   - destinatie: destinatia ofertei de modificat (char*)
 *   - data_plecarii: data plecarii a ofertei de modificat (char*)
 *   - pret_nou: noul pret pentru oferta (float)
 *
 * Returneaza:
 *   int - 1 daca oferta a fost modificata cu succes, altfel 0
 */
int modificaOferta(List *v, char *tip, char *destinatie, char *data_plecarii, float pret_nou);

List filtruOfertaDestinatie(List *v, char *criteriu);

List filtruOfertaTip(List *v, char *criteriu);

List filtruOfertaPret(List *v, float criteriu);

List sortOfertaPretCrescator(List *v);