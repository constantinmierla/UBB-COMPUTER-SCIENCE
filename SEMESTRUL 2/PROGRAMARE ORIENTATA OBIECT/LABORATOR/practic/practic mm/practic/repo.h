#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include "domeniu.h"
using namespace std;
class Repo {
private:
	string file;
	vector<Melodie>melodii;
	//supracsrie datele in fisier
	void write_to_file();
	void load_from_file();
	//citeste datele din fisier
public:
	Repo(string& file) :file{ file } {
		load_from_file();
	}
	//constructor si epelaza metoda privata de citire din fisier
	vector<Melodie>get_all()const { return melodii; }
	//rfeturneaza vectorul de melodii
	void adauga(const Melodie& m);
	//adauga un obiect de tip melodie in vectorul de melodii daca are id unic
	void sterge(int id);
	//sgterge un obiect cu id -int din vectorul de melodii daca il gaseste atribuit unui obiect
	int id_nou();
	//returneaza cel mai mic id liber
};