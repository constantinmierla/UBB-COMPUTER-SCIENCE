//
// Created by Costi on 11-Mar-24.
//

#include "service.h"
#include <string.h>

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
int adaugaOferta(List *v, char *tip, char *destinatie, char *data_plecarii, float pret)
{
    oferta o = creeazaOferta(tip, destinatie, data_plecarii, pret);
    if(valideazaOferta(o) == 0)
        return 0;

    add(v, o);
    return 1;
}

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
int stergeOferta(List *v, char *tip, char *destinatie, char *data_plecarii)
{
    int poz;
    for (int i = 0; i < size(v); i++)
    {
        if (strcmp(get(v,i).tip, tip) == 0 && strcmp(get(v,i).destinatie, destinatie) == 0
        && strcmp(get(v,i).data_plecarii, data_plecarii) == 0)
        {
            poz = i;
            oferta o = sterge(v, poz);
            destroy(&o);
            return 1;
        }
    }
    return 0;
}

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

List filtruOfertaDestinatie(List *v, char *criteriu)
{
    List listaFiltrata = createEmpty();
    for(int i = 0; i < size(v); i++)
    {
        oferta o = get(v,i);
        if (strcmp(o.destinatie, criteriu) == 0)
            add(&listaFiltrata, creeazaOferta(o.tip,o.destinatie,o.data_plecarii,o.pret));

    }
    return listaFiltrata;
}
List filtruOfertaTip(List *v, char *criteriu)
{
    List listaFiltrata = createEmpty();
    for (int i = 0; i < size(v); i++)
    {
        oferta o = get(v,i);
        if(strcmp(o.tip, criteriu) == 0)
            add(&listaFiltrata, creeazaOferta(o.tip,o.destinatie,o.data_plecarii,o.pret));
    }
}

List filtruOfertaPret(List *v, float criteriu)
{
    List listaFiltrata = createEmpty();
    for (int i = 0; i < size(v); i++)
    {
        oferta o = get(v,i);
        if(o.pret < criteriu)
            add(&listaFiltrata, creeazaOferta(o.tip,o.destinatie,o.data_plecarii,o.pret));
    }
}

/*
 *         for i in range(1, len(lista)):
            element = lista[i]
            ind = i

            while ind > 0 and element < lista[ind - 1]:
                lista[ind] = lista[ind - 1]
                ind = ind - 1

            lista[ind] = element
 */
List sortOfertaPretCrescator(List *v)
{
    List listaSortata = createEmpty();
    List listaN = createEmpty();
    for(int i = 0; i < size(v); i++)
    {
        oferta o = get(v,i);
        /*for(int j = 0; j < size(v); i++)
        {

        }*/
    }
}