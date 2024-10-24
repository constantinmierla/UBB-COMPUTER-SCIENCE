#pragma once
#include "repo.h"
#include "validator.h"
#include <map>
#include <algorithm>
using namespace std;

class Service {
private:
	Repo& repo;
	Validator& validator;
public:
	Service(Repo& repo, Validator& validator) : repo{ repo }, validator{ validator } {};
	void adauga(int id, const string& denumire, const string& tip, int nr);
	vector<Tractor> getAll() { return repo.get_all(); }
	vector <Tractor> filtrare(const string& tip);
	int tip(const string& tip);
	vector<Tractor> sortare();
	map<string, int> returneaza();
	void modifica(int idd, const string& denumire, const string& tip, int nr);
};