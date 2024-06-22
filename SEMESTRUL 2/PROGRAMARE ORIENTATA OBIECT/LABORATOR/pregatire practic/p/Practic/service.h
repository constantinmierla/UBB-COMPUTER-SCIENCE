#pragma once
#include "repo.h"
#include <algorithm>
class Service {
private:
	Repo& repo;
	//Validator& val;
public:
	Service(Repo& repo) : repo{ repo } {};
	~Service() = default;

	void adauga(int id, string nume, string tip, double pret);
	vector<Produs> getallserv() { return repo.get_all(); }
	vector<Produs> sortare();
};