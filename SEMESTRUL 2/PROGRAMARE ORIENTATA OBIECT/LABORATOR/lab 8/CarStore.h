#pragma once
#include "CarRepo.h"
#include "Masina.h"
#include "ValidatorMasina.h"
#include <functional>

using std::function;

class CarStore
{
private:
    CarRepo& repo;
    const ValidatorMasina& validator;

    /**
    * Functie generala pentru sortea masinilor
    *
    * @params: o functie care defineste o relatie Masina x Masina dupa care se va face sortarea
    *
    * @return: o lista de masini sortate dupa relatia daca ca parametru
    */
    DynamicArray<Masina> generalSort(const function<bool(const Masina& m1, const Masina& m2)>& rel) const;

    /**
    * Functie generala pentru filtrarea masinilor
    *
    * @params: o functie care defineste o conditie impuse asuprea masinilor
    *
    * @return: o lista de masini care indeplinesc relatia transmisa ca parametru parametru
    */
    DynamicArray<Masina> generalFilter(const function<bool(const Masina& m)>& filter);

public:
    CarStore() = delete;
    CarStore(const CarStore& ot) = delete;
    CarStore(CarRepo& repo, const ValidatorMasina& validator) noexcept : repo{ repo }, validator{ validator } {};

    /**
    * Functie care adauga o masina cu proprietatile specificate
    *
    * @params: nrInmatriculare - o referinta constanta la un string
    *		   producator - o referinta constanta la un string
    *          model - o referinta constanta la un string
    *		   tip - o referinta constanta la un string
    *
    *@exceptii: ValidateException - daca atributele sunt invalide
    *			CarRepoException - daca exista deja masina
    */
    void addMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);

    /**
    * Functie care sterge o masina pe baza numarului de inmatriculare
    *
    * @params: nrInmatriculare - o referinta constanta la un string
    *
    @exceptii: CarRepoException - daca nu exista masina
    */
    void eraseMasina(const string& nrInmatriculare);

    /**
    * Functie care modifica atributele unei masini pe baza numarului de inmatriculare
    *
    * @params: nrInmatriculare - o referinta constanta la un string
    *		   producator - o referinta constanta la un string
    *          model - o referinta constanta la un string
    *		   tip - o referinta constanta la un string
    *
    *@exceptii: ValidateException - daca atributele sunt invalide
    *			CarRepoException - daca nu exista o masina cu numarul de inmatriculare dat
    */
    void modifyMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);

    /**
    * Functie care cauta o masina avand numarul de inmatriculare dat
    *
    * @params: nrInmatriculare - o referinta constanta la un string
    *
    * @return: o referinta constanta la masina care are parametrii dati
    *
    * @exceptii: CarRepoException cu textul "Masina inexistenta!\n" daca masina nu exista in repo
    */
    const Masina& findMasina(const string& nrInmatricular);

    /**
    * Functie care returneaza o lista de masini ordonate in ordine crescatoare in functie de numarul de inmatriculare
    *
    * @params: -
    *
    * @return: o lista de masini
    */
    DynamicArray<Masina> sortByNtInmatriculare();

    /**
    * Functie care returneaza o lista de masini ordonate in ordine crescatoare in functie de tip
    *
    * @params: -
    *
    * @return: o lista de masini
    */
    DynamicArray<Masina> sortByTip();

    /**
    * Functie care returneaza o lista de masini ordonate in ordine crescatoare in functie de producator si model
    *
    * @params: -
    *
    * @return: o lista de masini
    */
    DynamicArray<Masina> sortByProducatorAndModel();

    /**
    * Functie pentru filtrarea masinilor in functie de producator
    *
    * @params: producator - un string
    *
    * @return: lista masinilor care au producatorul oferit ca producator
    */
    DynamicArray<Masina> filterByProducator(const string& producator);

    /**
    * Functie pentru filtrarea masinilor in functie de tip
    *
    * @params: tip - un string
    *
    * @return: lista masinilor care au tipul oferit ca tip
    */
    DynamicArray<Masina> filterByTip(const string& tip);

    /**
    * Functie care retuneaza o lista imutabila cu toate masinile
    *
    * @params: -
    *
    * @return: o lista imutabila de masini
    */
    const DynamicArray<Masina>& getAll() const noexcept;
};
