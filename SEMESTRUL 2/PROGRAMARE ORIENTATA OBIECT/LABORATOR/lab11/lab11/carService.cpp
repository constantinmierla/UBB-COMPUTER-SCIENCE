#include "carService.h"
#include "carValidator.h"
#include "exception.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include "undo.h"
#include <ios>
#pragma warning( disable : 4244 )
using namespace std;

void CarService::addCar(const string& licensePlate, const string& producer, const string& model, const string& type)
{

	if (repo.find(licensePlate) >= 0)
		throw ExistentCarError("Masina exista deja in baza de date!\n");
	if (validateCar(licensePlate, producer, model, type) == 0)
		throw InvalidCarError("Datele masinii sunt invalide!\n");
	Car newCar{ licensePlate, producer, model, type };

	try
	{
		repo.add(newCar);
		undoActions.push_back(make_unique<UndoAdd>(repo, newCar));
	}

	catch (const float& prob)
	{
		cout << "Probabilitatea este: " << prob << endl;
		undoActions.push_back(make_unique<UndoAdd>(repo, newCar));
	}
}

void CarService::modifyCar(const string& licensePlate, const string& newLicensePlate, const string& newProducer, const string& newModel, const string& newType)
{
	const int position = repo.find(licensePlate);
	if (position < 0)
		throw InexistentCarError("Masina nu exista in baza de date!\n");
	if (validateCar(newLicensePlate, newProducer, newModel, newType) == 0)
		throw InvalidCarError("Datele masinii sunt invalide!\n");
	Car newCar{ newLicensePlate, newProducer, newModel, newType };
	undoActions.push_back(make_unique<UndoModify>(repo, repo.getList().at(position), newCar));

	try
	{
		repo.modify(position, newCar);
	}

	catch (const float& prob)
	{
		cout << "Probabilitatea este: " << prob << endl;
	}
}

void CarService::removeCar(const string& licensePlate)
{
	const int position = repo.find(licensePlate);
	if (position < 0)
		throw InexistentCarError("Masina nu exista in baza de date!\n");
	undoActions.push_back(make_unique<UndoRemove>(repo, repo.getList().at(position)));

	try
	{
		repo.remove(position);
	}

	catch (const float& prob)
	{
		cout << "Probabilitatea este: " << prob << endl;
	}
}

void CarService::undo()
{
	if (undoActions.empty())
		throw EmptyListError("Nu mai exista operatii la care sa executam undo!\n");

	try
	{
		undoActions.back()->doUndo();
		undoActions.pop_back();
	}
	catch (const float& prob)
	{
		cout << "Probabilitatea este: " << prob << endl;
		undoActions.pop_back();
	}

}

const Car CarService::findCar(const string& licensePlate) const
{
	const __int64 position = repo.find(licensePlate);
	if (position < 0)
		throw InexistentCarError("Masina nu exista in baza de date!\n");
	return repo.getList().at(position);
}

const vector<Car> CarService::getCarList() const
{
	return repo.getList();
}

size_t CarService::listSize() const noexcept
{
	return repo.size();
}

vector<Car> CarService::filterByProd(const string& producer) const
{
	vector<Car> filteredList;
	auto& all = repo.getList();
	copy_if(all.begin(), all.end(), back_inserter(filteredList), [producer](const Car& car) { return car.getProducer() == producer; });
	if (filteredList.empty())
		throw EmptyListError("Nu exista masini de acest tip in baza de date!\n");
	return filteredList;
}

vector<Car> CarService::filterByType(const string& type) const
{
	vector<Car> filteredList;
	auto& all = repo.getList();
	copy_if(all.begin(), all.end(), back_inserter(filteredList), [type](const Car& car) { return car.getType() == type; });
	if (filteredList.empty())
		throw EmptyListError("Nu exista masini de acest tip in baza de date!\n");
	return filteredList;
}

vector<Car> CarService::sortByLicPlate(const char& mode) const
{
	vector<Car> sortedList = repo.getList();
	if (mode != 'c' && mode != 'd')
		throw InvalidSortingMode("Mod de sortare invalid!");

	if (mode == 'c')
		sort(sortedList.begin(), sortedList.end(), [](const Car& car1, const Car& car2) { return car1.getLicensePlate() < car2.getLicensePlate(); });
	else
		sort(sortedList.begin(), sortedList.end(), [](const Car& car1, const Car& car2) { return car1.getLicensePlate() > car2.getLicensePlate(); });
	return sortedList;
}

vector<Car> CarService::sortByType(const char& mode) const
{
	vector<Car> sortedList = repo.getList();
	if (mode != 'c' && mode != 'd')
		throw InvalidSortingMode("Mod de sortare invalid!");

	if (mode == 'c')
		sort(sortedList.begin(), sortedList.end(), [](const Car& car1, const Car& car2) { return car1.getType() < car2.getType(); });
	else
		sort(sortedList.begin(), sortedList.end(), [](const Car& car1, const Car& car2) { return car1.getType() > car2.getType(); });
	return sortedList;
}

vector<Car> CarService::sortByProdModel(const char& mode) const
{
	vector<Car> sortedList = repo.getList();
	if (mode != 'c' && mode != 'd')
		throw InvalidSortingMode("Mod de sortare invalid!");

	if (mode == 'c')
		sort(sortedList.begin(), sortedList.end(), [](const Car& car1, const Car& car2)
			{
				if (car1.getProducer() == car2.getProducer())
					return car1.getModel() < car2.getModel();
				else
					return car1.getProducer() < car2.getProducer();
			});

	else
		sort(sortedList.begin(), sortedList.end(), [](const Car& car1, const Car& car2)
			{
				if (car1.getProducer() == car2.getProducer())
					return car1.getModel() > car2.getModel();
				else
					return car1.getProducer() > car2.getProducer();
			});
	return sortedList;
}

void populateCarList(CarService& cs)
{
	cs.addCar("SV-99-CXC", "PASSAT", "B6", "SPORT");
	cs.addCar("SV-21-GBM", "PORSCHE", "911S", "SPORT");
	cs.addCar("SV-01-ADL", "MERCEDES", "ACLASS", "MINI");
	cs.addCar("SV-25-BNC", "AUDI", "Q5", "SUV");
	cs.addCar("SV-68-PPR", "RENAULT", "MEGAN", "ALTELE");
}

void CarService::addWash(const string& licensePlate)
{
	if (validateLicensePlate(licensePlate) == 0)
		throw InvalidLicensePlate("Numarul de inmatriculare al masinii este invalid!\n");
	try
	{
		const Car& car = findCar(licensePlate);
		washRepo.add(car);
		notify();
	}
	catch (const Error& error)
	{
		throw error;
	}
}

void CarService::emptyWash()
{
	while (washRepo.size())
	{
		washRepo.remove(0);
	}
	notify();
}

void CarService::populateWash(size_t number)
{
	if (number > listSize())
		throw InvalidGenerateNumber("Numarul de masini de generat este prea mare!\n");
	vector<Car> copyCarList = repo.getList();
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(copyCarList.begin(), copyCarList.end(), default_random_engine(seed));
	for (size_t i = 0; i < number; i++)
	{
		washRepo.add(copyCarList.at(i));
	}
	notify();
}

map<string, int> CarService::report() const
{
	map<string, int> rep;
	for (auto& car : repo.getList())
	{
		auto it = rep.find(car.getType());
		if (it != rep.end())
			rep[car.getType()]++;
		else
			rep.insert(pair<string, int>(car.getType(), 1));
	}
	return rep;
}

void CarService::exportCSV(const string& fileName)
{
	ofstream out;
	out.open(fileName, ios::trunc);
	if (!out.is_open())
		throw InvalidFileError("Fisierul nu a putut fi deschis!\n");
	for (const auto& car : washRepo.getList())
		out << car.getLicensePlate() << ',' << car.getProducer() << ',' << car.getModel() << ',' << car.getType() << '\n';
	out.close();
}

void CarService::exportHTML(const string& fileName)
{
	ofstream out;
	out.open(fileName, ios::trunc);
	if (!out.is_open())
		throw InvalidFileError("Fisierul nu a putut fi deschis!\n");
	out << "<html><body>" << endl << "<table border=\"1\" style=\"width:100 % \">" << endl;
	for (const auto& car : washRepo.getList())
		out << "<tr>" << endl << "<td>" << car.getLicensePlate() << "</td>" << endl << "<td>" << car.getProducer() << "</td>" << endl << "<td>" << car.getModel() << "</td>" << endl << "<td>" << car.getType() << "</td>" << endl << "</tr>" << endl;
	out << "</table>" << endl << "</body></html>" << endl;
	out.close();
}

void testService()
{
	CarRepo repo;
	CarRepo washRepo;
	CarService service{ repo, washRepo };

	// incercam sa executam undo fara operatii
	try
	{
		service.undo();
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Nu mai exista operatii la care sa executam undo!\n");
	}

	// adaugam cateva masini
	service.addCar("AG-12-AAA", "RENAULT", "CLIO", "ALTELE");
	service.addCar("CJ-01-AGH", "OPEL", "CORSA", "SPORT");
	service.addCar("AB-98-GTR", "TOYOTA", "COROLLA", "SUV");
	service.addCar("TR-45-POL", "RENAULT", "ZOE", "SPORT");
	service.addCar("SV-10-BBB", "RENAULT", "MEGAN", "SPORT");

	// executam undo la adauga
	service.undo();
	service.addCar("SV-10-BBB", "RENAULT", "MEGAN", "SPORT");

	// incercam sa adaugam o masina invalida
	try
	{
		service.addCar("TEST", "TEST", "TEST", "TEST");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Datele masinii sunt invalide!\n");
	}

	// incercam sa adaugam o masina deja existenta
	try
	{
		service.addCar("AG-12-AAA", "RENAULT", "CLIO", "ALTELE");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Masina exista deja in baza de date!\n");
	}

	// verificam ca s-au adaugat masinile valide
	assert(service.getCarList().at(0).getLicensePlate() == "AG-12-AAA");
	assert(service.getCarList().at(0).getProducer() == "RENAULT");
	assert(service.getCarList().at(0).getModel() == "CLIO");
	assert(service.getCarList().at(0).getType() == "ALTELE");

	// verificam ca s-a modificat masina
	service.modifyCar("AG-12-AAA", "CJ-00-BGG", "SKODA", "FABIA", "SUV");
	assert(service.getCarList().at(0).getLicensePlate() == "CJ-00-BGG");
	assert(service.getCarList().at(0).getProducer() == "SKODA");
	assert(service.getCarList().at(0).getModel() == "FABIA");
	assert(service.getCarList().at(0).getType() == "SUV");

	// executam undo la modificare
	service.undo();
	service.modifyCar("AG-12-AAA", "CJ-00-BGG", "SKODA", "FABIA", "SUV");

	// incercam sa modificam o masina inexistenta
	try
	{
		service.modifyCar("AA-00-AA", "AA-00-AAA", "PROD", "MODEL", "ALTELE");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Masina nu exista in baza de date!\n");
	}

	// incercam sa modificam o masina cu date invalide
	try
	{
		service.modifyCar("CJ-00-BGG", "TEST", "TEST", "TEST", "TEST");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Datele masinii sunt invalide!\n");
	}

	// cautam o masina existenta
	Car testCar;
	testCar = service.findCar("CJ-00-BGG");
	assert(testCar.getLicensePlate() == "CJ-00-BGG");
	assert(testCar.getProducer() == "SKODA");
	assert(testCar.getModel() == "FABIA");
	assert(testCar.getType() == "SUV");

	// cautam o masina inexistenta
	try
	{
		testCar = service.findCar("CS-01-AAA");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Masina nu exista in baza de date!\n");
	}

	// stergem o masina si verificam ca s-a micsorat marimea
	service.removeCar("CJ-00-BGG");
	assert(service.listSize() == 4);

	// incercam sa stergem o masina inexistenta
	try
	{
		service.removeCar("AA-00-AAA");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Masina nu exista in baza de date!\n");
	}

	// incercam sa executam undo
	service.undo();

	// verificam ca s-a adaugat masina inapoi
	assert(service.listSize() == 5);

	// stergem masina adaugata
	service.removeCar("CJ-00-BGG");


	// teste pentru filtrarea dupa producator
	// testam cu un producator de masini existent in lista
	vector<Car> carList = service.filterByProd("RENAULT");
	assert(carList.size() == 2);
	assert(carList.at(0).getLicensePlate() == "TR-45-POL");
	assert(carList.at(0).getProducer() == "RENAULT");
	assert(carList.at(0).getModel() == "ZOE");
	assert(carList.at(0).getType() == "SPORT");


	// testam cu un producator de masini inexistent in lista
	try
	{
		carList = service.filterByProd("FORD");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Nu exista masini de acest tip in baza de date!\n");
	}

	// teste pentru filtrarea dupa tip
	// testam cu un tip de masini existent in lista
	carList = service.filterByType("SPORT");
	assert(carList.size() == 3);
	assert(carList.at(0).getLicensePlate() == "CJ-01-AGH");
	assert(carList.at(0).getProducer() == "OPEL");
	assert(carList.at(0).getModel() == "CORSA");
	assert(carList.at(0).getType() == "SPORT");

	// testam cu un tip de masini inexistent in lista
	try
	{
		carList = service.filterByType("ALTELE");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Nu exista masini de acest tip in baza de date!\n");
	}

	// sortam descrescator dupa numarul de inmatriculare
	carList = service.sortByLicPlate('d');
	assert(carList.at(0).getLicensePlate() == "TR-45-POL");

	// sortam crescator dupa numarul de inmatriculare
	carList = service.sortByLicPlate('c');
	assert(carList.at(0).getLicensePlate() == "AB-98-GTR");

	// incercam sa sortam folosind un mod incorect
	try
	{
		carList = service.sortByLicPlate('g');
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Mod de sortare invalid!");
	}

	// sortam descrescator dupa tip
	carList = service.sortByType('d');
	assert(carList.at(0).getType() == "SUV");

	// sortam crescator dupa tip
	carList = service.sortByType('c');
	assert(carList.at(0).getType() == "SPORT");

	// incercam sa sortam folosind un mod incorect
	try
	{
		carList = service.sortByType('g');
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Mod de sortare invalid!");
	}

	// sortam descrescator dupa producator + model
	carList = service.sortByProdModel('d');
	assert(carList.at(0).getProducer() == "TOYOTA");

	// sortam crescator dupa producator + model
	carList = service.sortByProdModel('c');
	assert(carList.at(0).getProducer() == "OPEL");

	// incercam sa sortam folosind un mod incorect
	try
	{
		carList = service.sortByProdModel('g');
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Mod de sortare invalid!");
	}

	// testam functia de generat raport
	map<string, int>mp = service.report();
	assert(mp["SPORT"] == 3);


	// testam functionalitatile clasei WashService
	assert(service.washSize() == 0);

	// adaugam o masina existenta
	service.addWash("AB-98-GTR");
	assert(service.washSize() == 1);
	assert(service.getWashList().at(0).getLicensePlate() == "AB-98-GTR");
	assert(service.getWashList().at(0).getProducer() == "TOYOTA");
	assert(service.getWashList().at(0).getModel() == "COROLLA");
	assert(service.getWashList().at(0).getType() == "SUV");

	// incercam sa adaugam o masina inexistenta
	try
	{
		service.addWash("AA-00-AAA");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Masina nu exista in baza de date!\n");
	}

	// incercam sa adaugam o masina cu numar de inmatriculare invalid
	try
	{
		service.addWash("TEST");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Numarul de inmatriculare al masinii este invalid!\n");
	}

	// stergem toate masinile din lista de spalat
	service.emptyWash();
	assert(service.washSize() == 0);

	// generam masini de spalat
	service.populateWash(2);
	assert(service.washSize() == 2);

	// incercam sa generam prea multe masini de spalat
	try
	{
		service.populateWash(10);
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Numarul de masini de generat este prea mare!\n");
	}

	// incercam sa exportam in fisier CSV
	try
	{
		service.exportCSV("/test.csv");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Fisierul nu a putut fi deschis!\n");
	}

	// incercam sa exportam in fisier HTML
	try
	{
		service.exportHTML("/test.html");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Fisierul nu a putut fi deschis!\n");
	}

	ofstream outCSV("test.csv", ios::trunc);
	ofstream outHTML("test.html", ios::trunc);
	service.emptyWash();

	// adaugam o masina in lista de spalat si o exportam in CSV
	service.addWash("AB-98-GTR");
	service.exportCSV("test.csv");
	ifstream inCSV("test.csv");
	string testString;
	inCSV >> testString;
	assert(testString == "AB-98-GTR,TOYOTA,COROLLA,SUV");

	// adaugam o masina in lista de spalat si o exportam in HTML
	service.exportHTML("test.html");
	ifstream inHTML("test.html");
	inHTML >> testString;
	assert(testString == "<html><body>");

	// construim un maprepo si un mapservice
	MapRepo maprepo{ 0.2F };
	CarService mapservice{ maprepo, washRepo };

	// adaugam o masina
	mapservice.addCar("AA-01-ABC", "PROD", "MODEL", "SUV");
	assert(mapservice.listSize() == 1);

	// executam undo
	mapservice.undo();
	assert(mapservice.listSize() == 0);

	// adaugam din nou masina
	mapservice.addCar("AA-01-ABC", "PROD", "MODEL", "SUV");
	assert(mapservice.listSize() == 1);

	// modificam si apoi stergem masina
	mapservice.modifyCar("AA-01-ABC", "AB-01-ABC", "PROD", "MODEL", "ALTELE");
	mapservice.removeCar("AB-01-ABC");
	assert(mapservice.listSize() == 0);
}
