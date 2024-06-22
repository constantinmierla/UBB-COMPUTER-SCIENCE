#pragma once
#include "domain.h"
#include <vector>

class Repo {
private:
	string filename;
	vector<Produs> all;
	void load_from_file();
	void save_to_file();
public:
	Repo(string& filename) : filename{ filename } {
		load_from_file();
	}
	vector<Produs> get_all() { return this->all; }
	int nr_vocale(Produs& t) {
		int count = 0;
		for (int i = 0; i < t.get_nume().size(); i++)
		{
			if (strchr("aeiouAEIOU", t.get_nume()[i]))
				count++;
		}
		return count;
	}
	void adauga(Produs& t);
	~Repo() = default;
};