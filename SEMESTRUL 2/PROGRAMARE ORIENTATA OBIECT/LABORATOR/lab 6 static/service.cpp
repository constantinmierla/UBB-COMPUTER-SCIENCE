//
// Created by Costi on 29-Mar-24.
//

#include "service.h"

// Funcție pentru a adăuga o mașină în repo
bool MasinaService::addMasinaService(int nr, const std::string &producator, const std::string &model,
                                     const std::string &tip) {
    Masina m{nr, producator, model, tip};
    bool c = rep.store(m);
    if (c)
        return true;
    return false;
}

// Funcție pentru a șterge o mașină din repo bazându-se pe numărul său
bool MasinaService::delMasinaService(int nr) {
    bool c = rep.delMasinaRepo(nr);
    if (c)
        return true;
    return false;
}

// Funcție pentru a modifica informațiile unei mașini din repo bazându-se pe numărul său
bool MasinaService::modifyMasinaService(int nr, const std::string &producator, const std::string &model,
                                        const std::string &tip) {
    Masina m{nr, producator, model, tip};
    bool c = rep.modifyMasinaRepo(nr, m);
    if (c)
        return true;
    return false;
}

