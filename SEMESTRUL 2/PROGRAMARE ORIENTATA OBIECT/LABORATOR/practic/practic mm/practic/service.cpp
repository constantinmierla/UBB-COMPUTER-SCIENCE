#include "service.h"

void Service::adauga(const string& titlu, const  string& artist, const  string& gen)
{
	int id = repo.id_nou();
	Melodie m{ id,titlu,artist,gen };
	validator.valideaza(m);
	repo.adauga(m);
	//notify();
}

void Service::sterge(int id)
{
	repo.sterge(id);
	//notify();
}

vector<Melodie> Service::sorteaza_autor()
{
	vector<Melodie>sortedvector{ repo.get_all() };
	sort(sortedvector.begin(), sortedvector.end(), [&](const Melodie& m1, const Melodie& m2) {return m1.get_artist() < m2.get_artist(); });
	return sortedvector;
}

int Service::gen(string gen)
{
	map<string, int>rez;
	vector<Melodie>lista = get_all();
	for (const auto& i : lista) {
		if (rez.find(i.get_gen()) != rez.end())
			rez[i.get_gen()]++;
		else
			rez[i.get_gen()] = 1;
	}
	return rez[gen];
}

int Service::artist(string artist)
{
	map<string, int>rez;
	vector<Melodie>lista = get_all();
	for (const auto& i : lista) {
		if (rez.find(i.get_artist()) != rez.end())
			rez[i.get_artist()]++;
		else
			rez[i.get_artist()] = 1;
	}
	return rez[artist];
}
