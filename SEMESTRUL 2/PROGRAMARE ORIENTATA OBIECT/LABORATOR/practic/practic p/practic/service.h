#pragma once
#include"repo.h"
#include"validator.h"
#include<algorithm>
#include"observer.h"
#include<algorithm>
#include<map>
#include"undo.h"
class Service :public Observable {
private:
	Repo& repo;
	Validator& val;
	vector<unique_ptr<Undo>>UndoAction;
public:
	Service(Repo& repo, Validator& validator) :repo{ repo }, val{ validator } {};
	//constructor service primeste referinte de la repo si validator
	vector<Produs>get_all() { return repo.get_all(); }
	//returneaza vectorul de produse
	vector<Produs>sorteaza();
	//sorteaza vectroul dupa numarul de vocale;
	int nr_vocale(string text);
	//retruneaza numarul de vocale dintr un string -text
	void adauga(const int id, const string& denumire, const string& tip, const double pret);
	//adaga un obiect in vector si il valideaza mai intai
	int numar(const string text);
	//returneaza numarul de elemente din vectorul cu tipul text-string
	map<string, int>tipuri();
	//returneaza un dictionar cu toate tipurile existente si frecventa lor
	void undo();
	//reface ultima operatie
};