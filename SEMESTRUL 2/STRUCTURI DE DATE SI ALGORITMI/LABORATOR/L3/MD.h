//
// Created by Costi on 06-Apr-24.
//
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


class NodL //nod intr-o lista simplu inlantuita folosita pentru a stoca
        //valorile asociate unei chei in cadrul MultiDictionarului
        //contine un pointer catre urmatorul nod si o valoare
{
    friend class ListaV;
public:

    NodL() = default;

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    TValoare element();

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    NodL* urmator();

    TValoare v; //valoare
    NodL* urm; //nod lista urmator

private:
};


class ListaV //o lista simplu inlantuita de noduri de tip NodL
            //este utilizata pentru a stoca toate valorile asociate unei chei specifice din MultiDictionar
{
    friend class MD;
public:

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    ListaV();

    ///Complexitate favorabil: Θ(1)
    ///Complexitate defavorabil: Θ(n)
    ///Complexitate timp total: O(n)
    void adauga(TValoare v);

    ///Complexitate favorabil: Θ(1)
    ///Complexitate defavorabil: Θ(n)
    ///Complexitate timp total: O(n)
    bool sterge(TValoare v);

    ///Complexitate favorabil: Θ(1)
    ///Complexitate defavorabil: Θ(n)
    ///Complexitate timp total: O(n)
    vector<TValoare> cauta();
    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    int dim();

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    bool vida() const;

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(n)
    ~ListaV();

    NodL* prim;

private:
    int n;
};


class Nod //Aceasta clasa reprezinta un nod intr-o lista simplu inlantuita folosita
        //pentru a stoca perechi (cheie, lista de valori).
        //contine un pointer catre urmatorul nod si o pereche
{
    friend class MD;
public:

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    Nod();

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    Telem element();

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    Nod* urmator();

    Telem e;
    Nod* urm;

private:
};


class MD //structura de liste inlantuite pentru a stoca cheile si valorile asociate lor
{
    friend class IteratorMD;

private:

    int n;
    Nod* prim;

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    void stergeCheie(Nod* prec);

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    void adaugaCheieNoua(TCheie c, TValoare v, Nod* prec);

public:
    ///Θ(1)
    // constructorul implicit al MultiDictionarului
    MD();

    ///Complexitate favorabil: Θ(n)
    ///Complexitate defavorabil: Θ(n^2)
    ///Complexitate timp total: O(n^2)
    // adauga o pereche (cheie, valoare) in MD
    void adauga(TCheie c, TValoare v);

    ///Complexitate favorabil: Θ(n)
    ///Complexitate defavorabil: Θ(n^2)
    ///Complexitate timp total: O(n^2)
    //sterge o cheie si o valoare
    //returneaza adevarat daca s-a gasit cheia si valoarea de sters
    bool sterge(TCheie c, TValoare v);

    ///Complexitate favorabil: Θ(1)
    ///Complexitate defavorabil: Θ(n)
    ///Complexitate timp total: O(n)
    //cauta o cheie si returneaza vectorul de valori asociate
    vector<TValoare> cauta(TCheie c) const;

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total = Θ(1)
    //returneaza numarul de perechi (cheie, valoare) din MD
    int dim() const;

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    //verifica daca MultiDictionarul e vid
    bool vid() const;

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(1)
    // se returneaza iterator pe MD
    IteratorMD iterator() const;

    ///Caz favorabil: Θ(1)
    ///Caz defavorabil: Θ(n*m)
    ///Caz timp total: O(n*m)
    ///elimina o cheie impreuna cu toate valorile sale, n numarul de chei, m numarul de valori
    ///returneaza un vector cu valorile care au fost anterior asociate acesei chei (si au fost eliminate)
    vector<TValoare> stergeValoriPentruCheie(TCheie cheie);
/*
 * PSEUDOCOD ALGORITM stergeValoriPentruCheie
 *
 * stergeValoriPentruCheie(cheie: TCheie)
 *     vectorValoriSterse <- vector gol
 *     daca primul nod din MultiDictionar este diferit de nullptr atunci:
 *         nodCurent <- primul nod din MultiDictionar
 *         nodPrecedent <- nullptr
 *         cat timp nodCurent este diferit de nullptr executa:
 *             daca cheia nodului curent este egala cu cheia data ca argument atunci:
 *                 vectorValoriSterse <- valori asociate nodului curent
 *                 daca nodul precedent este nullptr atunci
 *                     stergeCheie(nullptr)
 *                 altfel
 *                     stergeCheie(nodPrecedent)
 *                 oprire bucla
 *             altfel:
 *                 nodPrecedent <- nodCurent
 *                 nodCurent <- nodul urmator din MultiDictionar
 *             sfarsit daca
 *         sfarsit cat timp
 *     sfarsit daca
 *     returneaza vectorValoriSterse
 * sfarsit algoritmului
 */

    ///Complexitate favorabil = Complexitate defavorabil = Complexitate timp total =Θ(n)
    // destructorul MultiDictionarului
    ~MD();


};

