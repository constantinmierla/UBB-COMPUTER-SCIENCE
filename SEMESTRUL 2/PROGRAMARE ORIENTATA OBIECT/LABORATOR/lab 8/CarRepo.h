#pragma once
#include "Masina.h"
#include "DynamicArray.h"
#include <vector>
#include <ostream>

using std::vector;
using std::ostream;

class CarRepo
{
private:
    DynamicArray<Masina> storage;

    /**
    * Functie care verifica daca masina se afla deja in repo
    *
    * @params: masina - o referinta constanta la o masina
    *
    * @return: true - daca masina este in repo
    *		   false - altfel
    */
    bool exista(const Masina& masina) const;
public:
    CarRepo() = default;
    CarRepo(const CarRepo& ot) = delete;

    /**
    * Functie care adauga o masina in repo
    *
    * @params: masina - o referinta constanta la o adresa
    *
    * @return: -
    *
    * @exceptii: CarRepoException cu textul "Masina deja existenta!\n" daca masina deja exista in repo
    */
    void store(const Masina& masina);

    /**
    * Functie care sterge o masina din repo pe baza numarului de inmatriculare
    *
    * @params: masina - o referinta constanta la un string
    *
    * @return: -
    *
    * @exceptii: CarRepoException cu textul "Masina inexistenta!\n" daca masina nu exista in repo
    */
    void erase(const string& nrInmatriculare);

    /**
    * Functie care cauta o masina avand numarul de inmatriculare dat
    *
    * @params: nrInmatriculare - o referinta constanta la un string
    *
    * @return: o referinta constanta la masina care are parametrii dati
    *
    * @exceptii: CarRepoException cu textul "Masina inexistenta!\n" daca masina nu exista in repo
    */
    const Masina& find(const string& nrInmatriculare) const;

    /**
    * Functie care modifica o atributele unei masini pe baza numarului de inmatriculare
    *
    * @params: nrInmatriculare - o referinta constanta la un string
    *		   producator - o referinta constanta la un string
    *		   model - o referinta constanta la un string
    *          tip - o referinta constanta la un string
    */
    void modify(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);

    /**
    * Functie care returneaza o lista imutabila cu masini
    *
    * @params: -
    *
    * @return: o lista cu referinte constante spre masini
    */
    const DynamicArray<Masina>& getAll() const noexcept;

    /**
    * Functie care returneaza numarul de obiecte din repo
    *
    * @params: -
    *
    * @return: intreg
    */
    unsigned int getLength() const noexcept;

    /**
    * Functie care goleste repo-ul
    *
    * @params: -
    *
    * @return: -
    */
    void clear();

    /**
    * Functie generica pentru afisarea unui repo
    *
    * @params: out - o referinta la un string de tip ostream
    *		   ex - o referinta un repo de produse
    *
    * @return: o referinta la un string de tip ostream
    */
    friend ostream& operator<<(ostream& out, const CarRepo& repo);
};

class CarRepoException {
    string message;
public:
    explicit CarRepoException(string message): message { message }{};

    /**
    * Functie generica pentru afisarea unei CarRepoException
    *
    * @params: out - o referinta la un string de tip ostream
    *		   ex - o referinta constanta la o CarRepoException
    *
    * @return: o referinta la un string de tip ostream
    */
    friend ostream& operator<<(ostream& out, const CarRepoException& ex);
};
