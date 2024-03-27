//
// Created by Costi on 24-Mar-24.
//

#ifndef L1_MULTIME_H
#define L1_MULTIME_H
typedef int TElem;

typedef bool (*Relatie)(TElem, TElem);

// in implementarea operatiilor se va folosi functia (relatia) rel (de ex,
// pentru <=)
//  va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

class Multime {
    friend class IteratorMultime;

private:
    /* aici e reprezentarea */
    TElem *vector;
    int dimensiune;
    int capacitatea;

    void resize_append();
    void resize_delete();

public:
    // constructorul implicit
    Multime();

    // adauga un element in multime
    // returneaza adevarat daca elementul a fost adaugat (nu exista deja in
    // multime)
    bool adauga(TElem e);

    // sterge un element din multime
    // returneaza adevarat daca elementul a existat si a fost sters
    bool sterge(TElem e);

    // verifica daca un element se afla in multime
    bool cauta(TElem elem) const;

    // intoarce numarul de elemente din multime;
    int dim() const;

    // verifica daca multimea e vida;
    bool vida() const;

    // returneaza un iterator pe multime
    IteratorMultime iterator() const;

    // adauga toate elementele din multimea b in multimea curenta
    void reuniune(const Multime &b);

    // destructorul multimii
    ~Multime();
};
#endif //L1_MULTIME_H
