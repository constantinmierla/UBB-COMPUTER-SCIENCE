//
// Created by Costi on 29-Mar-24.
//

#ifndef LAB_6_STATIC_DOMAIN_H
#define LAB_6_STATIC_DOMAIN_H
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Masina{
    int nr;  // Numărul mașinii
    std::string producator;  // Producătorul mașinii
    std::string model;  // Modelul mașinii
    std::string tip;  // Tipul mașinii

public:
    // Constructor care primește un număr, un producător, un model și un tip pentru a inițializa obiectul Masina
    Masina(int n, const string& prod, const string& mod, const string& t) : nr{ n}, producator{prod}, model{mod}, tip{t}{
    }

    // Constructor de copiere care creează o nouă instanță a clasei Masina pe baza unei alte instanțe
    Masina(const Masina& ot) : nr{ ot.nr}, producator{ot.producator}, model{ot.model}, tip{ot.tip}{
        cout << "*\n";
    }

    // Funcție pentru a obține numărul mașinii
    int getNR() const noexcept{
        return nr;
    }

    // Funcție pentru a obține producătorul mașinii
    string getProducator() const{
        return producator;
    }

    // Funcție pentru a obține modelul mașinii
    string getModel() const{
        return model;
    }

    // Funcție pentru a obține tipul mașinii
    string getTip()const{
        return tip;
    }

    // Funcție pentru a converti informațiile despre mașină într-un șir de caractere pentru afișare
    string to_string_print();
};


#endif //LAB_6_STATIC_DOMAIN_H
