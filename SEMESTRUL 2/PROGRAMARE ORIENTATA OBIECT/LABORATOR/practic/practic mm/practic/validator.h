#pragma once
#include"domeniu.h"
#include<iostream>
using namespace std;
class ValException {
	string msg;
public:
	ValException(string m) :msg{ m } {

	}
	//returneaza mesajul -string
	string get_mesaj() {
		return msg;
	};
};
class Validator {
public:
	//valideaza un obiect de tip melodie
	void valideaza(const Melodie& m);
};