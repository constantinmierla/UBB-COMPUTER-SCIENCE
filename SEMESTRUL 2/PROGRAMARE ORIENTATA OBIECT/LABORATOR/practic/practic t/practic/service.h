#pragma once
#include"repo.h"
#include"validator.h"
#include<algorithm>
#include<functional>
#include<vector>
#include<map>
using namespace std;

class Service {
private:
	Repo& repo;
	Validator& validator;
public:
	Service(Repo& repo, Validator& validator) :repo{ repo }, validator{ validator } {};
	
	
	/*
	* Functie de tip vector de tractoare
	* returneaza vectorul de tip tractor
	*/
	vector<Tractor>get_all() { return repo.get_all(); }
	
	
	/*
	* Functie de tip - int
	* Input : tip de tip - string
	* returneaza un map de string si int reprezentand nr de aparitii al tipului
	*/
	int tip(const string& tip);

	int cilindri(const int cil);
	/*
	* Functie de tip vector de Tractoare
	* returneaza un vector de Tractoare sortat crescator dupa denumire
	*/
	vector<Tractor>sortare_denumire();

	/*
	* Functie de tip - map
	* returneaza un map de string si int reprezentand nr de aparitii al tipului
	*/
	map<string, int>returneaza_tip();

	/*
	* Functie care sterge un tractor din vector
	* input : id - de tip intreg reprezentand id ul clasei
	*/
	void sterge(int id);

	/*
	* Functie care modifica un tractor din vector
	* input :	id de tip intreg
				denumire de tip string
				tip de tip string
				cilindri de tip intreg
	*/
	void modifica(int id, const string& denumire, const string& tip, int nr);
	void adauga(int id, const string& denumire, const string& tip, int nr);
};