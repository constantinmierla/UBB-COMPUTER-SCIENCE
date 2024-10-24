#pragma once
#include <string>

// validarea numarului de inmatriculare
int validateLicensePlate(std::string licensePlate);

// validarea modelului
int validateModel(std::string model);

// validarea producatorului
int validateProducer(std::string producer);

// validarea tipului
int validateType(std::string type);

// validarea unei masini
int validateCar(std::string licensePlate, std::string producer, std::string model, std::string type);

// teste pentru validator
void testValidateCar();