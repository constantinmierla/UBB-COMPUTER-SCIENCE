#pragma once

#include <utility>
#include <vector>
using std::vector;
#include <string>
using std::string;

#include "domain.h"
#include "VectorDinamic.h"

/*
    Clasa de exceptii pentru repo
*/
class RepoException : public std::exception {
    string msg;
public:
    explicit RepoException(string m) : msg{ std::move(m) } {

    }

    string get_msg() {
        return msg;
    }
};

/*
 * Clasa de repository pentru masini
 * vector dinamic
 */
class MasinaRepo {
private:
    vector<Masina> masini;
    vector<Masina> manager;
    bool allow_manager = true;
public:
    MasinaRepo() = default;
    ~MasinaRepo() = default;
    /*
     * Adauga o masina in lista de masini
     * Date de intrare: masina - Masina
     * Date de iesire: -
     * pre: masina este valida si lista de masini nu contine masina cu acelasi nr_inmatriculare
     * post: masina este adaugata in lista de masini
     * post: lungimea listei de masini este cu 1 mai mare
     * exceptie: daca masina cu nr_inmatriculare exista deja
     */
    void adaugaMasina(const Masina& masina);


    /*
     * Sterge o masina din lista de masini
     * Date de intrare: nr_inmatriculare - string
     * Date de iesire: -
     * post: masina cu nr_inmatriculare este stearsa din lista de masini
     * post: lungimea listei de masini este cu 1 mai mica
     * exceptie: daca masina cu nr_inmatriculare nu exista
     */
    void stergeMasina(const string& nr_inmatriculare);

    /*
     * Modifica o masina din lista de masini
     * Date de intrare: masina - Masina
     * Date de iesire: -
     * post: masina cu nr_inmatriculare este modificata
     * exceptie: daca masina cu nr_inmatriculare nu exista
     */
    void modificaMasina(const Masina& masina);

    /*
     * Returneaza toate masinile din lista de masini
     * Date de intrare: -
     * Date de iesire: vector<Masina>
     * post: se returneaza toate masinile din lista de masini
     */
    vector<Masina>& getAllMasini() {
        return masini;
    }

    void clearAllManager() {
		manager.clear();
	}

    void adaugaManager(const Masina& masina);

    vector<Masina>& getAllManager() {
		return manager;
	}

    bool allowManager() {
        return allow_manager;
    }

    void setManagerFalse() {
		allow_manager = false;
	}
};