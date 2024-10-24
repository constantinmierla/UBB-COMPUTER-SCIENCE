#include "CarStore.h"

void CarStore::addMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip) {
    Masina masina{ nrInmatriculare, producator, model, tip };

    validator.validate(masina);
    repo.store(masina);
}

void CarStore::eraseMasina(const string& nrInmatriculare) {
    repo.erase(nrInmatriculare);
}

void CarStore::modifyMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip) {
    Masina masina{ nrInmatriculare, producator, model, tip };
    validator.validate(masina);
    repo.modify(nrInmatriculare, producator, model, tip);
}

const Masina& CarStore::findMasina(const string& nrInmatricular) {
    return repo.find(nrInmatricular);
}

const DynamicArray<Masina>& CarStore::getAll() const noexcept {
    return repo.getAll();
}

DynamicArray<Masina> CarStore::generalSort(const function<bool(const Masina& m1, const Masina& m2)>& rel) const {
    auto sorted{ getAll() };
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < static_cast<int>(sorted.size()) - 1; i += 1) {
            if (!rel(sorted.at(i), sorted.at(i + 1))) {
                auto aux = sorted.at(i);
                sorted.at(i) = sorted.at(i + 1);
                sorted.at(i + 1) = aux;
            }
        }
    }

    return sorted;}
DynamicArray<Masina> CarStore::sortByNtInmatriculare() {
    return generalSort(cmpNrInmatriculare);
}

DynamicArray<Masina> CarStore::sortByTip() {
    return generalSort(cmpTip);
}

DynamicArray<Masina> CarStore::sortByProducatorAndModel() {
    return generalSort(cmpProducatorAndModel);
}

DynamicArray<Masina> CarStore::generalFilter(const function<bool(const Masina& m)>& filter) {
    DynamicArray<Masina> result{};
    auto ceva = repo.getAll();

    for (const auto& masina : ceva) {
        if (filter(masina)) {
            result.push_back(masina);
        }
    }

    return result;
}

DynamicArray<Masina> CarStore::filterByProducator(const string& producator) {
    return generalFilter([producator](const Masina& m) {
        return m.GetProducator() == producator;
    });
}

DynamicArray<Masina> CarStore::filterByTip(const string& tip) {
    return generalFilter([tip](const Masina& m) {
        return m.GetTip() == tip;
    });
}