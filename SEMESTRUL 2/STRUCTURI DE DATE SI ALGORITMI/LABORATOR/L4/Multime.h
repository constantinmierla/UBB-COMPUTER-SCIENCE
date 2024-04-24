#pragma once
#define cap 10


typedef int TElem;
struct nod {
    TElem info;
    int urm, ant;
};

struct LDI {
    nod* nodes;
    int capacitate, inceput, sfarsit, firstEmpty, size;
};



typedef bool(*Relatie)(TElem, TElem);


bool rel(TElem, TElem);

class IteratorMultime;

class Nod;



class Multime {

    friend class IteratorMultime;

private:

    LDI ldi;
    //Relatie relatie;

    void insertPosition(TElem e, int pos);

    void resize();

    int allocate();

    void free(int poz);

public:

    //constructorul implicit
    Multime();

    //adauga un element in multime
    //returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
    bool adauga(TElem e);

    //sterge un element din multime
    //returneaza adevarat daca elementul a existat si a fost sters
    bool sterge(TElem e);

    //verifica daca un element se afla in multime
    bool cauta(TElem elem) const;


    //intoarce numarul de elemente din multime;
    int dim() const;

    //verifica daca multimea e vida;
    bool vida() const;

    void intersectie(const Multime& b);

    void redim();

    void afisare();
    //returneaza un iterator pe multime
    IteratorMultime iterator() const;

    // destructorul multimii
    ~Multime();

};
