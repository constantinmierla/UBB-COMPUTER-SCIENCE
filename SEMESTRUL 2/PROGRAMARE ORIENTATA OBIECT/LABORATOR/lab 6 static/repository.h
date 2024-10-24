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
    vector<Masina> all;  // Vector care conține toate mașinile stocate în repo
    bool exist(const Masina& m) const;  // Funcție privată pentru a verifica dacă o mașină există deja în repo
public:
    // Constructor implicit pentru MasinaRepo
    MasinaRepo() = default;

    // Constructor de copiere eliminat pentru a preveni copierea neautorizată a repo-ului
    MasinaRepo(const MasinaRepo& ot) = delete;

    // Funcție pentru a adăuga o mașină în repo
    bool store(const Masina& m);

    // Funcție pentru a șterge o mașină din repo bazându-se pe numărul său
    bool delMasinaRepo(int nr);

    // Funcție pentru a modifica informațiile unei mașini din repo bazându-se pe numărul său
    bool modifyMasinaRepo(int nr, const Masina& masina_de_modificat);

    // Funcție pentru a găsi o mașină din repo bazându-se pe numărul său
    const Masina& srcMasinaRepo(int nr);

    // Funcție pentru a căuta o mașină în repo bazându-se pe producător și model
    const Masina& find(const string& producator, const string& model) const;

    // Funcție pentru a returna toate mașinile din repo
    const vector<Masina>& getAll() const noexcept;
};

class MasinaRepoException{
    string msg;  // Mesajul excepției

public:
    // Constructor care primește un mesaj pentru excepție
    explicit MasinaRepoException(string m) : msg{ m } {

    }

    // Suprascrierea operatorului de afișare pentru a afișa excepția
    //friend ostream& operator<<(ostream& out, const MasinaRepoException& ex);
};

//ostream& operator<<(ostream& out, const MasinaRepoException& ex);


#endif //LAB_6_STATIC_REPOSITORY_H
