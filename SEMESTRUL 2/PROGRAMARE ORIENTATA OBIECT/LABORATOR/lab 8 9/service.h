#pragma once
#include "repository.h"
#include "domain.h"
#include "VectorDinamic.h"
#include <string>
#include <utility>
using std::string;


typedef int(*Sort)(const Masina&, const Masina&);

/*
 * Clasa de service pentru masini
 */
class ServiceMasina {
private:
    MasinaRepo& repo;
public:
    /*
     * initializeaza un service pentru masini
     */
    explicit ServiceMasina(MasinaRepo& repo) : repo{ repo } { }

    /*
     * Adauga o masina in lista de masini
     */
    void adaugaMasinaService(string& nr_inmatriculare, string& producator, string& model, string& tip);

    /*
     * Sterge o masina din lista de masini
     */
    void stergeMasinaService(const string& nr_inmatriculare);

    /*
     * Modifica o masina din lista de masini
     */
    void modificaMasinaService(string& nr_inmatriculare, string& producator, string& model, string& tip);

    /*
     * Returneaza toate masinile din lista de masini
     */
    vector<Masina> getAllMasiniService();

    /*
     * returneaza o lista filtrata dupa producator
     */
    vector<Masina> filterMasiniProducer(string& producator);

    /*
     * returneaza o lista filtrata dupa tip
     */
    vector<Masina> filterMasiniType(string& tip);

    /*
     * returneaza o lista sortate dupa o functie de sortare
     */
    vector<Masina> sortMasini(Sort functieSortare);

    /*
     * returneaza toate masinile din lista de manager
     */
    vector<Masina>& getAllManager();

    /*
     * adauga o masina in lista de manager
     */
    void adaugaManagerService(string& nr_inmatriculare);

    /*
     * sterge toate masinile din lista de manager
     */
    void clearAllManager();

    /*
     * returneaza true daca managerul este activ
     */
    void createManager();

    /*
     * genereaza o lista random de masini din cele existente
     */
    void generateRandom(int n);
};

/*
 * Functii de sortare
 */
 /*
  * dupa nr_inmatriculare
  */
int sortNrInmatriculare(const Masina& m1, const Masina& m2);

/*
 * dupa tip
 */
int sortTip(const Masina& m1, const Masina& m2);

/*
 * dupa producator si model
 */
int sortProducatorModel(const Masina& m1, const Masina& m2);

/*
 * dupa producator
 */
int sortProducator(const Masina& m1, const Masina& m2);

/*
 * dupa model
 */
int sortModel(const Masina& m1, const Masina& m2);
