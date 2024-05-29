#pragma once
#include "repo.h"
#include <algorithm>
class Service {
private:
	Repo& r;
public:
	Service(Repo& r) : r{ r } {		
	}
	vector<Produs> get_all();
	vector<Produs> sortarepret(vector<Produs> p);
	vector<Produs> sortarenumar(vector<Produs> p);
};