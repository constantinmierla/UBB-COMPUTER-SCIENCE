//
// Created by Costi on 29-Mar-24.
//

#include "service.h"
#include <algorithm>
#include <functional>

void MasinaService::addMasinaService(int nr, const std::string &producator, const std::string &model,
                                     const std::string &tip) {
    Masina m{nr, producator, model, tip};
    rep.store(m);
}

void MasinaService::delMasinaService(int nr) {
    rep.delMasinaRepo(nr);
}

void MasinaService::modifyMasinaService(int nr, const std::string &producator, const std::string &model,
                                        const std::string &tip) {
    Masina m{nr, producator, model, tip};
    rep.modifyMasinaRepo(nr, m);
}

const Masina &MasinaService::srcMasinaService(int nr) {
    return rep.srcMasinaRepo(nr);
}