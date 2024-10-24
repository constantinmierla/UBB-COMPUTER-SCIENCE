#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>
#include <cmath>

// Verifica daca un numar este prim.
// Complexitate: Theta(sqrt(x)) pentru best case worst case si total case.
bool prim(int x) {
    int d = 2;
    while (d <= sqrt(x)) {
        if (x % d == 0) {
            return false;
        }
        d++;
    }
    return true;
}

// Gaseste urmatorul numar prim mai mare decat cel dat.
// Complexitate: Theta(n) pentru best case, worst case si total case, unde n este numarul urmatorului numar prim.
int next_prime(int number) {
    int next_prime_number = number * 2;

    if (prim(next_prime_number))
        return next_prime_number;

    while (!prim(next_prime_number)) {
        next_prime_number++;
    }

    return next_prime_number;
}

// Constructorul care initializeaza o multime noua.
// Complexitate: Theta(n) pentru best case, worst case si total case, unde n este capacitatea initiala a multimii.
Multime::Multime() {
    capacitate = 17;
    dimensiune = 0;
    elemente = new TElem[capacitate];
    for (int i = 0; i < capacitate; i++) {
        elemente[i] = EMPTY_POSITION;
    }
}

// Functia care adauga un element in multime.
// Complexitate: Theta(1) pentru best case si Theta(n) pentru worst case=> O(n) total case.n este dimensiunea multimii
bool Multime::adauga(TElem elem) {
    if (cauta(elem))
        return false;
    int poz = this->doubleHash(elem);
    if (poz != -1) {
        this->elemente[poz] = elem;
        this->dimensiune++;
        return true;
    } else {
        this->resize();
        poz = this->doubleHash(elem);
        this->elemente[poz] = elem;
        this->dimensiune++;
        return true;
    }
    return false;
}

// Functia care sterge un element din multime.
// Complexitate: Theta(1) pentru best case, Theta(n) pentru worst case, O(n) pentru total case. n este capacitatea multimii
bool Multime::sterge(TElem elem) {
    int p = 0;
    int poz;
    int aux = abs(elem);
    while (p < this->capacitate) {
        poz = (this->hashFunction1(aux) + p * this->hashFunction2(aux)) % this->capacitate;
        if (this->elemente[poz] == EMPTY_POSITION)
            return false;
        else if (this->elemente[poz] != elem)
            p++;
        else if (this->elemente[poz] == elem) {
            this->elemente[poz] = DELETED_POSITION;
            this->dimensiune--;
            return true;
        }
    }
    return false;
}

// Functia care verifica daca un anumit element exista in multime.
// Complexitate: Theta(1) pentru best case, Theta(n) pentru worst case si O(n) pentru total case. n este capacitatea multimii
bool Multime::cauta(TElem elem) const {
    int p = 0;
    int poz;
    int aux = abs(elem);
    while (p < this->capacitate) {
        poz = (this->hashFunction1(aux) + p * this->hashFunction2(aux)) % this->capacitate;
        if (this->elemente[poz] == EMPTY_POSITION)
            return false;
        else if (this->elemente[poz] != elem)
            p++;
        else if (this->elemente[poz] == elem)
            return true;
    }
    return false;
}

// Functia care returneaza dimensiunea multimii (numarul de elemente).
// Complexitate: Theta(1) pentru best case, worst case si total case.
int Multime::dim() const {
    return dimensiune;
}

// Functia care verifica daca multimea este vida.
// Complexitate: Theta(1) pentru best case, worst case si total case.
bool Multime::vida() const {
    return dimensiune == 0;
}

// Redimensioneaza multimea la o capacitate mai mare.
// Complexitate: Theta(n) pentru best case, worst case si total case, unde n este dimensiunea multimii.
void Multime::resize() {
    TElem* aux = new TElem[dimensiune];
    int j = 0;
    for (int i = 0; i < this->capacitate; i++) {
        if (this->elemente[i] != EMPTY_POSITION && this->elemente[i] != DELETED_POSITION) {
            aux[j] = this->elemente[i];
            j++;
        }
    }
    this->capacitate = next_prime(this->capacitate);
    this->elemente = new TElem[this->capacitate];
    int poz;
    for (int i = 0; i < this->capacitate; i++) {
        this->elemente[i] = EMPTY_POSITION;
    }
    for (int i = 0; i < j; i++) {
        poz = this->doubleHash(aux[i]);
        this->elemente[poz] = aux[i];
    }
}

// Destructorul care elibereaza memoria alocata pentru multime.
// Complexitate: Theta(1) pentru best case, worst case si total case.
Multime::~Multime() {
    delete[] elemente;
}

// Functia care returneaza un iterator pentru multime.
IteratorMultime Multime::iterator() const {
    return IteratorMultime(*this);
}
