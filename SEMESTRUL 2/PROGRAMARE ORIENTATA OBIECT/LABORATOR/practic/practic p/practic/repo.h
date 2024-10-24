#pragma once
#include"domeniu.h"
#include<vector>
#include<sstream>
#include<fstream>
class Repo {
private:
	string fisier;
	void load_from_file();
	//citeste din fisier 
	void write_to_file();
	//suprascrie fisierul 
	vector<Produs>produse;
public:
	Repo(const string& fisier) :fisier{ fisier } {
		load_from_file();

	};
	//constructor primeste fisier -string si apeleaza metoda load_form-file
	void adauga(const Produs& p);
	//adauga un Produs in vectorul de produse se reflacta in fisier
	vector<Produs>get_all() { return produse; }
	//returneaza vectorul produse
	void sterge(const int id);
	//adauga un Produs din vectorul de produse se reflacta in fisier dupa id -int
};