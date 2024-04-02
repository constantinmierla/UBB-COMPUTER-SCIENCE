//
// Created by Costi on 29-Mar-24.
//

#ifndef LAB_6_STATIC_REPOSITORY_H
#define LAB_6_STATIC_REPOSITORY_H
#include "domain.h"
#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class MasinaRepo{
        vector<Masina> all;
        bool exist(const Masina& m) const;
public:
        MasinaRepo() = default;

        MasinaRepo(const MasinaRepo& ot) = delete;

        bool store(const Masina& m);

        bool delMasinaRepo(int nr);

        bool modifyMasinaRepo(int nr, const Masina& masina_de_modificat);

        const Masina& srcMasinaRepo(int nr);

        const Masina& find(string producator, string model) const;

        const vector<Masina>& getAll() const noexcept;
};

class MasinaRepoException{
        string msg;

public:
        MasinaRepoException(string m) : msg{ m } {

        }

        friend ostream& operator<<(ostream& out, const MasinaRepoException& ex);
};

ostream& operator<<(ostream& out, const MasinaRepoException& ex);


#endif //LAB_6_STATIC_REPOSITORY_H
