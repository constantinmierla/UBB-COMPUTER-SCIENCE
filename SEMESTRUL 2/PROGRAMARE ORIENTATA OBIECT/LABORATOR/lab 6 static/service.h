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
    MasinaRepo &rep;


public:
    MasinaService(MasinaRepo &r) : rep{r} {

    }

    MasinaService(const MasinaService &ot) = delete;

    const vector<Masina> &getAll() noexcept
    {
        return rep.getAll();
    }

    bool addMasinaService(int nr, const string &producator, const string &model, const string &tip);

    bool delMasinaService(int nr);

    bool modifyMasinaService(int nr, const string &producator, const string &model, const string &tip);

    //const Masina &srcMasinaService(int nr);



};
#endif //LAB_6_STATIC_SERVICE_H
