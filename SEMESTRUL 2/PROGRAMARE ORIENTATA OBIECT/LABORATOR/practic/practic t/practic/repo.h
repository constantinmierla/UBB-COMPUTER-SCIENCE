#pragma once
#include"domeniu.h"
#include<vector>
#include<sstream>
#include<fstream>
#include<string.h>

class Repo {
private:
	string fisier;
	vector<Tractor>tractoare;

	/*
	* Incarcam datele din fisierul txt in vectorul tractoare
	*/
	void load_from_file();

	/*
	* Incarcam datele din vector in fisierul txt
	*/
	void write_to_file();

public:
	Repo(const string& fisier) :fisier{ fisier } {
		load_from_file();
	}

	/*
	* Adauga Tractorul in vector
	* input : t - de tip Tractor
	*/
	void adauga(const Tractor& t);

	/*
	* Functie de tip vector de tractoare
	* returneaza vectorul de tip tractor
	*/
	vector<Tractor>get_all()const {
		return tractoare;
	}

	/*
	* Functie care sterge un tractor din vector
	* input : id - de tip intreg reprezentand id ul clasei
	*/
	void sterge(int id);

	/*
	* Functie care modifica un tractor din vector
	* input : t - de tip Tractor
	*/
	void modifica(Tractor& t);
};