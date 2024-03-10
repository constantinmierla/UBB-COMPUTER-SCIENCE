//
// Created by Costi on 11-Mar-24.
//

#include "service.h"
#include <string.h>

int adaugaOferta(List *v, char *tip, char *destinatie, char *data_plecarii, float pret)
{
    oferta o = creeazaOferta(tip, destinatie, data_plecarii, pret);
    if(valideazaOferta(o) == 0)
        return 0;

    add(v, o);
    return 1;
}

int stergeOferta(List *v, char *tip, char *destinatie, char *data_plecarii)
{
    int poz;
    for (int i = 0; i < size(v); i++)
    {
        if (strcmp(get(v,i).tip, tip) == 0 && strcmp(get(v,i).destinatie, destinatie) == 0
        && strcmp(get(v,i).data_plecarii, data_plecarii) == 0)
        {
            poz = i;
            oferta o = delete(v, poz);
            destroy(&o);
            return 1;
        }
    }
    return 0;
}

int modificaOferta(List *v, char *tip, char *destinatie, char *data_plecarii, float pret_nou)
{
    oferta o = creeazaOferta(tip, destinatie, data_plecarii, pret_nou);
    if (valideazaOferta(o) == 0)
        return 0;
    int sters = stergeOferta(v,tip,destinatie,data_plecarii);
    if (sters == 0)
        return 0;
    else
        adaugaOferta(v,tip,destinatie,data_plecarii,pret_nou);
    return 1;
}

List filtruOferta(List *v, int criteriu, char *nume)// de vazut cum filtrez eu
{
    List listaFiltrata = createEmpty();
    for (int i = 0; i < size(v); i++) {
        oferta o = get(v, i);
        if (criteriu == 1 && o.destinatie == *nume)
            add(&listaFiltrata, creeazaOferta(o.tip, o.destinatie, o.data_plecarii, o.pret));
        else {
            if (criteriu == 2 && o.tip == *nume)
                add(&listaFiltrata, creeazaOferta(o.tip, o.destinatie, o.data_plecarii, o.pret));
            else {
                if (criteriu == 3 && o.pret == *nume) //aici nu-i ok probabil refac separat
                    add(&listaFiltrata, creeazaOferta(o.tip, o.destinatie, o.data_plecarii, o.pret));
            }
        }
    }
    return listaFiltrata;
}

List sortOfertaPret()
{

}