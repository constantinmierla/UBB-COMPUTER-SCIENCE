#pragma once
#include"domeniu.h"
class ValException {
private:
	string msg;
public:
	ValException(string& msg) :msg{ msg } {};
	//constructor
	string get_mesaj()const { return msg; };
	//returneaza string mesaj
};
class Validator {
public:
	void valideaza(const Melodie& m);
};