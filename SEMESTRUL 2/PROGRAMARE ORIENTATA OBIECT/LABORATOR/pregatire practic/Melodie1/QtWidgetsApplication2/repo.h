#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include <fstream>
class Repo {
private:
	string filename;
	vector<Tractor> all;
	void load_from_file();
	void save_to_file();
public:
	Repo(const string& filename) : filename{ filename } {
		load_from_file();
	}
	void adauga(const Tractor& t);
	vector<Tractor> get_all() { return this->all; }
	void sterge(int id);
	void modifica(Tractor& t);
};