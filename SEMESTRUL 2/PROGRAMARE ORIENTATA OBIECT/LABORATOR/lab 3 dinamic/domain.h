//
// Created by Costi on 06-Mar-24.
//

#ifndef LAB_2_DOMAIN_H
#define LAB_2_DOMAIN_H

typedef struct{
    char tip[20];
    char destinatie[50];
    char data_plecarii[20];
    float pret;
} oferta;

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
oferta creeazaOferta(char *tip, char *destinatie, char *data_plecarii, float pret);

/*
 * Valideaza o oferta.
 *
 * Parametri:
 *   - o: oferta de validat (oferta)
 *
 * Returneaza:
 *   int - 1 daca oferta este valida, 0 altfel
 */
int valideazaOferta(oferta o);

/*
 * Distruge o oferta.
 *
 * Parametri:
 *   - o: oferta de distrus (oferta*)
 */
void distrugeOferta(oferta *o);

#endif //LAB_2_DOMAIN_H