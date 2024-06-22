#pragma once
#include<iostream>
#include"repo.h"
#include<algorithm>
#include"validator.h"
#include<map>
class Service {
private:
	Repo& repo;
	Validator& val;
public:
	Service(Repo& repo, Validator& val) :repo{ repo }, val{ val } {};
	//constructor 
	void modifica(int id, string titlu, string artist, int rank);
	//modifica un obiect Melodie dupa id,titlu,artist,rank , valideaza obiectul apeleaza repo
	void sterge(int id);
	//sterge un obiect Melodie dupa id apeleaza repo
	vector<Melodie>get_all() { return repo.get_all(); }
	//returbenaza vectorul de melodii
	vector<Melodie>sorteaza_rank();
	int rank(int r);

};