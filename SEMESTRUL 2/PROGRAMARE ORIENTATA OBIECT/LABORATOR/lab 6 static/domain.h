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
    int nr;
    std::string producator;
    std::string model;
    std::string tip;

public:
    Masina(int n, const string prod, const string mod, const string t) : nr{ n}, producator{prod}, model{mod}, tip{t}{

    }
    Masina(const Masina& ot) : nr{ ot.nr}, producator{ot.producator}, model{ot.model}, tip{ot.tip}{
        cout << "*\n";
    }
    int getNR() const noexcept{
        return nr;
    }

    string getProducator() const{
        return producator;
    }

    string getModel() const{
        return model;
    }

    string getTip()const{
        return tip;
    }

    string to_string_print();
};

#endif //LAB_6_STATIC_DOMAIN_H