#include "domain.h"

const int val = 9;

string Masina::get_nr_inmatriculare() const {
    return nr_inmatriculare;
}

string Masina::get_producator() const {
    return producator;
}

string Masina::get_model() const {
    return model;
}

string Masina::get_tip() const {
    return tip;
}

int Masina::validateMasina(const Masina& masina) {
    if (masina.get_nr_inmatriculare().size() != val)
        return 1;
    if (masina.get_producator().empty())
        return 2;
    if (masina.get_model().empty())
        return 3;
    if (masina.get_tip().empty())
        return 4;
    return 0;
}



