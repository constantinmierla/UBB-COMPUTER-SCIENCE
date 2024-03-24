#include "Multime.h"

#include "IteratorMultime.h"

// o posibila relatie
bool rel(TElem e1, TElem e2)
{
    return e1 <= e2;
}

Multime::Multime() {
    dimensiune = 0;
    capacitatea = 1;
    vector = new TElem[capacitatea];
}

Multime::~Multime() { delete[] vector; }

void Multime::resize_append() {
    capacitatea *= 2;
    TElem *new_items = new TElem[capacitatea];

    for (int i = 0; i < dimensiune; ++i) {
        new_items[i] = vector[i];
    }

    delete[] vector;
    vector = new_items;
}

void Multime::resize_delete() {
    capacitatea /= 2;
    TElem *new_items = new TElem[capacitatea];

    for (int i = 0; i < dimensiune; ++i) {
        new_items[i] = vector[i];
    }

    delete[] vector;
    vector = new_items;
}

bool Multime::adauga(TElem elem) {
    if (cauta(elem)) return false;

    if (dimensiune == capacitatea) {
        resize_append();
    }

    int poz = dimensiune - 1;
    while (!rel(vector[poz], elem) && poz >= 0) {
        vector[poz + 1] = vector[poz];
        poz--;
    }

    vector[poz + 1] = elem;
    dimensiune++;

    return true;
}

bool Multime::sterge(TElem elem) {
    if (!cauta(elem)) return false;

    if (dimensiune == capacitatea / 4) {
        resize_delete();
    }

    for (int i = 0; i < dimensiune; ++i) {
        if (vector[i] == elem) {
            for (int j = i; j < dimensiune; ++j) {
                vector[j] = vector[j + 1];
            }
            break;
        }
    }

    dimensiune--;
    return true;
}

bool Multime::cauta(TElem elem) const {
    int left = 0;
    int right = dimensiune - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (vector[mid] == elem) {
            return true;
        } else if (!rel(vector[mid], elem)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return false;
}

int Multime::dim() const {
    return dimensiune;
}

bool Multime::vida() const {
    return dimensiune == 0;
}

IteratorMultime Multime::iterator() const {
    return IteratorMultime(*this);
}