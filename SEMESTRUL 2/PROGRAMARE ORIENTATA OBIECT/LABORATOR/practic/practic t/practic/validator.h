#pragma once
#include "repo.h"

class ValException {
private:
	string msg;
public: ValException(string& msg) :msg{ msg } {};
	  /*
	  * Functie care returneaza mesaj de tip string
	  */
	  string get_mesaj() { return msg; }
};
class Validator {
private:
	Repo& repo;
public:
	Validator(Repo& repo) :repo{ repo } {};

	/*
	* Functie care valideaza datele
	*/
	void valideaza(const Tractor& t);

	/*
	* Functie care valideaza datele
	*/
	void valideaza_sterge(int id);
	
	/*
	* Functie care valideaza datele
	*/
	void valideaza_modifica(const Tractor& t);
};