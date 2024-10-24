#include "serv.h"
#include <map>
void Service::adauga(int id, const string& denumire, const string& tip, int nr) {
	Tractor t = Tractor(id, denumire, tip, nr);
	validator.valideaza(t);
	repo.adauga(t);
}
vector <Tractor> Service::filtrare(const string& tip) {
	vector<Tractor> r = getAll();
	vector<Tractor> rez;
	copy_if(r.begin(), r.end(), back_inserter(rez), [tip](const Tractor& t) {
		return t.get_tip() == tip;
		});
	return rez;
}
int Service::tip(const string& tip) {
	map<string, int> m;
	for (const auto& i : getAll())
	{
		if (m.find(i.get_tip()) == m.end())
			m[i.get_tip()] = 1;
		else
			m[i.get_tip()]++;
	}
	return m[tip];
}
vector<Tractor> Service::sortare(){
	vector<Tractor> al = repo.get_all();
	sort(al.begin(), al.end(), [&](const Tractor& t1, const Tractor& t2) {
		return t1.get_denumire() < t2.get_denumire();
		});
	return al;
}
map<string, int> Service::returneaza(){
	map<string, int> rez;
	for (auto& t : getAll())
	{
		if (rez.find(t.get_tip()) == rez.end())
			rez[t.get_tip()] = 1;
		else
			rez[t.get_tip()]++;

	}
	return rez;
}
void Service::modifica(int idd, const string& denumire, const string& tip, int nr) {
	Tractor t = Tractor(idd, denumire, tip, nr);
	validator.valideaza_modifica(t);
	repo.modifica(t);
}