#include "domain.h"

int Produs::get_cod() {
	return this->cod;
}
string Produs::get_denumire()
{
	return this->denumire;
}
int Produs::get_numar() {
	return this->numar;
}
int Produs::get_pret() {
	return this->pret;
}
void Produs::set_numar(int numar)
{
	this->numar = numar - 1;
}