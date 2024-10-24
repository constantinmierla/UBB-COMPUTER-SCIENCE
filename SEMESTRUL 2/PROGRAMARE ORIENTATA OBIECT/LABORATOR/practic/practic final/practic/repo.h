#pragma once
#include "domeniu.h"
#include <vector>
class Repo {
private:
	string filename;
	vector<Tractor> all;
	void load_from_file();
	void save_to_file();
public:
	Repo(string filename) : filename{ filename } {
		load_from_file();
	}

	void adauga(Tractor t)
	{
		//validare
		all.push_back(t);
	}
	void modifica(Tractor t);
};