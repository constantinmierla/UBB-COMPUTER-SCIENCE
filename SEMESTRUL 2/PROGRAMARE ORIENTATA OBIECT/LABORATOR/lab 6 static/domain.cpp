//
// Created by Costi on 29-Mar-24.
//

#include "domain.h"

string Masina::to_string_print() {
    return "NrInmatriculare: " + std::to_string(this->nr) + " | Producator: " + this->producator + " | Model: " + this->model + " | Tip:" + this->tip;
}
