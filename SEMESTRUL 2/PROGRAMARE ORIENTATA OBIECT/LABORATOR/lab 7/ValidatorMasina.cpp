#include "ValidatorMasina.h"

bool ValidatorMasina::esteNrInmatriculare(const string& nrInmatriculare) {
    if (nrInmatriculare.length() != 7) {
        return false;
    }

    for (const auto& indice : { 0,1,4,5,6 }) {
        if (!isupper(nrInmatriculare.at(indice))) {
            return false;
        }
    }

    for (const auto& indice : { 2,3 }) {
        if (!isdigit(nrInmatriculare.at(indice))) {
            return false;
        }
    }

    return true;
}

void ValidatorMasina::validate(const Masina& masina) const {
    vector<string> errors;

    if (!esteNrInmatriculare(masina.GetNrInmatriculare())) {
        errors.push_back("Numar de inmatriculare invalid!\n");
    }
    if (masina.GetProducator() == "") {
        errors.push_back("Producator invalid!\n");
    }
    if (masina.GetModel() == "") {
        errors.push_back("Model invalid!\n");
    }
    if (masina.GetTip() == "") {
        errors.push_back("Tip invalid!\n");
    }

    if (errors.size() > 0) {
        throw ValidateException(errors);
    }
}

ostream& operator<<(ostream& out, const ValidateException& validator) {
    for (const auto& error : validator.errors) {
        out << error;
    }
    return out;
}