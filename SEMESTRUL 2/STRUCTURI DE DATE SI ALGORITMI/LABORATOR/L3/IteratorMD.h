//
// Created by Costi on 06-Apr-24.
//
#pragma once
#include "MD.h"

class MD;

class IteratorMD
{
    friend class MD;
private:

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    //constructorul primeste o referinta catre Container
    //iteratorul va referi primul element din container
    IteratorMD(const MD& c);

    //contine o referinta catre containerul pe care il itereaza
    const MD& md;

    /* aici e reprezentarea  specifica a iteratorului */
    Nod* curent;
    NodL* curentL;


public:

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    //reseteaza pozitia iteratorului la inceputul containerului
    void prim();

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    //muta iteratorul in container
    // arunca exceptie daca iteratorul nu e valid
    void urmator();

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    //verifica daca iteratorul e valid (indica un element al containerului)
    bool valid() const;

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    //returneaza valoarea elementului din container referit de iterator
    //arunca exceptie daca iteratorul nu e valid
    TElem element() const;

};

