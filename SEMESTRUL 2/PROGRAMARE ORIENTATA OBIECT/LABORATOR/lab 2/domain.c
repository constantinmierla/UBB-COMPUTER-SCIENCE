//
// Created by Costi on 06-Mar-24.
//

#include "domain.h"
#include <string.h>

oferta creeazaOferta(char *tip, char *destinatie, char *data_plecarii, float pret)
{
    oferta o;
    strcpy(o.tip, tip);
    strcpy(o.destinatie, destinatie);
    strcpy(o.data_plecarii, data_plecarii);
    o.pret = pret;

    return o;
}

int valideazaOferta(oferta o)
{
    /*
     * validator pentru oferta
     */
    if (o.tip != "munte" || o.tip != "mare" || o.tip != "city break")
        return 0;
    if (strlen(o.destinatie) == 0)
        return 0;
    if (strlen(o.data_plecarii) == 0)
        return 0;
    if (o.pret < 0)
        return 0;
    return 1;
}

void distrugeOferta(oferta *o)
{
    o -> tip[0] = '\0';
    o -> destinatie[0] = '\0';
    o -> data_plecarii[0] = '\0';
    o -> pret = -1;
}
