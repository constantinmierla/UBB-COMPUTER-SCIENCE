#pragma once
#include <iostream>
#include <cstring>
using namespace std;

class Produs {
private:
	int id;
	string nume;
	string tip;
	double pret;
public:
	Produs(int id, string nume, string tip, double pret) : id{ id }, nume{ nume }, tip{ tip }, pret{ pret } {};
	~Produs() = default;


	int get_id() { return this->id; }
	string get_nume() { return this->nume; }
	string get_tip() { return this->tip; }
	double get_pret() { return this->pret; }

	void set_id() { this->id = id; }
	void set_nume() { this->nume = nume; }
	void set_tip() { this->tip = tip; }
	void set_pret() {  this->pret = pret; }

};