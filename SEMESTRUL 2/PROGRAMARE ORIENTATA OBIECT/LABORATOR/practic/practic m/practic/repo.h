#pragma once
#include"domeniu.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;
class Repo {
private:
	string fisier;
	vector<Melodie>melodii;
	//vector de melodii
	void load_from_file();
	//citeste din fisier si adauga in vcetorul de melodii
	void write_to_file();
	//suprascrie fisierul dupa vectorul de melodii
public:
	Repo(const string& fisier) :fisier{ fisier } {
		load_from_file();
	}
	//constructor primeste fisier-styring si alepeaza metoda de citire din fisier
	void adauga(const Melodie& m);
	//adauga un obiect de tip Melodie in vectorul de melodii daca are id unic
	void modifica(const Melodie& m);
	//modifica un element cu id==m.get_id daca il gaseste in melodii
	void sterge(int id);
	//strege un element din vector dupa id 
	vector<Melodie>get_all()const { return melodii; }
	//returneaza vectorul de melodii
};