#include "car.h"
#include <cassert>

void testDomain()
{
	// crearea unui obiect de tip Car
	Car testCar{ "CT-01-ABC","SUZUKI","VITARA","altele" };
	assert(testCar.getLicensePlate() == "CT-01-ABC");
	assert(testCar.getProducer() == "SUZUKI");
	assert(testCar.getModel() == "VITARA");
	assert(testCar.getType() == "altele");

	Car testCar2 = testCar;
	assert(testCar2.getLicensePlate() == "CT-01-ABC");
	assert(testCar2.getProducer() == "SUZUKI");
	assert(testCar2.getModel() == "VITARA");
	assert(testCar2.getType() == "altele");
}