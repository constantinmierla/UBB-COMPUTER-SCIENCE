//
// Created by Costi on 24-Mar-24.
//

#include "IteratorMultime.h"
#include "Multime.h"

// Constructorul clasei IteratorMultime.
// Inițializeaza iteratorul pentru multimea data și seteaza indexul la prima poziție.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(1) - Initializare a unui iterator.
// Complexitate spatiu: Θ(1) - Nu consuma memorie suplimentara in afara variabilelor locale.

IteratorMultime::IteratorMultime(const Multime &m) : mult(m) {
    prim();
}

// Returneaza elementul curent din iterație.
// Functia element returneaza elementul curent la care indica iteratorul.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(1) - Acces constant la elementul curent.
// Complexitate spatiu: Θ(1) - Nu consuma memorie suplimentara in afara valorii returnate.

TElem IteratorMultime::element() const {
    return mult.vector[index];
}

// Verifică dacă iteratorul este valid.
// Funcția valid returnează true dacă iteratorul este valid (în limitele mulțimii), altfel returneaza false.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(1) - Verificare constantă a validității iteratorului.
// Complexitate spațiu: Θ(1) - Nu consumă memorie suplimentară în afara valorii returnate.

bool IteratorMultime::valid() const {
    return index < mult.dim();
}

// Avansează iteratorul la următorul element din mulțime.
// Funcția urmator avansează iteratorul la următorul element din mulțime.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(1) - Avansare constantă la următorul element.
// Complexitate spațiu: Θ(1) - Nu consumă memorie suplimentară în afara variabilelor locale.

void IteratorMultime::urmator() {
    index += 1;
}

// Repune iteratorul la începutul mulțimii.
// Funcția prim resetează indexul iteratorului la prima poziție din mulțime.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(1) - Resetare constantă a indexului iteratorului.
// Complexitate spațiu: Θ(1) - Nu consumă memorie suplimentară în afara variabilelor locale.

void IteratorMultime::prim() {
    index = 0;
}
