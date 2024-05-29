#include "teste.h"
#include "repository.h"
#include "domain.h"
#include "service.h"
#include <iostream>
#include <cassert>
using namespace std;

void testAddRepo() {
    MasinaRepo repo;
    Masina m1("BH-04-VLD", "Skoda", "Octavia", "Sedan");
    Masina m2("BH-05-VLD", "Skoda", "Octavia", "Sedan");
    Masina m3("BH-06-VLD", "Skoda", "Octavia", "Sedan");
    Masina m4("BH-07-VLD", "Skoda", "Octavia", "Sedan");
    Masina m5("BH-08-VLD", "Skoda", "Octavia", "Sedan");

    repo.adaugaMasina(m1);
    repo.adaugaMasina(m2);
    repo.adaugaMasina(m3);
    repo.adaugaMasina(m4);
    repo.adaugaMasina(m5);

    assert(repo.getAllMasini().size() == 5);
    assert(repo.getAllMasini()[0].get_nr_inmatriculare() == "BH-04-VLD");
    assert(repo.getAllMasini()[1].get_producator() == "Skoda");
    assert(repo.getAllMasini()[2].get_model() == "Octavia");
    assert(repo.getAllMasini()[3].get_tip() == "Sedan");
    try {
        repo.adaugaMasina(m1);
        assert(false);
    }
    catch (RepoException& except) {
        assert(except.get_msg() == "Masina cu acelasi numar de inmatriculare deja existenta!");

    }
}

void testValidateMasina()
{
    assert(Masina::validateMasina(Masina("BH-04-VLD", "Skoda", "Octavia", "Sedan")) == 0);
    assert(Masina::validateMasina(Masina("BH-04-VLD", "", "Octavia", "Sedan")) == 2);
    assert(Masina::validateMasina(Masina("BH-04-VLD", "Skoda", "", "Sedan")) == 3);
    assert(Masina::validateMasina(Masina("BH-04-VLD", "Skoda", "Octavia", "")) == 4);
    assert(Masina::validateMasina(Masina("BH-04-VL", "Skoda", "Octavia", "Sedan")) == 1);
}

void testStergeMasina()
{
    MasinaRepo repo;
    Masina m1("BH-04-VLD", "Skoda", "Octavia", "Sedan");
    Masina m2("BH-05-VLD", "Skoda", "Octavia", "Sedan");
    Masina m3("BH-06-VLD", "Skoda", "Octavia", "Sedan");
    repo.adaugaMasina(m1);
    repo.adaugaMasina(m2);
    repo.adaugaMasina(m3);
    repo.stergeMasina("BH-05-VLD");
    assert(repo.getAllMasini().size() == 2);
    assert(repo.getAllMasini()[0].get_nr_inmatriculare() == "BH-04-VLD");
    assert(repo.getAllMasini()[1].get_nr_inmatriculare() == "BH-06-VLD");
    try {
        repo.stergeMasina("BH-07-VLD");
        assert(false);
    }
    catch (RepoException& except) {
        assert(except.get_msg() == "Masina cu acest numar de inmatriculare nu exista!");
    }
}

void testModificaMasina()
{
    MasinaRepo repo;
    Masina m1("BH-04-VLD", "Skoda", "Octavia", "Sedan");
    Masina m2("BH-05-VLD", "Skoda", "Octavia", "Sedan");
    Masina m3("BH-06-VLD", "Skoda", "Octavia", "Sedan");
    repo.adaugaMasina(m1);
    repo.adaugaMasina(m2);
    repo.adaugaMasina(m3);
    repo.modificaMasina(Masina("BH-05-VLD", "Skoda", "Octavia", "Combi"));
    assert(repo.getAllMasini()[1].get_tip() == "Combi");
    try {
        repo.modificaMasina(Masina("BH-07-VLD", "Skoda", "Octavia", "Combi"));
        assert(false);
    }
    catch (RepoException& except) {
        assert(except.get_msg() == "Masina cu acest numar de inmatriculare nu exista!");
    }
}

void testAdaugaMasinaService()
{
    MasinaRepo repo;
    ServiceMasina service(repo);
    string nr_inmatriculare = "BH-04-VLD";
    string producator = "Skoda";
    string model = "Octavia";
    string tip = "Sedan";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    nr_inmatriculare = "BH-05-VLD";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    assert(service.getAllMasiniService().size() == 2);
    try {
        service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Masina cu acelasi numar de inmatriculare deja existenta!");
    }
    nr_inmatriculare = "BH-06-VL";
    try {
        service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Numar de inmatriculare invalid!");
    }
    nr_inmatriculare = "BH-06-VLD";
    producator = "";
    try {
        service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Producator invalid!");
    }
    producator = "Skoda";
    model = "";
    try {
        service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Model invalid!");
    }
    model = "Octavia";
    tip = "";
    try {
        service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Tip invalid!");
    }
}

void testStergeMasinaService()
{
    MasinaRepo repo;
    ServiceMasina service(repo);
    string nr_inmatriculare = "BH-04-VLD";
    string producator = "Skoda";
    string model = "Octavia";
    string tip = "Sedan";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    nr_inmatriculare = "BH-05-VLD";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    service.stergeMasinaService("BH-04-VLD");
    assert(service.getAllMasiniService().size() == 1);
    try {
        service.stergeMasinaService("BH-04-VLD");
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Masina cu acest numar de inmatriculare nu exista!");
    }
}

void testModificaMasinaService()
{
    MasinaRepo repo;
    ServiceMasina service(repo);
    string nr_inmatriculare = "BH-04-VLD";
    string producator = "Skoda";
    string model = "Octavia";
    string tip = "Sedan";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    model = "Fabia";
    service.modificaMasinaService(nr_inmatriculare, producator, model, tip);
    assert(service.getAllMasiniService()[0].get_model() == "Fabia");
    model = "Octavia";
    service.modificaMasinaService(nr_inmatriculare, producator, model, tip);
    nr_inmatriculare = "BH-05-VLD";
    try {
        service.modificaMasinaService(nr_inmatriculare, producator, model, tip);
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Masina cu acest numar de inmatriculare nu exista!");
    }
    nr_inmatriculare = "BH-05-VL";
    try {
        service.modificaMasinaService(nr_inmatriculare, producator, model, tip);
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Numar de inmatriculare invalid!");
    }
    nr_inmatriculare = "BH-04-VLD";
    producator = "";
    try {
        service.modificaMasinaService(nr_inmatriculare, producator, model, tip);
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Producator invalid!");
    }
    producator = "Skoda";
    model = "";
    try {
        service.modificaMasinaService(nr_inmatriculare, producator, model, tip);
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Model invalid!");
    }
    model = "Octavia";
    tip = "";
    try {
        service.modificaMasinaService(nr_inmatriculare, producator, model, tip);
        assert(false);
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Tip invalid!");
    }
}

void testRepoExceptionMsg()
{
    try {
        throw RepoException("Mesaj");
    }
    catch (RepoException& except) {
        assert(except.get_msg() == "Mesaj");
    }
}

void testMasinaExceptionMsg()
{
    try {
        throw MasinaException("Mesaj");
    }
    catch (MasinaException& except) {
        assert(except.get_msg() == "Mesaj");
    }
}

void testOperator()
{
    Masina m1("BH-04-VLD", "Skoda", "Octavia", "Sedan");

    const Masina& m2(m1);
    assert(m2.get_nr_inmatriculare() == m1.get_nr_inmatriculare());
    assert(m2.get_producator() == m1.get_producator());
    assert(m2.get_model() == m1.get_model());
    assert(m2.get_tip() == m1.get_tip());

    Masina m3 = m1;
    assert(m3.get_nr_inmatriculare() == m1.get_nr_inmatriculare());
    assert(m3.get_producator() == m1.get_producator());
    assert(m3.get_model() == m1.get_model());
    assert(m3.get_tip() == m1.get_tip());

    m3 = Masina("BH-04-VLD", "Skoda", "Octavia", "Combi");
    assert(m1.get_tip() != m3.get_tip());
}

void testFilterProducator()
{
    MasinaRepo repo;
    ServiceMasina service(repo);
    string nr_inmatriculare = "BH-04-VLD";
    string producator = "Skoda";
    string model = "Octavia";
    string tip = "Sedan";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    nr_inmatriculare = "BH-05-VLD";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    string producator2 = "Dacia";
    nr_inmatriculare = "BH-06-VLD";
    service.adaugaMasinaService(nr_inmatriculare, producator2, model, tip);
    vector<Masina> masini = service.filterMasiniProducer(producator);
    assert(masini.size() == 2);
    assert(masini[0].get_producator() == "Skoda");
    assert(masini[1].get_producator() == "Skoda");
    masini = service.filterMasiniProducer(producator2);
    assert(masini.size() == 1);
    assert(masini[0].get_producator() == "Dacia");
}

void testFilterTip()
{
    MasinaRepo repo;
    ServiceMasina service(repo);
    string nr_inmatriculare = "BH-04-VLD";
    string producator = "Skoda";
    string model = "Octavia";
    string tip = "Sedan";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    nr_inmatriculare = "BH-05-VLD";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    string tip2 = "Combi";
    nr_inmatriculare = "BH-06-VLD";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip2);
    vector<Masina> masini = service.filterMasiniType(tip);
    assert(masini.size() == 2);
    assert(masini[0].get_tip() == "Sedan");
    assert(masini[1].get_tip() == "Sedan");
    masini = service.filterMasiniType(tip2);
    assert(masini.size() == 1);
    assert(masini[0].get_tip() == "Combi");
}

void testSortare()
{
    MasinaRepo repo;
    ServiceMasina service(repo);
    string nr_inmatriculare = "BH-05-VLD";
    string producator = "Skoda";
    string model = "Octavia";
    string tip = "Sedan";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    nr_inmatriculare = "BH-04-VLD";
    producator = "Dacia";
    model = "Logan";
    tip = "Break";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    vector<Masina> lista_sortata = service.sortMasini(sortNrInmatriculare);
    assert(lista_sortata[0].get_nr_inmatriculare() == "BH-04-VLD");
    assert(lista_sortata[1].get_nr_inmatriculare() == "BH-05-VLD");
    lista_sortata = service.sortMasini(sortTip);
    assert(lista_sortata[0].get_tip() == "Break");
    assert(lista_sortata[1].get_tip() == "Sedan");
    lista_sortata = service.sortMasini(sortProducatorModel);
    assert(lista_sortata[0].get_producator() == "Dacia");
    assert(lista_sortata[1].get_producator() == "Skoda");
    nr_inmatriculare = "BH-06-VLD";
    producator = "Dacia";
    model = "Logam";
    tip = "Break";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    lista_sortata = service.sortMasini(sortProducatorModel);
    assert(lista_sortata[0].get_producator() == "Dacia");
    assert(lista_sortata[1].get_producator() == "Dacia");
    assert(lista_sortata[2].get_producator() == "Skoda");
    assert(lista_sortata[0].get_model() == "Logam");
    assert(lista_sortata[1].get_model() == "Logan");
}

void testAssignmentOperator() {
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    // Test deep copy
    vector<int> v2 = v1;
    assert(v2.size() == v1.size());
    for (int i = 0; i < v1.size(); i++) {
        assert(v2[i] == v1[i]);
    }

    // Test original object remains unchanged
    v2.push_back(4);
    assert(v1.size() == 3);
    assert(v2.size() == 4);

    // Test self-assignment
    v2 = v2;
    assert(v2.size() == 4);
    assert(v2[3] == 4);
}

void testSortProducator()
{
    MasinaRepo repo;
    ServiceMasina service(repo);
    string nr_inmatriculare = "BH-05-VLD";
    string producator = "Skoda";
    string model = "Octavia";
    string tip = "Sedan";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    nr_inmatriculare = "BH-04-VLD";
    producator = "Dacia";
    model = "Logan";
    tip = "Break";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    vector<Masina> lista_sortata = service.sortMasini(sortProducator);
    assert(lista_sortata[0].get_producator() == "Dacia");
    assert(lista_sortata[1].get_producator() == "Skoda");
}

void testSortModel()
{
    MasinaRepo repo;
    ServiceMasina service(repo);
    string nr_inmatriculare = "BH-05-VLD";
    string producator = "Skoda";
    string model = "Octavia";
    string tip = "Sedan";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    nr_inmatriculare = "BH-04-VLD";
    producator = "Dacia";
    model = "Logan";
    tip = "Break";
    service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    vector<Masina> lista_sortata = service.sortMasini(sortModel);
    assert(lista_sortata[0].get_model() == "Logan");
    assert(lista_sortata[1].get_model() == "Octavia");
}

void testClearAllManager()
{
    MasinaRepo repo;
	ServiceMasina service(repo);
	Masina m1("BH-04-VLD", "Skoda", "Octavia", "Sedan");
    repo.adaugaMasina(m1);
	service.createManager();
    string nr_inmatriculare = "BH-04-VLD";
	service.adaugaManagerService(nr_inmatriculare);
    assert(service.getAllManager().size() == 1);
	service.clearAllManager();
	assert(service.getAllManager().size() == 0);
}

void testGetAllManager()
{
    MasinaRepo repo;
	ServiceMasina service(repo);
	Masina m1("BH-04-VLD", "Skoda", "Octavia", "Sedan");
    repo.adaugaMasina(m1);
	service.createManager();
	string nr_inmatriculare = "BH-04-VLD";
	service.adaugaManagerService(nr_inmatriculare);
	assert(service.getAllManager().size() == 1);
}

void testAdaugaManager()
{
    MasinaRepo repo;
	ServiceMasina service(repo);
	Masina m1("BH-04-VLD", "Skoda", "Octavia", "Sedan");
    repo.adaugaMasina(m1);
	service.createManager();
	string nr_inmatriculare = "BH-04-VLD";
	service.adaugaManagerService(nr_inmatriculare);
	assert(service.getAllManager().size() == 1);
    service.adaugaManagerService(nr_inmatriculare);
}

void testAdaugaManagerService()
{
    MasinaRepo repo;
	ServiceMasina service(repo);
	Masina m1("BH-04-VLD", "Skoda", "Octavia", "Sedan");
	repo.adaugaMasina(m1);
	service.createManager();
	string nr_inmatriculare = "BH-04-VLD";
	service.adaugaManagerService(nr_inmatriculare);
	assert(service.getAllManager().size() == 1);
    service.adaugaManagerService(nr_inmatriculare);
	nr_inmatriculare = "BH-05-VL";
    try {
		service.adaugaManagerService(nr_inmatriculare);
		assert(false);
	}
    catch (MasinaException& except) {
		assert(except.get_msg() == "Masina cu acest numar de inmatriculare nu exista!");
	}
}

void testGenerateRandom()
{
    MasinaRepo repo;
	ServiceMasina service(repo);
	Masina m1("BH-04-VLD", "Skoda", "Octavia", "Sedan");
	repo.adaugaMasina(m1);
	service.createManager();
	service.generateRandom(1);
	assert(service.getAllManager().size() == 1);
}

void testSetAllowManager()
{
    MasinaRepo repo;
    ServiceMasina service(repo);
    Masina m1("BH-04-VLD", "Skoda", "Octavia", "Sedan");
    service.createManager();
    try {
        service.createManager();
        assert(false);
    }
    catch (MasinaException& except) {
		assert(except.get_msg() == "Managerul este deja creat!");
	}
}

void allTests() {
    cout << "Teste incepute..." << endl;
    testAddRepo();
    testValidateMasina();
    testStergeMasina();
    testModificaMasina();
    testAdaugaMasinaService();
    testStergeMasinaService();
    testModificaMasinaService();
    testRepoExceptionMsg();
    testMasinaExceptionMsg();
    testOperator();
    testFilterProducator();
    testFilterTip();
    testSortare();
    testAssignmentOperator();
    testSortProducator();
    testSortModel();
    testSetAllowManager();
    testAdaugaManager();
    testGetAllManager();
    testClearAllManager();
    testAdaugaManagerService();
    testGenerateRandom();
    cout << "Teste finalizate!" << endl;
}