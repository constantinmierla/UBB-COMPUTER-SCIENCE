#pragma once
#include <string>
#include <iostream>
#include <utility>
using std::string;

class MasinaException : public std::exception {
    string msg;
public:
    explicit MasinaException(string msg) : msg{ std::move(msg) } {

    }

    [[nodiscard]] string get_msg() const {
        return msg;
    }

};

class Masina {
private:
    string nr_inmatriculare;
    string producator;
    string model;
    string tip;
public:
    /*
     * functie getter pentru nr_inmatriculare
     * returneaza nr_inmatriculare
     */
    [[nodiscard]] string get_nr_inmatriculare() const;

    /*
     * functie getter pentru producator
     * returneaza producator
     */
    [[nodiscard]] string get_producator() const;

    /*
     * functie getter pentru model
     * returneaza model
     */
    [[nodiscard]] string get_model() const;

    /*
     * functie getter pentru tip
     * returneaza tip
     */
    [[nodiscard]] string get_tip() const;

    /*
     * functie de creare a obiectului Masina
     * Date de intrare: nr_inmatriculare - string, producator - string, model - string, tip - string
     * Date de iesire: -
     * pre: nr_inmatriculare are 9 caractere, producator, model si tip nu sunt siruri vide
     * post: obiectul Masina este creat
     * post: nr_inmatriculare, producator, model si tip sunt setate
     */
    Masina() = default;

    Masina(string  nr_inmatriculare, string  producator, string  model, string  tip) : nr_inmatriculare{ std::move(nr_inmatriculare) }, producator{ std::move(producator) }, model{ std::move(model) }, tip{ std::move(tip) } {
        
    }

    Masina(const Masina& masina) : nr_inmatriculare{ masina.nr_inmatriculare }, producator{ masina.producator }, model{ masina.model }, tip{ masina.tip } {
        //std::cout<<"copy\n";
    }

    ~Masina() {
        
    }

    Masina& operator=(const Masina& masina) = default;


    /*
     * functie de validare a obiectului Masina
     * Date de intrare: masina - Masina
     * Date de iesire: 0 - daca masina este valida, 1 - daca nr_inmatriculare nu are 9 caractere,
     * 2 - daca producator este gol, 3 - daca model este gol, 4 - daca tip este gol
     */
    static int validateMasina(const Masina& masina);
};