#include "CarRepo.h"

void CarRepo::store(const Masina& masina) {
    if (exista(masina)) {
        throw CarRepoException("Masina deja existenta!\n");
    }
    storage.push_back(masina);
}

void CarRepo::erase(const string& nrInmatriculare) {
    find(nrInmatriculare);
    for (unsigned int i = 0; i < getLength(); ++i) {
        if (storage.at(i).GetNrInmatriculare() == nrInmatriculare) {
            storage.erase(i);
        }
    }
}

const Masina& CarRepo::find(const string& nrInmatriculare) const {
    for (const auto& masina : this->storage) {
        if (masina.GetNrInmatriculare() == nrInmatriculare) {
            return masina;
        }
    }

    throw CarRepoException("Masina inexistenta!\n");
}

bool CarRepo::exista(const Masina& masina) const {
    try {
        find(masina.GetNrInmatriculare());
        return true;
    }
    catch (const CarRepoException&) {
        return false;
    }
}

void CarRepo::modify(const string& nrInmatriculare, const string& producator, const string& model, const string& tip) {
    find(nrInmatriculare);

    for (auto& masina : storage) {
        if (masina.GetNrInmatriculare() == nrInmatriculare) {
            masina.SetProducator(producator);
            masina.SetModel(model);
            masina.SetTip(tip);

            return;
        }
    }
}

void CarRepo::clear() {
    storage.clear();
}


ostream& operator<<(ostream& out, const CarRepo& repo) {
    for (const auto& masina : repo.storage) {
        out << masina;
    }
    return out;
}

const DynamicArray<Masina>& CarRepo::getAll() const noexcept {
    return storage;
}

unsigned int CarRepo::getLength() const noexcept{
    return storage.size();
}

ostream& operator<<(ostream& out, const CarRepoException& ex) {
    out << ex.message;
    return out;
}