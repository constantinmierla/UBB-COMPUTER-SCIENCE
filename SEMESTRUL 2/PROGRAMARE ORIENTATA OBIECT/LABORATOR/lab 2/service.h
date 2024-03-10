//
// Created by Costi on 11-Mar-24.
//
#include "repository.h"
#ifndef LAB_2_SERVICE_H
#define LAB_2_SERVICE_H

#endif //LAB_2_SERVICE_H

int adaugaOferta(List *v, char *tip, char *destinatie, char *data_plecarii, float pret);

int stergeOferta(List *v, char *tip, char *destinatie, char *data_plecarii);

int modificaOferta(List *v, char *tip, char *destinatie, char *data_plecarii, float pret_nou);

List filtruOferta(List *v, int criteriu, char *nume);

List sortOfertaPret();