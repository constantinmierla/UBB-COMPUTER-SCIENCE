#pragma once
#include<iostream>
#include<string>
using namespace std;

class Tractor {
private:
	int id;
	string denumire;
	string tip;
	int cilindri;

public:
	/*
	* Constructorul clasei Tractor
	* are ca parametri 
	id de tip intreg
	denumire de tip string
	tip de tip string
	cilindri de tip intreg
	*/
	Tractor(int id, const string& denumire, const string& tip, int cilindri) :id{ id }, denumire{ denumire }, tip{ tip }, cilindri{ cilindri } {};
	
	/*
	* Getter
	* Returneaza id ul curent - de tip intreg
	*/
	int get_id()const { return id; }
	
	/*
	* Getter
	* Returneaza denumirea - de tip string
	*/
	string get_denumire()const { return denumire; }
	
	/*
	* Getter
	* Returneaza tipul - de tip string
	*/
	string get_tip()const { return tip; }

	/*
	* Getter
	* Returneaza numarul de cilindri - de tip int
	*/
	int get_nr()const { return cilindri; }


	/*
	* modificam operatorul ==
	* verificam daca id urile sunt egale
	*/
	bool operator==(const Tractor& t) { return t.get_id() == id; }


	/*
	* modificam operatorul = 
	* verificam fiecare membru al clasei
	*/
	Tractor& operator=(const Tractor& other)
	{
		id = other.id;
		denumire = other.denumire;
		tip = other.tip;
		cilindri = other.cilindri;
		return *this;
	}

};