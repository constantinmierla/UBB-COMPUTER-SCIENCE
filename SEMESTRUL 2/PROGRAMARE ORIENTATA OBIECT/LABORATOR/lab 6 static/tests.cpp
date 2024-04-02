//
// Created by Costi on 29-Mar-24.
//

#include "tests.h"
#include "service.h"
#include "domain.h"
#include "repository.h"
#include <cassert>
#include <iostream>
#include <vector>

// teste domain
void test_domain() {
    Masina m1(123, "Audi", "A4", "sedan");
    assert(m1.getNR() == 123);
    assert(m1.getProducator() == "Audi");
    assert(m1.getModel() == "A4");
    assert(m1.getTip() == "sedan");

    Masina m2 = m1;
    assert(m2.getNR() == 123);
    assert(m2.getProducator() == "Audi");
    assert(m2.getModel() == "A4");
    assert(m2.getTip() == "sedan");

    assert(m1.to_string_print() == "NrInmatriculare: 123 | Producator: Audi | Model: A4 | Tip:sedan");
}

// teste repository
void test_repository()
{

    MasinaRepo repo;
    assert(repo.getAll().empty());

    Masina m6(123, "Audi", "A4", "sedan");
    repo.store(m6);

    assert(!repo.delMasinaRepo(999));

    Masina m1(123, "Audi", "A4", "sedan");
    Masina m2(456, "BMW", "X5", "SUV");

    repo.store(m1);
    assert(repo.getAll().size() == 1);

    repo.store(m2);
    assert(repo.getAll().size() == 2);

    assert(repo.delMasinaRepo(123));
    assert(repo.getAll().size() == 1);
    assert(repo.delMasinaRepo(456));
    assert(repo.getAll().empty());

    repo.store(m1);
    assert(repo.modifyMasinaRepo(123, Masina(123, "Opel", "Corsa", "hatchback")));
    assert(repo.getAll().size() == 1);
    assert(repo.find("Opel", "Corsa").getModel() == "Corsa");

    try {
        repo.srcMasinaRepo(999);
    } catch (const MasinaRepoException& ex) {
    }

    try {
        repo.delMasinaRepo(-1);
    } catch (const MasinaRepoException& ex) {
    }

    try {
        repo.find("Ford", "Focus");
    } catch (const MasinaRepoException& ex) {
    }

    Masina m(123, "Audi", "A4", "sedan");
    assert(repo.store(m));

    Masina q(123, "Audi", "A4", "sedan");
    assert(!repo.store(q));

    Masina w(129, "Audi", "A4", "hatchback");
    assert(!repo.modifyMasinaRepo(-1, w));

    MasinaRepo repo2;
    Masina y(123, "Audi", "A4", "sedan");
    assert(repo2.store(y)); // Adăugăm mașina în repo

    const Masina& masina_recuperata = repo2.srcMasinaRepo(123);
    assert(masina_recuperata.getNR() == y.getNR());
    assert(masina_recuperata.getProducator() == y.getProducator());
    assert(masina_recuperata.getModel() == y.getModel());
    assert(masina_recuperata.getTip() == y.getTip());
}

//teste service
void test_service()
{
    MasinaRepo repo;
    MasinaService srv{repo};

    assert(srv.addMasinaService(123, "Audi", "A4", "sedan"));
    assert(srv.getAll().size() == 1);

    assert(srv.delMasinaService(123));
    assert(srv.getAll().empty());

    assert(srv.addMasinaService(123, "Audi", "A4", "sedan"));
    assert(srv.modifyMasinaService(123, "Opel", "Corsa", "hatchback"));
    assert(srv.getAll().size() == 1);

    assert(srv.addMasinaService(123, "Audi", "A4", "sedan"));
    assert(!srv.addMasinaService(123, "Audi", "A4", "sedan"));

    assert(!srv.delMasinaService(999));

    assert(!srv.modifyMasinaService(999, "Opel", "Corsa", "hatchback"));


}
void test_total()
{
    test_domain();
    test_repository();
    test_service();
    std::cout << "All tests passed!\n";
}

