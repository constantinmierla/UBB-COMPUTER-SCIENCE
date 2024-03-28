//
// Created by Costi on 29-Mar-24.
//

#include "repository.h"
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void MasinaRepo::store(const Masina& m){
    if(exist(m)){
        throw MasinaRepoException("Exista deja masina!" + std::to_string(m.getNR()) + " " + m.getModel());
    }
    all.push_back(m);
}
void MasinaRepo::delMasinaRepo(int nr) {
    if (nr >= 0)
    {
        int poz;
        for(int i = 0; i < (int)all.size(); i++)
        {
            if(all[i].getNR() == nr)
            {
                poz = i;
                break;
            }
        }
        if(poz == 0)
            all.erase(all.begin(), all.begin()+1);
        else
            all.erase(all.begin() + poz);
    }
    else
        throw MasinaRepoException("NrInmatriculare invalid!");
}

void MasinaRepo::modifyMasinaRepo(int nr, const Masina &masina_de_modificat) {
    if(nr >= 0)
    {
        for(int i = 0; i < (int)all.size(); i++)
        {
            if (all[i].getNR() == nr)
            {
                all[i] = masina_de_modificat;
                break;
                //sa verific si daca nu exista elementul dorit
            }
        }
    }
    else
        throw MasinaRepoException("Nr invalid!");
}

const Masina &MasinaRepo::srcMasinaRepo(int nr) {
    if(nr >= 0)
    {
        for(int i = 0; i < (int)all.size(); i++)
        {
            if(all[i].getNR() == nr)
                return all[i];
        }
    }
    else
        throw MasinaRepoException("Nr invalid!");
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

ostream& operator<<(ostream& out, const MasinaRepoException& ex)
{
    out << ex.msg;
    return out;
}