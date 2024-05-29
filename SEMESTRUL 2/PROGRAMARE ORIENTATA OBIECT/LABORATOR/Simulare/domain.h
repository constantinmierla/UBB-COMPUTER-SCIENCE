#pragma once
#include <string>
using namespace std;
class Produs {
private:
	int cod;
	string denumire;
	int numar;
	int pret;
public:
	Produs(int cod, string denumire, int numar, int pret) : cod{ cod }, denumire{ denumire }, numar{ numar }, pret{ pret } {};
	int get_cod();
	string get_denumire();
	int get_numar();
	int get_pret();
	void set_numar(int numar);
};