//
// Created by Costi on 29-Mar-24.
//

#include "repository.h"
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

bool MasinaRepo::store(const Masina& m){
    if(exist(m)){
        return false;
    }
    all.push_back(m);
    return true;
}
bool MasinaRepo::delMasinaRepo(int nr) {
    if (nr >= 0)
    {
        int pozitie = -1;
        for(int i = 0; i < (int)all.size(); i++)
        {
            if(all[i].getNR() == nr)
            {
                pozitie = i;
                break;
            }
        }
        if(pozitie == -1) {
            //all.erase(all.begin(), all.begin() + 1);
            return false;
        }
        else
            all.erase(all.begin() + pozitie);
        return true;
    }
    else
        return false;
}

bool MasinaRepo::modifyMasinaRepo(int nr, const Masina &masina_de_modificat) {
    if(nr >= 0)
    {
        for(auto & i : all)
        {
            if (i.getNR() == nr)
            {
                i = masina_de_modificat;
                return true;
            }
        }
        return false;
    }
    else
        return false;
}

const Masina &MasinaRepo::srcMasinaRepo(int nr) {
    if(nr >= 0) {
        for (const auto & i : all) {
            if (i.getNR() == nr)
                return i;
        }
    }
    throw MasinaRepoException("Nu exista masina!");
}

bool MasinaRepo::exist(const Masina &m) const {
    try{
        find(m.getProducator(), m.getModel());
        return true;
    }
    catch(MasinaRepoException&)
    {
        return false;
    }
}

const Masina& MasinaRepo::find(std::string producator, std::string model) const {
    for(const auto& m: all)
    {
        if(m.getProducator() == producator && m.getModel() == model)
            return m;
    }
    throw MasinaRepoException("Nu exista masina!");
}

const vector<Masina>& MasinaRepo::getAll() const noexcept {
    return all;
}

/*ostream& operator<<(ostream& out, const MasinaRepoException& ex)
{
    out << ex.msg;
    return out;
}*/