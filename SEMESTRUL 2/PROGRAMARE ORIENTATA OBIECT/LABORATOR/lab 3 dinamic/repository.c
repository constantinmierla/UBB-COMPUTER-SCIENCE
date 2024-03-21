#include "repository.h"
#include <stdlib.h>
#include <stdio.h>

/*Adauga o oferta noua.*/
void addEntitate(Offerte* f, Entitate e)
{
    if (f->dimensiune < f->capacitate)
    {
        f->oferte[f->dimensiune] = e;
        f->dimensiune += 1;
    }
    else
    {
        asiguraCapacitate(f);
        addEntitate(f, e);
    }

}

/*Functie care mareste capacitatea.*/
void asiguraCapacitate(Offerte* f)
{

    Entitate* capacitateNoua = malloc(sizeof(Entitate)*(f->capacitate * 2));
    //copiaza elementele
    for (int i = 0; i < f->dimensiune; i++)
        capacitateNoua[i] = f->oferte[i];

    //dealoca memoria
    free(f->oferte);
    f->oferte = capacitateNoua;
    f->capacitate *= 2;

}

/*Sterge o oferta*/
int deleteEntitate(Offerte* f, int id)
{
    int i = 0;
    int ok = 1;
    while(i<f->dimensiune)
    {
        Oferta* p = get(f, i);
        if (p->id == id)
        {
            destroyOferta(p);
            for (int j = i; j < f->dimensiune - 1; j++)
                f->oferte[j] = f->oferte[j + 1];
            f->dimensiune -= 1;
            ok = 0;
        }

        i++;
    }

    return ok;
}


/*Functie care creeaza o entitate noua si returneaza pointerul la entitatea respectiva.*/
Offerte* creeazaOfferte()
{

    Offerte* f = malloc(sizeof(Offerte));
    f->dimensiune = 0;
    f->capacitate = 2;
    f->oferte = malloc(sizeof(Entitate) * f->capacitate);

    return f;
}

/*Primeste un pointer la entitate si dealoca memoria ocupata de entitate.*/
void destroyOfferte(Offerte* f)
{
    for (int i = 0; i < f->dimensiune; i++)
        destroyOferta(f->oferte[i]);

    free(f->oferte);
    free(f);

}
/*Functie care face update
 Primeste un pointer cu caracteristicile actualizate, distruge
 vechi si il pune pe cel actualizat.
*/
int updateOferta(Offerte* f, Oferta* m)
{
    int ok = -1;
    for (int i=0; i < f->dimensiune; i++)
    {
        Oferta* p = get(f, i);
        if (p->id == m->id)
        {
            destroyOferta(set(f,i,m));
            ok = 0;
        }
    }
    return ok;
}
/*Functie care primeste un int -id- si returneaza pozitia pe care se afla elementul sau -1 in caz contrar*/
int cauta(Offerte* f, int id)
{

    for (int i = 0; i < f->dimensiune; i++)
    {
        Oferta* p = get(f, i);
        if (p->id == id)
            return i;

    }
    return -1;
}


/*Functie care returneaza elementul de pe o pozitie data*/
Entitate get(Offerte* f, int i)
{
    return f->oferte[i];
}

/*Functie care pune pe o pozitie data o entitate data si returneaza fostul element de pe pozitia data.*/
Entitate set(Offerte* f, int poz, Entitate e)
{

    Entitate rez = f->oferte[poz];
    f->oferte[poz] = e;
    return rez;
}

//Functie copy
Offerte* copy(Offerte* p)
{
    Offerte* f = malloc(sizeof(Offerte));
    f->dimensiune = p->dimensiune;
    f->capacitate = p->capacitate;
    f->oferte = malloc(sizeof (Oferta)*p->dimensiune);
    for(int i=0; i< p->dimensiune;i++)
        f->oferte[i] = copyOferta(p->oferte[i]);

    return f;
}