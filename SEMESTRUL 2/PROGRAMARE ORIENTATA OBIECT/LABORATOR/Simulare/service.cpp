#include "service.h"

vector<Produs> Service::get_all()
{
	return r.getall();
}

vector<Produs> sortarepret(vector<Produs> p) {
	sort(p.begin(), p.end(), [&](Produs p1, Produs p2) {
		return p1.get_pret() < p2.get_pret();
		});
	return p;
}
vector<Produs> sortarenumar(vector<Produs> p) {
	sort(p.begin(), p.end(), [&](Produs p1, Produs p2) {
		return p1.get_numar() < p2.get_numar();
		});
	return p;
}