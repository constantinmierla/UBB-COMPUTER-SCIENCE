#pragma once
#include "MD.h"

class MD;

class IteratorMD
{
    friend class MD;
private:

    ///Θ(1)
    //constructorul primeste o referinta catre Container
    //iteratorul va referi primul element din container
    IteratorMD(const MD& c);

    //contine o referinta catre containerul pe care il itereaza
    const MD& md;

    /* aici e reprezentarea  specifica a iteratorului */
    Nod* curent;
    NodL* curentL;


public:

    ///Θ(1)
    //reseteaza pozitia iteratorului la inceputul containerului
    void prim();

    ///Θ(1)
    //muta iteratorul in container
    // arunca exceptie daca iteratorul nu e valid
    void urmator();

    ///Θ(1)
    //verifica daca iteratorul e valid (indica un element al containerului)
    bool valid() const;

    ///Θ(1)
    //returneaza valoarea elementului din container referit de iterator
    //arunca exceptie daca iteratorul nu e valid
    TElem element() const;


    void avanseazaPasi(int k);

    /*
    Complexitati:
    -caz favorabil = caz mediu = caz defavorabil = Θ(k)
    -caz general: Θ(k)

    */

    /*
    * pre: k este numar intreg, md este multidictionar
    * post: iteratorul refera a k-a pereche din multidictionar
    Subalgoritm avanseazaPasi(MD md, int k)
        Daca k<=0 atunci
            @arunca exceptie
        SfDaca

        Pentru i=0,k executa
            Daca [curentL].urm = NIL atunci
                curent <- [curent].urmator
                Daca curent != NIL atunci
                    curentL <- [[curent].e.second]prim
                SfDaca
            Altfel
                curentL <- [curentL].urm
            SfDaca
            Daca valid == false atunci
                @arunca exceptie
        SfPentru
    SfSubalgoritm

    */

};

