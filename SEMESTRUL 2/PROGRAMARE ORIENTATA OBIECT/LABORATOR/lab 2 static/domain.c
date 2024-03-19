//
// Created by Costi on 06-Mar-24.
//

#include "domain.h"
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
oferta creeazaOferta(char *tip, char *destinatie, char *data_plecarii, float pret)
{
    oferta o;
    strcpy(o.tip, tip);
    strcpy(o.destinatie, destinatie);
    strcpy(o.data_plecarii, data_plecarii);
    o.pret = pret;

    return o;
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
int valideazaOferta(oferta o)
{
    /*
     * validator pentru oferta
     */
    char tipp[50];
    strcpy(tipp, o.tip);
    if ((strcmp(tipp,"munte") != 0) && (strcmp(tipp , "mare") != 0) && (strcmp(tipp, "city break") != 0))
        return 0;
    if (strlen(o.destinatie) == 0)
        return 0;
    if (strlen(o.data_plecarii) == 0)
        return 0;
    if (o.pret < 0)
        return 0;

    return 1;
}

/*
 * Distruge o oferta.
 *
 * Parametri:
 *   - o: oferta de distrus (oferta*)
 */
void distrugeOferta(oferta *o)
{
    o -> tip[0] = '\0';
    o -> destinatie[0] = '\0';
    o -> data_plecarii[0] = '\0';
    o -> pret = -1;
}
