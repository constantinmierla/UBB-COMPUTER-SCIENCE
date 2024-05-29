#pragma once
#include "domain.h"
#include <vector>
#include <fstream>
class Repo {
private:
	string filename;
	void load_file();
	vector<Produs> all;
public:
	Repo(string filename) : filename{ filename } {
		load_file();
	}
	vector<Produs> getall() {return all;}
	
};