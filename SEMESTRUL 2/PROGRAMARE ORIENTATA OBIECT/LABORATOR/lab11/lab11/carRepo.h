#pragma once
#include "car.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

class FloatException : public std::exception {
public:
	FloatException(float value) : value(value) {}

	const char* what() const noexcept override {
		return "Probabilitatea este";
	}

	float getValue() const {
		return value;
	}

private:
	float value;
};

class AbstractRepo
{
public:
	AbstractRepo() = default;
	virtual void add(const Car& c) = 0;
	virtual void modify(const __int64& position, const Car& newCar) = 0;
	virtual void remove(const __int64& position) = 0;
	virtual __int64 find(const string& licensePlate) const = 0;
	virtual size_t size() const noexcept = 0;
	virtual const vector<Car> getList() const = 0;
	virtual ~AbstractRepo() = default;
};


class MapRepo : public AbstractRepo
{
private:
	// dictionarul care retine masinile
	map<size_t, Car> dict = {};

	// probabilitatea
	float prob;

public:
	// constructorul clasei MapRepo
	MapRepo(const float& prob) : prob{ prob } {};

	// adaugarea unei masini in dict
	void add(const Car& c) override
	{
		dict.insert(pair<size_t, Car>(dict.size(), c));
		if(prob > 1)
			throw FloatException(prob);
	}
	virtual vector<Car> getWashedCars() const
	{
		vector<Car> list = {};
		for (auto& pair : dict)
			list.push_back(pair.second);
		return list;
	}
	// stergerea unei masini din dict
	void remove(const __int64& position) override
	{
		dict.erase(position);
		throw prob;
	}

	// modificarea unei masini din dict
	void modify(const __int64& position, const Car& newCar) override
	{
		dict.at(position) = newCar;
		if(prob> 1)
			throw FloatException(prob);
	}

	// cautarea unei masini in dict
	__int64 find(const string& licensePlate) const override
	{
		for (auto& pair : dict)
			if (pair.second.getLicensePlate() == licensePlate)
				return __int64(pair.first);
		return -1;
	}

	// lungimea dictionarului
	size_t size() const noexcept override
	{
		return dict.size();
	}

	// getter pentru lista de masini
	const vector<Car> getList() const override
	{
		vector<Car> list = {};
		for (auto& pair : dict)
			list.push_back(pair.second);
		return list;
	}

	~MapRepo() override = default;
};


class CarRepo : public AbstractRepo
{
private:
	vector<Car> carList = {};

public:
	// constructorul clasei repository
	CarRepo() noexcept = default;

	// impiedicam crearea de noi obiecte repository
	CarRepo(const CarRepo& c) = delete;

	// adaugarea unei masini in vector
	void add(const Car& c) override;

	// modificarea unei masini din vector
	void modify(const __int64& position, const Car& newCar) override;

	// stergerea unei masini din vector
	void remove(const __int64& position) override;

	// cautarea unei masini in vector
	__int64 find(const string& licensePlate) const override;

	// getter pentru lista curenta de masini
	const vector<Car> getList() const override;

	// getter pentru lungimea listei
	size_t size() const noexcept override;

	// destructorul clasei repository
	~CarRepo() = default;
};


// teste pentru Repository
void testRepo();