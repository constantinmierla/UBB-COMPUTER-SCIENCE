#include "IteratorMultime.h"
#include "Multime.h"
#include <stdexcept>

#define NOT_VALID 9900990

// Constructorul care initializeaza un iterator pentru o multime data.
// Complexitate: Theta(n) pentru best case, worst case si total case, unde n este capacitatea multimii.
IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
    this->pozitie_curenta = 0;
    if ((this->element() == EMPTY_POSITION || this->element() == DELETED_POSITION) && this->pozitie_curenta < multime.get_capacitate())
        while ((this->element() == EMPTY_POSITION || this->element() == DELETED_POSITION) && this->pozitie_curenta < multime.get_capacitate()) {
            this->pozitie_curenta++;
        }
    if (this->pozitie_curenta >= multime.get_capacitate())
        this->pozitie_curenta = NOT_VALID;
}

// Muta iteratorul la prima pozitie valida din multime.
// Complexitate: Theta(n) pentru best case, worst case si total case, unde n este capacitatea multimii.
void IteratorMultime::prim() {
    pozitie_curenta = 0;
    if ((this->element() == EMPTY_POSITION || this->element() == DELETED_POSITION) && pozitie_curenta < multime.get_capacitate())
        while ((this->element() == EMPTY_POSITION || this->element() == DELETED_POSITION) && pozitie_curenta < multime.get_capacitate()) {
            pozitie_curenta++;
        }
    if (this->pozitie_curenta >= multime.get_capacitate())
        this->pozitie_curenta = NOT_VALID;
}

// Avanseaza iteratorul la urmatoarea pozitie valida din multime.
// Complexitate: Theta(n) pentru best case, worst case si total case, unde n este capacitatea multimii.
void IteratorMultime::urmator() {
    if (!valid())
        throw std::runtime_error("bad");
    pozitie_curenta++;
    if ((this->element() == EMPTY_POSITION || this->element() == DELETED_POSITION) && pozitie_curenta < multime.get_capacitate())
        while ((this->element() == EMPTY_POSITION || this->element() == DELETED_POSITION) && pozitie_curenta < multime.get_capacitate()) {
            pozitie_curenta++;
        }
    if (pozitie_curenta >= multime.get_capacitate())
        pozitie_curenta = NOT_VALID;
}

// Returneaza elementul curent din multime.
// Complexitate: Theta(1) pentru best case, worst case si total case.
TElem IteratorMultime::element() const {
    if (valid())
        return multime.get_elemente()[pozitie_curenta];
    else
        return -1;
}

// Verifica daca iteratorul este valid.
// Complexitate: Theta(1) pentru best case, worst case si total case.
bool IteratorMultime::valid() const {
    if (this->pozitie_curenta != NOT_VALID)
        return true;
    return false;
}
/*
 * anterior()
    daca iteratorul nu este valid
        arunca o excepție

    daca pozitia curenta este 0
        iteratorul devine nevalid
        return

    poziție_temporara <- poziția curenta - 1

    cat timp poziția_temporară >= 0 și elementul de la poziția_temporară este EMPTY_POSITION sau DELETED_POSITION
        scade poziția_temporara

    dacă poziția_temporara < 0
        iteratorul devine nevalid
    altfel
        muta iteratorul la pozitia_temporara
 */
//Muta iteratorul la o pozitie valida anterioara din multime.
//Complexitate: Theta(1) pentru best case, Theta(n) pentru worst case => O(n) total case. unde n este dimensiunea multimii.
void IteratorMultime::anterior() {
    if (!valid())
        throw std::runtime_error("bad");

    if (pozitie_curenta == 0) {
        pozitie_curenta = NOT_VALID;
        return;
    }

    int pozitie_temporara = pozitie_curenta - 1;
    while ((multime.get_elemente()[pozitie_temporara] == EMPTY_POSITION || multime.get_elemente()[pozitie_temporara] == DELETED_POSITION) && pozitie_temporara >= 0) {
        pozitie_temporara--;
    }

    if (pozitie_temporara < 0) {
        pozitie_curenta = NOT_VALID;
    } else {
        pozitie_curenta = pozitie_temporara;
    }
}
