#include "Masina.h"

string Masina::GetNrInmatriculare() const {
    return this->nrInmatriculare;
}

string Masina::GetProducator() const {
    return this->producator;
}

string Masina::GetModel() const {
    return this->model;
}

string Masina::GetTip() const {
    return this->tip;
}

void Masina::SetNrInmatriculare(const string& nrInmatriculare) {
    this->nrInmatriculare = nrInmatriculare;
}

void Masina::SetProducator(const string& producator) {
    this->producator = producator;
}

void Masina::SetModel(const string& model) {
    this->model = model;
}

void Masina::SetTip(const string& tip) {
    this->tip = tip;
}

Masina& Masina::operator=(const Masina& ot) {
    if (this == &ot) {
        return *this;
    }

    this->nrInmatriculare = ot.nrInmatriculare;
    this->model = ot.model;
    this->producator = ot.producator;
    this->tip = ot.tip;

    return *this;
}

ostream& operator<<(ostream& out, const Masina& masina) {
    out << masina.GetNrInmatriculare() << " " << masina.GetProducator() << " " << masina.GetModel() << " " << masina.GetTip() << '\n';
    return out;
}

bool cmpNrInmatriculare(const Masina& m1, const Masina& m2) {
    return m1.GetNrInmatriculare() < m2.GetNrInmatriculare();
}

bool cmpTip(const Masina& m1, const Masina& m2) {
    return m1.GetTip() < m2.GetTip();
}

bool cmpProducatorAndModel(const Masina& m1, const Masina& m2) {
    auto producator1 = m1.GetProducator();
    auto producator2 = m2.GetProducator();

    if (producator1 != producator2) {
        return producator1 < producator2;
    }

    return m1.GetModel() < m2.GetModel();
}