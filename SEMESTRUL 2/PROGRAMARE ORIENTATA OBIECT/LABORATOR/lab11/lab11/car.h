#pragma once
#include <string>
#include <iostream>
using namespace std;
class Car
{
private:
	// numarul de inmatriculare al masinii
	string licensePlate;

	// producatorul masinii
	string producer;

	// modelul masinii
	string model;

	//tipul masinii
	string type;

public:
	// constructorul unui obiect de tip masina
	Car(const string l, const string p, const string m, const string t) : licensePlate{ l }, producer{ p }, model{ m }, type{ t } {};

	// constructor unui obiect de tip masina fara argumente
	Car() :licensePlate{ "" }, producer{ "" }, model{ "" }, type{ "" } {};

	// getter pentru numarul de inmatriculare al masinii
	string getLicensePlate() const
	{
		return licensePlate;
	}

	// getter pentru producatorul masinii
	string getProducer() const
	{
		return producer;
	}

	// getter pentru modelul masinii
	string getModel() const
	{
		return model;
	}

	// getter pentru tipul masinii
	string getType() const
	{
		return type;
	}

	// copy constructor
	Car(const Car& c) : licensePlate{ c.licensePlate }, producer{ c.producer }, model{ c.model }, type{ c.type } {}

	// copy assignment
	// copiaza masina din car in this
	Car& operator=(const Car& car)
	{
		licensePlate = car.getLicensePlate();
		producer = car.getProducer();
		model = car.getModel();
		type = car.getType();
		return *this;
	}

	// move constructor
	// se apeleaza cand construim o masina noua dintr-un r-value (ex la return)
	Car(Car&& source)
	{
		licensePlate = source.getLicensePlate();
		producer = source.getProducer();
		model = source.getModel();
		type = source.getType();
	}

	// move assignment
	Car& operator=(Car&& source)
	{
		licensePlate = source.getLicensePlate();
		producer = source.getProducer();
		model = source.getModel();
		type = source.getType();
		return *this;
	}

	~Car() = default;

};
// testele pentru Domain
void testDomain();