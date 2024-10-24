#include "service.h"

void Service::adauga(int id, string nume, string tip, double pret) {
	//valideaza
	Produs t = Produs(id, nume, tip, pret);
	repo.adauga(t);
}
vector<Produs> Service::sortare()
{
	vector<Produs> p = getallserv();
	sort(p.begin(), p.end(), [&](Produs p1, Produs p2) {
		return p1.get_pret() < p2.get_pret();
		});
	return p;
}
