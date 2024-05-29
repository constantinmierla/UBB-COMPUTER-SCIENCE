#include "repository.h"

void MasinaRepo::adaugaMasina(const Masina& masina) {
    bool exista = false;
    for( auto& masina_curenta : masini)
		if (masina_curenta.get_nr_inmatriculare() == masina.get_nr_inmatriculare())
			exista = true;
    if (exista) {
        throw RepoException("Masina cu acelasi numar de inmatriculare deja existenta!");
    }
    masini.push_back(masina);
}

void MasinaRepo::stergeMasina(const std::string& nr_inmatriculare) {
    __int64_t poz = -1;
    for(auto& masina : masini)
		if (masina.get_nr_inmatriculare() == nr_inmatriculare)
			poz = &masina - &masini[0];
    if (poz == -1)
        throw RepoException("Masina cu acest numar de inmatriculare nu exista!");
    masini.erase(masini.begin() + poz);
}

void MasinaRepo::modificaMasina(const Masina& masina) {
    __int64_t poz = -1;
    for(auto& masina_curenta : masini)
        if (masina_curenta.get_nr_inmatriculare() == masina.get_nr_inmatriculare())
            poz = &masina_curenta - &masini[0];
    if (poz == -1)
        throw RepoException("Masina cu acest numar de inmatriculare nu exista!");
    masini[poz] = masina;
}

void MasinaRepo::adaugaManager(const Masina& masina) {
    manager.push_back(masina);
}


