#include "service.h"

void Service::modifica(int id, string titlu, string artist, int rank)
{
	Melodie m{ id,titlu,artist,rank };
	val.valideaza(m);
	repo.modifica(m);
}

void Service::sterge(int id)
{
	repo.sterge(id);
}

vector<Melodie> Service::sorteaza_rank()
{
	vector<Melodie>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [&](const Melodie& o1, const Melodie& o2) {return o1.get_rank() < o2.get_rank(); });
	return rez;
}

int Service::rank(int r)
{
	map<int, int>rez;
	for (auto& m : get_all())
	{
		rez[m.get_rank()]++;

	}
	return rez[r];
}
