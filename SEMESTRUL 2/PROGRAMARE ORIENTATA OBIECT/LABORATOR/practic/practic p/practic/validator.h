#pragma once
#include"repo.h"
class ValException {
private:
	string msg;
public:
	ValException(const string& msg) :msg{ msg } {};
	//constructor primeste msg-string
	string get_mesaj()const {
		return msg;
	}
	//returneaza mesajul de eroase string
};
class Validator {
private:
	Repo& repo;
public:
	Validator(Repo& repo) :repo{ repo } {}
	//constructor primeste referinta la repo
	void valideaza(const Produs& p);
	//valideaza un produs dupa id,nume,tip,pret
};