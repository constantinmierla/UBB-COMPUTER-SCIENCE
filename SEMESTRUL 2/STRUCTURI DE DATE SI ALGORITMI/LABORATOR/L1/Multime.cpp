#include "Multime.h"
#include "IteratorMultime.h"

// Relatia de ordine între elementele mulțimii.
// Funcția rel returneaza true dacă e1 este mai mic sau egal cu e2, altfel returneaza false.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(1) - Operație simpla de comparare.
// Complexitate spațiu: Θ(1) - Funcție de timp constant și nu consumă memorie suplimentară.
bool rel(TElem e1, TElem e2)
{
    return e1 <= e2;
}

// Constructorul clasei Multime.
// Inițializeaza dimensiunea si capacitatea mulțimii, alocand memorie pentru vectorul de elemente.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(1) - Inițializare si alocare constanta de memorie.
// Complexitate spațiu: Θ(1) - Alocare constanta de memorie pentru vectorul de elemente.
Multime::Multime() {
    dimensiune = 0;
    capacitatea = 1;
    vector = new TElem[capacitatea];
}

// Destructorul clasei Multime.
// Eliberează memoria alocată pentru vectorul de elemente.
// Complexitate timp: Θ(1) - Eliberare constantă de memorie.
// Complexitate spațiu: Θ(1) - Nu consuma memorie suplimentara.
Multime::~Multime() { delete[] vector; }

// Redimensioneaza capacitatea mulțimii dublând dimensiunea.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(n) - Parcurgere lineara a vectorului de elemente.
// Complexitate spatiu: Θ(n) - Alocare si copiere a unui nou vector cu dimensiunea dubla.
void Multime::resize_append() {
    capacitatea *= 2;
    TElem *new_items = new TElem[capacitatea];

    for (int i = 0; i < dimensiune; ++i) {
        new_items[i] = vector[i];
    }

    delete[] vector;
    vector = new_items;
}

// Redimensioneaza capacitatea multimii jumatatind dimensiunea.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(n) - Parcurgere lineara a vectorului de elemente.
// Complexitate spațiu: Θ(n) - Alocare și copiere a unui nou vector cu dimensiunea jumatatita.
void Multime::resize_delete() {
    capacitatea /= 2;
    TElem *new_items = new TElem[capacitatea];

    for (int i = 0; i < dimensiune; ++i) {
        new_items[i] = vector[i];
    }

    delete[] vector;
    vector = new_items;
}

// Adauga un element nou in mulțime.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: O(n) - Parcurgere a cel mult n elemente.
// Complexitate spațiu: Θ(1) - Operatii de adaugare sau eliminare a unui singur element.
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

// Sterge un element din mulțime.
// Complexitate defavorabila : Θ(n) - Parcurgere a cel mult n elemente.
// Complexitate favorabila : Θ(log n) - Elementul cautat este nu exista.
// => Complexitate timp total: O(n) - Parcurgere a cel mult n elemente.
// Complexitate spațiu: Θ(1) - Operații de adăugare sau eliminare a unui singur element.
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

// Caută un element in mulțime.
// Funcția cauta utilizeaza o cautare binara intr-un vector sortat pentru a determina dacă elementul dat este prezent în mulțime.
// Complexitate defavorabila : Θ(n) - Parcurgere a cel mult n elemente.
// Complexitate favorabila : Θ(1) - Elementul cautat este cel din mijlocul vectorului.
//=> Complexitate totala timp: O(log n) - Cautare binara intr-un vector sortat de dimensiune n.
// Complexitate spațiu: Θ(1) - Nu consuma memorie suplimentara in afara variabilelor locale.
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

// Returneaza dimensiunea multimii.
// Funcția dim intoarce numarul de elemente din mulțime.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(1) - Operatie constanta de returnare a dimensiunii.
// Complexitate spațiu: Θ(1) - Nu consuma memorie suplimentara in afara valorii returnate.
int Multime::dim() const {
    return dimensiune;
}

// Verifica daca mulțimea este vida.
// Funcția vida returneaza true daca mulțimea este vida, altfel returneaza false.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(1) - Operatie constanta de verificare a dimensiunii.
// Complexitate spațiu: Θ(1) - Nu consuma memorie suplimentara in afara valorii returnate.
bool Multime::vida() const {
    return dimensiune == 0;
}

// Adauga toate elementele din multimea b in multimea curenta.
// Complexitate defavorabila = Θ(n*m) - fiecare element este distinct
// Complexitate favorabila = Θ(m) - multimile au aceleasi elemente
// Complexitate timp total: O(n*m) - n este nr de elemente din multimea curenta, m nr de elemente pe care le adaugam.
// Complexitate spatiu: Θ(1) - Nu consuma memorie suplimentara in afara variabilelor locale.
void Multime::reuniune(const Multime &b) {
    for (int i = 0; i < b.dim(); ++i) {
        adauga(b.vector[i]);
    }
}
// Returneaza un iterator pentru multime.
// Funcția iterator intoarce un iterator inițializat cu mulțimea curenta.
// Complexitate defavorabila = Complexitate favorabila = Complexitate timp total: Θ(1) - Initializare a unui iterator.
// Complexitate spatiu: Θ(1) - Nu consuma memorie suplimentara in afara iteratorului returnat.
IteratorMultime Multime::iterator() const {
    return IteratorMultime(*this);
}

/*
 * PSEUDOCOD ALGORITM Reuniune
 *
 * Reuniune(b: Multime)
     * pentru i <- 0 pana la dimensiunea b executa:
     *     adauga(b.vector[i])
     * sfarsit pentru
 *
 */