//
// Created by Costi on 06-Mar-24.
//

#ifndef LAB_2_DOMAIN_H
#define LAB_2_DOMAIN_H

#endif //LAB_2_DOMAIN_H

typedef struct{
    char tip[20];
    char destinatie[50];
    char data_plecarii[20];
    float pret;
} oferta;

oferta creeazaOferta(char *tip, char *destinatie, char *data_plecarii, float pret);

int valideazaOferta(oferta o);

void distrugeOferta(oferta *o);