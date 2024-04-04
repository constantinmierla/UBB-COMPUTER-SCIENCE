//
// Created by Costi on 29-Mar-24.
//

#ifndef LAB_6_STATIC_SERVICE_H
#define LAB_6_STATIC_SERVICE_H

#include "domain.h"
#include "repository.h"
#include <functional>
#include <vector>

using std::vector;
using std::function;

class MasinaService {
    MasinaRepo &rep;  // Referință către repo-ul Masina

public:
    // Constructor care primește o referință către un MasinaRepo pentru a inițializa MasinaService
    explicit MasinaService(MasinaRepo &r) : rep{r} {

    }

    // Constructor de copiere eliminat pentru a preveni copierea neautorizată a MasinaService
    MasinaService(const MasinaService &ot) = delete;

    // Funcție pentru a returna toate mașinile din repo
    const vector<Masina> &getAll() noexcept
    {
        return rep.getAll();
    }

    // Funcție pentru a adăuga o mașină în repo
    bool addMasinaService(int nr, const string &producator, const string &model, const string &tip);

    // Funcție pentru a șterge o mașină din repo bazându-se pe numărul său
    bool delMasinaService(int nr);

    // Funcție pentru a modifica informațiile unei mașini din repo bazându-se pe numărul său
    bool modifyMasinaService(int nr, const string &producator, const string &model, const string &tip);

    // Funcție pentru a căuta o mașină în repo bazându-se pe numărul său
    //const Masina &srcMasinaService(int nr);
};

#endif //LAB_6_STATIC_SERVICE_H
