#pragma once
#include<iostream>
#include<vector>
#include"repo.h"
#include"validator.h"
#include<algorithm>
#include<unordered_map>
#include<map>
#include"observer.h"
using namespace std;
class Service {
private:
	Repo& repo;
	Validator& validator;
public:
	Service(Repo& repo, Validator& validator) :repo{ repo }, validator{ validator } {};
	//constructor apleaza repo si validator
	void adauga(const string& titlu, const string& artist, const string& gen);
	//formeaza un obiect de tip melodie il valideaza si apeleaza repo
	void sterge(int id);
	//apeleaza repo
	vector<Melodie>sorteaza_autor();
	//sorteaza un vcetor dupa autor
	vector<Melodie>get_all()const { return repo.get_all(); }
	//returneaza vectorul de melodii
	int gen(string gen);
	//formeaza un map<string,int> cu genurile existemte si nr de elemente asociate
	int artist(string artist);
	//formeaza un map<string,int> cu  existemte si nr de elemente asociate
};