#include "TestRepo.h"

void TestRepo::testStore() const {
    Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
    CarRepo repo{};
    assert(repo.getLength() == 0);

    repo.store(masina);
    assert(repo.getLength() == 1);

    try {
        Masina masinaNoua{ "BC13BCG", "Ceva", "Logan", "berlina" };
        repo.store(masinaNoua);
        assert(false);
    }
    catch (const CarRepoException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Masina deja existenta!\n");
    }

    Masina const masinaNoua{ "BC13BC3", "Ceva", "Logan", "berlina" };
    repo.store(masinaNoua);
    assert(repo.getLength() == 2);
}

void TestRepo::testErase() const {
    Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
    CarRepo repo{};

    repo.store(masina);
    Masina masinaNoua{ "BC13BCB", "Ceva", "Logan", "berlina" };
    repo.store(masinaNoua);

    repo.erase("BC13BCB");
    assert(repo.getLength() == 1);

    try {
        repo.erase("BC13BC2");
        assert(false);
    }
    catch (const CarRepoException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Masina inexistenta!\n");
    }

    repo.store(masinaNoua);
    assert(repo.getLength() == 2);

    repo.clear();
    assert(repo.getLength() == 0);
}

void TestRepo::testFind() const {
    Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
    CarRepo repo{};

    repo.store(masina);
    auto masinaGasita = repo.find("BC13BCG");
    assert(masinaGasita.GetNrInmatriculare() == masina.GetNrInmatriculare());
    assert(masinaGasita.GetProducator() == masina.GetProducator());
    assert(masinaGasita.GetModel() == masina.GetModel());
    assert(masinaGasita.GetTip() == masina.GetTip());

    try {
        repo.find("SV13BCG");
        assert(false);
    }
    catch (const CarRepoException& e) {
        stringstream os;
        os << e;
        assert(os.str() == "Masina inexistenta!\n");
        assert(true);
    }
}

void TestRepo::testGetAll() const {
    Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
    CarRepo repo{};

    repo.store(masina);

    Masina masinaNoua{ "BC13BCE", "Ceva", "Logan", "berlina" };
    repo.store(masinaNoua);
    assert(repo.getLength() == 2);

    Masina masinaNouaNoua{ "BC13BCR", "Ceva", "Logan", "berlina" };
    repo.store(masinaNouaNoua);
    assert(repo.getLength() == 3);

    auto list = repo.getAll();
    assert(list.size() == 3);

    assert(list.at(0).GetNrInmatriculare() == "BC13BCG");
    assert(list.at(1).GetNrInmatriculare() == "BC13BCE");
    assert(list.at(2).GetNrInmatriculare() == "BC13BCR");
}

void TestRepo::testPrint() const {
    Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
    CarRepo repo{};

    repo.store(masina);

    Masina masinaNoua{ "BC13BCE", "Ceva", "Logan", "berlina" };
    repo.store(masinaNoua);

    stringstream os;
    os << repo;
    assert(os.str() == "BC13BCG Dacia Logan berlina\nBC13BCE Ceva Logan berlina\n");
}

void TestRepo::testModify() const {
    Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
    CarRepo repo{};

    repo.store(masina);
    repo.modify("BC13BCG", "Renault", "Megane", "break");

    auto masinaGasita = repo.find("BC13BCG");
    assert(masinaGasita.GetProducator() == "Renault");
    assert(masinaGasita.GetModel() == "Megane");
    assert(masinaGasita.GetTip() == "break");

    try {
        repo.modify("SV25ABC", "Renault", "Megane", "break");
        assert(false);
    }
    catch (const CarRepoException& ex) {
        stringstream os;
        os << ex;
        assert(os.str() == "Masina inexistenta!\n");
        assert(true);
    }
}

void TestRepo::runAllTests() const {
    testStore();
    testErase();
    testFind();
    testGetAll();
    testPrint();
    testModify();
}