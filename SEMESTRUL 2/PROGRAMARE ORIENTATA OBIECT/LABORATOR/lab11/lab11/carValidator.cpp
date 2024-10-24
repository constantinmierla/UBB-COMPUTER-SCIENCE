#include "car.h"
#include <ctype.h>
#include <cassert>
int validateLicensePlate(string licensePlate)
{
	// validam numarul de inmatriculare
	// este de forma XX-00-XXX, unde X poate sa fie orice majuscula, iar 0 orice litera

	if (licensePlate.size() != 9)
		return 0;

	if ((isupper(licensePlate.at(0)) == 0 || isupper(licensePlate.at(1)) == 0 || isupper(licensePlate.at(6)) == 0) &&
		(isupper(licensePlate.at(7)) == 0 || isupper(licensePlate.at(8)) == 0 || isdigit(licensePlate.at(3)) == 0) &&
		(isdigit(licensePlate.at(4)) == 0 || licensePlate.at(2) != '-' || licensePlate.at(5) != '-'))
		return 0;
	return 1;
}

int validateModel(string model)
{
	// validam modelul
	// trebuie sa contina doar majuscule si cifre

	for (size_t i = 0; i < model.size(); i++)
		if (isupper(model.at(i)) == 0 && isdigit(model.at(i)) == 0)
			return 0;
	return 1;
}

int validateProducer(string producer)
{
	// validam producatorul
	// trebuie sa contina doar majuscule

	for (size_t i = 0; i < producer.size(); i++)
		if (isupper(producer.at(i)) == 0)
			return 0;
	return 1;
}

int validateType(string type)
{
	// validam tipul
	// tipul poate fi doar MINI, SUV, SPORT, ALTELE

	if (type != "MINI" && type != "SUV" && type != "SPORT" && type != "ALTELE")
		return 0;
	return 1;
}

int validateCar(string licensePlate, string producer, string model, string type)
{
	if (validateLicensePlate(licensePlate) && validateProducer(producer) && validateModel(model)
		&& validateType(type))
		return 1;
	return 0;
}

void testValidateCar()
{
	// testam functia de validare 
	// mai intai cu o masina valida
	// apoi cu cate o masina care sa contina cate un atribut invalid

	assert(validateCar("CT-98-AGH", "FIAT", "PUNTO", "ALTELE") == 1);
	assert(validateCar("CT-99-AGHH", "FIAT", "PUNTO", "ALTELE") == 0);
	assert(validateCar("78-CT-AGH", "FIAT", "PUNTO", "ALTELE") == 0);
	assert(validateCar("CT-98-AGH", "fiat", "PUNTO", "ALTELE") == 0);
	assert(validateCar("CT-98-AGH", "FIAT", "punto", "ALTELE") == 0);
	assert(validateCar("CT-98-AGH", "FIAT", "PUNTO", "altele") == 0);
}

