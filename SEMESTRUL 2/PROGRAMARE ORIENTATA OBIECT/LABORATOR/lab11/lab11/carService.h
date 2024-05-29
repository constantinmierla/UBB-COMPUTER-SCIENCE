#pragma once
#include "car.h"
#include "carRepo.h"
#include "undo.h"
#include <vector>
#include <string>
#include <map>
#include "observer.h"
using namespace std;

class CarService : public Observable
{
private:
	// repository-ul curent

	AbstractRepo& repo;
	//CarRepo& repo;
	CarRepo& washRepo;

	// lista de actiuni de undo
	vector<unique_ptr<UndoAction>> undoActions;

public:
	// constructorul clasei Service
	CarService(AbstractRepo& cR, CarRepo& wR) noexcept : repo{ cR }, washRepo{ wR } {};

	// impiedicam crearea de noi obiecte de tip Service
	CarService(const CarService& cS) = delete;

	// getter pentru lista curenta de masini
	const vector<Car> getCarList() const;

	// adaugarea unei masini in lista
	void addCar(const string& licensePlate, const string& producer, const string& model, const string& type);

	// modificarea unei masini din lista
	void modifyCar(const string& licensePlate, const string& newLicensePlate, const string& newProducer, const string& newModel, const string& newType);

	// stergerea unei masini din lista
	void removeCar(const string& licensePlate);

	// cautarea unei masini in lista
	const Car findCar(const string& licensePlate) const;

	// getter pentru lungimea listei
	size_t listSize() const noexcept;

	// filtrare dupa producator
	vector<Car> filterByProd(const string& producer) const;

	// filtrare dupa tip
	vector<Car> filterByType(const string& type) const;

	// sortare dupa numarul de inmatriculare
	vector<Car> sortByLicPlate(const char& mode) const;

	// sortare dupa tip
	vector<Car> sortByType(const char& mode) const;

	// sortare dupa producator + model
	vector<Car> sortByProdModel(const char& mode) const;

	// creeaza raport
	map<string, int> report() const;

	// destructorul clasei Service
	~CarService() = default;

	// executam operatia de undo
	void undo();

	// adaugam o masina noua in lista de spalat
	void addWash(const string& licensePlate);

	// golim lista de spalat
	void emptyWash();

	// populam lista de spalat cu un numar dat de masini
	void populateWash(size_t number);

	// getter pentru lungimea listei de spalat
	size_t washSize() noexcept
	{
		return washRepo.size();
	}

	// getter pentru lista de spalat
	const vector<Car> getWashList()
	{
		return washRepo.getList();
	}

	// exporta lista de masini care trebuie spalate in .csv
	void exportCSV(const string& fileName);

	// exporta lista de masini care trebuie spalate in .html
	void exportHTML(const string& fileName);

};

// teste pentru Service
void testService();

void populateCarList(CarService& cs);