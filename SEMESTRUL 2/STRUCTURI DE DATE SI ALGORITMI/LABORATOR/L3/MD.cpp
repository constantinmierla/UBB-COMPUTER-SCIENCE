//
// Created by Costi on 06-Apr-24.
//
#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;


TValoare NodL::element()
{
    return this->v;
}

NodL* NodL::urmator()
{
    return this->urm;
}

ListaV::ListaV() {
    prim = nullptr;
    this->n = 0;
}

void ListaV::adauga(TValoare v)
{
    NodL* p = prim;
    if (this->prim == nullptr)
    {
        prim = new NodL();
        prim->v = v;
        prim->urm = nullptr;
        this->n++;
        return;
    }

    while (p->urm != nullptr){
        p = p->urm;
    }
    p->urm = new NodL();
    p->urm->v = v;
    p->urm->urm = nullptr;
    this->n++;
}


bool ListaV::sterge(TValoare v)
{
    if (this->prim != nullptr)
    {
        NodL* p = this->prim;
        if (this->prim->v ==v)
        {
            this->prim = this->prim->urm;
            delete p;
            this->n--;
            return true;
        }

        while (p->urm != nullptr)
        {
            if (p->urm->v == v)
            {
                NodL* aux;
                aux = p->urm;
                p->urm = p->urm->urm;
                delete aux;
                this->n--;
                return true;
            }
            p = p->urm;
        }
        return false;
    }
    return false;
}


vector<TValoare> ListaV::cauta()
{
    vector<TValoare> Valori;
    if (this->prim != nullptr)
    {
        NodL* p = this->prim;
        Valori.push_back(p->v);
        while (p->urm != nullptr)
        {
            Valori.push_back(p->urm->v);
            p = p->urm;
        }
    }

    return Valori;
}

bool ListaV::vida() const
{
    if (this->n == 0)
        return true;
    return false;
}

int ListaV::dim()
{
    return this->n;
}

ListaV::~ListaV()
{
    while (prim != nullptr)
    {
        NodL* p = prim;
        prim = prim->urm;
        delete p;
    }

}



Nod::Nod() {
    this->e = make_pair(NULL, nullptr);
    this->urm = nullptr;
}

Telem Nod::element() {
    return this->e;
}

Nod* Nod::urmator() {
    return this->urm;
}

MD::MD() {
    this->n = 0;
    this->prim = nullptr;
}


void MD::adauga(TCheie c, TValoare v) {

    if (this->prim != nullptr)
    {
        Nod* p = this->prim;

        if (p->e.first == c)
        {
            p->e.second->adauga(v);
            this->n++;
            return;
        }

        while (p->urm != nullptr)
        {
            if (p->urm->e.first == c)
            {
                p->urm->e.second->adauga(v);
                this->n++;
                return;
            }
            p = p->urm;
        }
        adaugaCheieNoua(c, v, p);
        this->n++;
    }

    else
    {
        adaugaCheieNoua(c, v, nullptr);
        this->n++;
    }
}

void MD::adaugaCheieNoua(TCheie c, TValoare v, Nod* prec)
{
    Nod* nou = new Nod();
    nou->e.first = c;
    nou->e.second = new ListaV();
    nou->e.second->adauga(v);
    if (prec == nullptr)
    {
        nou->urm = this->prim;
        prim = nou;
    }
    else
    {
        nou->urm = prec->urm;
        prec->urm = nou;
    }

}


bool MD::sterge(TCheie c, TValoare v) {

    if (this->prim != nullptr)
    {
        Nod* p = this->prim;
        if (p->e.first == c)
        {
            if (p->e.second->dim() == 1)
            {
                bool ok = p->e.second->sterge(v);
                if (ok == true)
                {
                    this->n--;
                    stergeCheie(nullptr);
                    return true;
                }
                else
                    return false;
            }

            bool ok = p->e.second->sterge(v);
            if (ok == true)
            {
                this->n--;
                return true;
            }
            else
                return false;
        }

        while (p->urm != nullptr)
        {
            if (p->urm->e.first == c)
            {
                if (p->urm->e.second->dim() == 1)
                {
                    bool ok = p->urm->e.second->sterge(v);
                    if (ok == true)
                    {
                        this->n--;
                        stergeCheie(p);
                        return true;
                    }
                    else
                        return false;
                }
                bool ok = p->urm->e.second->sterge(v);
                if (ok == true)
                {
                    this->n--;
                    return true;
                }
                else
                    return false;
            }
            p = p->urm;
        }
        return false;

    }

    return false;
}

void MD::stergeCheie(Nod* prec)
{
    if (prec == nullptr)
    {
        Nod* sters = this->prim;
        prim = prim->urm;
        sters->e.second->~ListaV();
        delete sters;
    }
    else
    {
        Nod* sters = prec->urm;
        prec->urm = prec->urm->urm;
        sters->e.second->~ListaV();
        delete sters;
    }

}

vector<TValoare> MD::cauta(TCheie c) const {

    vector<TValoare> Valori;
    if(this->prim == nullptr)
        return Valori;

    else
    {
        Nod* p = this->prim;

        if (p->e.first == c)
            return p->e.second->cauta();


        while (p->urm != nullptr)
        {
            if (p->urm->e.first == c)
                return p->urm->e.second->cauta();

            p = p->urm;
        }
    }
    return Valori;
}


int MD::dim() const {
    return this->n;
}


bool MD::vid() const {
    if (this->n == 0)
        return true;
    return false;
}

IteratorMD MD::iterator() const {
    return IteratorMD(*this);
}

vector<TValoare> MD::stergeValoriPentruCheie(TCheie cheie) {
    vector<TValoare> valoriSterse;

    if (this->prim != nullptr) {
        Nod* p = this->prim;
        Nod* prec = nullptr;

        while (p != nullptr) {
            if (p->e.first == cheie) {
                valoriSterse = p->e.second->cauta();

                if (prec == nullptr)
                    stergeCheie(nullptr);
                else
                    stergeCheie(prec);

                break;
            }

            prec = p;
            p = p->urm;
        }
    }

    return valoriSterse;
}

MD::~MD() {

    while (prim != nullptr) {
        Nod* p = prim;
        p->e.second->~ListaV();
        prim = prim->urm;

        delete p;
    }
}

