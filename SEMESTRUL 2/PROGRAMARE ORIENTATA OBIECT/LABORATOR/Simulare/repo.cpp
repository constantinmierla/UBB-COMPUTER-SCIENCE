#include "repo.h"

void Repo::load_file()
{
	all.clear();
	int cod;
	string denumire;
	int numar;
	int pret;
	ifstream in(filename);
	while (in >> cod >> denumire >> numar >> pret)
	{
		auto q = Produs(cod, denumire, numar, pret);
		all.push_back(q);
	}
	in.close();
}