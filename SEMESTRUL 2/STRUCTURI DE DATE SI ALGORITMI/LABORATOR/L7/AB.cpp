#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>

// Theta(1)
AB::AB() {
    this->radacina = NULL;
}

/// caz favoranil : Theta(1)
/// caz defavorabil : Theta(n)
/// caz mediu : Theta(n)
/// overall case : O(n)
AB::AB(const AB& ab) {
    this->radacina = copiere(ab.radacina);
}

// Theta(1)
AB::AB(TElem e){
    this->radacina = new Nod(e, NULL, NULL);
}

/// caz favoranil : Theta(1)
/// caz defavorabil : Theta(n)
/// caz mediu : Theta(n)
/// overall case : O(n)
AB::AB(const AB& st, TElem e, const AB& dr){
    this->radacina = new Nod(e, copiere(st.radacina), copiere(dr.radacina));
}

/// caz favoranil : Theta(1)
/// caz defavorabil : Theta(n)
/// caz mediu : Theta(n)
/// overall case : O(n)
PNod AB::copiere(PNod p) const {
    if (p != NULL) {
        //creez radacina
        PNod pNew = new Nod(p->element, NULL, NULL);
        pNew->st = copiere(p->st);
        pNew->dr = copiere(p->dr);
        return pNew;
    }
    return NULL;
}

/// caz favoranil : Theta(1)
/// caz defavorabil : Theta(n)
/// caz mediu : Theta(n)
/// overall case : O(n)
void AB::distrugeSubarbori(PNod p) {
    if (p != NULL) {
        distruge(p->st);
        distruge(p->dr);
    }
}

/// caz favoranil : Theta(1)
/// caz defavorabil : Theta(n)
/// caz mediu : Theta(n)
/// overall case : O(n)
void AB::distruge(PNod p) {
    if (p != NULL) {
        distruge(p->st);
        distruge(p->dr);
        delete p;
    }
}

/// caz favoranil : Theta(1)
/// caz defavorabil : Theta(n)
/// caz mediu : Theta(n)
/// overall case : O(n)
void AB::adaugaSubSt(const AB& st){
    if (this->vid())
        throw(exception());
    // distrug vechii subarbori ai subarborelui stang
    distrugeSubarbori(this->radacina->st);
    //copiez noul subarbore
    this->radacina->st = copiere(st.radacina);
}

/// caz favoranil : Theta(1)
/// caz defavorabil : Theta(n)
/// caz mediu : Theta(n)
/// overall case : O(n)
void AB::adaugaSubDr(const AB& dr){
    if (this->vid())
        throw(exception());
    // distrug vechii subarbori ai subarborelui drept
    distrugeSubarbori(this->radacina->dr);
    //copiez noul subarbore
    this->radacina->dr = copiere(dr.radacina);
}

// Theta(1)
TElem AB::element() const{
    if (this->vid())
        throw(exception());
    return this->radacina->element;
}

// Theta(1)
AB AB::stang() const{
    if (this->vid())
        throw(exception());
    AB ab;
    ab.radacina = copiere(this->radacina->st);
    return ab;
}

// Theta(1)
AB AB::drept() const{
    if (this->vid())
        throw(exception());
    AB ab;
    ab.radacina = copiere(this->radacina->dr);
    return ab;
}

/// caz favoranil : Theta(1)
/// caz defavorabil : Theta(n)
/// caz mediu : Theta(n)
/// overall case : O(n)
AB::~AB() {
    distruge(this->radacina);
}

// Theta(1)
bool AB::vid() const{
    return this->radacina == NULL;
}

// Theta(1)
IteratorAB* AB::iterator(string s) const {
    if (s=="preordine")
        return new IteratorPreordine(*this);
    if (s=="inordine")
        return new IteratorInordine(*this);
    if (s=="postordine")
        return new IteratorPostordine(*this);
    if (s=="latime")
        return new IteratorLatime(*this);
    return nullptr;
};

/*
 * maxim()
    dacă arborele este vid
        arunca exceptie

    maxi <- valoarea elementului din radacina

    coada q
    adauga radacina in q

    cat timp q nu este goala
        aux <- q.front()
        q.pop()

        daca aux.st nu este NULL
            adauga aux.st în q

        daca aux.dr nu este NULL
            adauga aux.dr în q

        daca aux.element > maxi
            maxi <- aux.element

    return maxi
 */
/// gaseste si returneaza valoarea maxima din arbore
/// Complexitate :  Theta(n)
/// caz favoranil : Theta(1) daca n e 1
/// caz defavorabil : Theta(n)
/// caz mediu : Theta(n)
/// overall case : Theta(n)
int AB::maxim()
{
    if (this->vid())
        throw(exception());

    // initializam max cu radacina
    TElem maxi = radacina->element;
    // parcurgem arborele prin latime
    queue<PNod> q;
    // se adauga radacina in coada
    q.push(radacina);

    // incepem bfs ul
    while (!q.empty())
    {
        PNod aux = q.front();
        q.pop();

        if (aux->st != NULL)
            q.push(aux->st);
        if (aux->dr != NULL)
            q.push(aux->dr);

        if (aux->element > maxi)
            maxi = aux->element;
    }

    return maxi;
}