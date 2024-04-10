//
// Created by Costi on 06-Apr-24.
//
#include <iostream>
#include "IteratorMD.h"
#include "MD.h"
#include <exception>
#include <iterator>
using std::exception;
using namespace std;


IteratorMD::IteratorMD(const MD& _md) : md(_md) {

    curent = md.prim;
    if(curent != nullptr)
        curentL = curent->e.second->prim;
}

TElem IteratorMD::element() const {

    if (valid())
    {
        TCheie c = curent->element().first;
        TValoare v = curentL->element();
        return make_pair(c, v);
    }
    else
        throw exception();

}

bool IteratorMD::valid() const {
    if (curent == nullptr)
        return false;
    else
        return true;
}

void IteratorMD::urmator() {

    if (valid())
    {
        if (curentL->urm == nullptr)
        {
            curent = curent->urmator();
            if(curent != nullptr)
                curentL = curent->e.second->prim;
        }

        else
            curentL = curentL->urm;

    }
    else
        throw exception();

}

void IteratorMD::prim() {
    curent = md.prim;
    if (curent != nullptr)
        curentL = curent->e.second->prim;
}


