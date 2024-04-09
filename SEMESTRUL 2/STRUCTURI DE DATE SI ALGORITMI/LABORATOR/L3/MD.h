#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

class ListaV;
class IteratorMD;
class IteratorL;
class Nod;
class NodL;

typedef ListaV* Valori;
typedef std::pair<TCheie, Valori> Telem;
typedef std::pair<TCheie, TValoare> TElem;


class NodL
{
    friend class ListaV;
public:

    NodL() = default;

    ///Θ(1)
    TValoare element();

    ///Θ(1)
    NodL* urmator();

    TValoare v; //valoare
    NodL* urm; //nod lista urmator

private:
};


class ListaV
{
    friend class MD;
public:

    ///Θ(1)
    ListaV();

    ///O(n)
    void adauga(TValoare v);

    ///O(n)
    bool sterge(TValoare v);

    ///O(n)
    vector<TValoare> cauta();

    ///Θ(1)
    int dim();

    ///Θ(1)
    bool vida() const;

    ///Θ(n)
    ~ListaV();

    NodL* prim;

private:
    int n;
};


class Nod
{
    friend class MD;
public:

    ///Θ(1)
    Nod();

    ///Θ(1)
    Telem element();

    ///Θ(1)
    Nod* urmator();

    Telem e;
    Nod* urm;

private:
};


class MD
{
    friend class IteratorMD;

private:

    int n;
    Nod* prim;

    ///Θ(1)
    void stergeCheie(Nod* prec);

    ///Θ(1)
    void adaugaCheieNoua(TCheie c, TValoare v, Nod* prec);

public:
    ///Θ(1)
    // constructorul implicit al MultiDictionarului
    MD();

    ///O(n^2)
    // adauga o pereche (cheie, valoare) in MD
    void adauga(TCheie c, TValoare v);

    ///O(n^2)
    //sterge o cheie si o valoare
    //returneaza adevarat daca s-a gasit cheia si valoarea de sters
    bool sterge(TCheie c, TValoare v);

    ///O(n)
    //cauta o cheie si returneaza vectorul de valori asociate
    vector<TValoare> cauta(TCheie c) const;

    ///Θ(1)
    //returneaza numarul de perechi (cheie, valoare) din MD
    int dim() const;

    ///Θ(1)
    //verifica daca MultiDictionarul e vid
    bool vid() const;

    ///Θ(1)
    // se returneaza iterator pe MD
    IteratorMD iterator() const;

    ///O(n)
    // destructorul MultiDictionarului
    ~MD();


};

