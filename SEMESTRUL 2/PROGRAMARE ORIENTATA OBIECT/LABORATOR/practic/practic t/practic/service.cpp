#include "service.h"

void Service::adauga(int id, const string& denumire, const string& tip, int nr)
{
	Tractor t{ id,denumire,tip,nr };
	validator.valideaza(t);
	repo.adauga(t);
}

void Service::sterge(int id)
{
	vector<Tractor>rez{ repo.get_all() };
	string tipp;
	string error = "";

	for (auto& i : rez)
	{
		if (i.get_id() == id)
		{
			if (cilindri(i.get_nr()) > 1)
			{
				repo.sterge(id);
				break;
			}
		}
	}
}
int Service::tip(const string& tip)
{
	map < string, int>rez;
	for (const auto& t : get_all()) {
		if (rez.find(t.get_tip()) == rez.end())
			rez[t.get_tip()] = 1;
		else
			rez[t.get_tip()]++;
	}
	return rez[tip];
}
int Service::cilindri(const int cil) {
	map < int, int>rez;
	for (const auto& t : get_all()) {
		if (rez.find(t.get_nr()) == rez.end())
			rez[t.get_nr()] = 1;
		else
			rez[t.get_nr()]++;
	}
	return rez[cil];
}
vector<Tractor> Service::sortare_denumire()
{
	vector<Tractor>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [&](const Tractor& o1, const Tractor& o2) {
		if (o1.get_tip() == o2.get_tip())
		{
			return o1.get_denumire() < o2.get_denumire();
		}
		else { return o1.get_tip() < o2.get_tip(); }});
	return rez;
}

map<string, int> Service::returneaza_tip()
{
	map < string, int>rez;
	for (const auto& t : get_all()) {
		if (rez.find(t.get_tip()) == rez.end())
			rez[t.get_tip()] = 1;
		else
			rez[t.get_tip()]++;
	}
	return rez;
}


void Service::modifica(int id, const string& denumire, const string& tip, int nr)
{
	Tractor t{ id,denumire,tip,nr };
	validator.valideaza_modifica(t);
	repo.modifica(t);
}
