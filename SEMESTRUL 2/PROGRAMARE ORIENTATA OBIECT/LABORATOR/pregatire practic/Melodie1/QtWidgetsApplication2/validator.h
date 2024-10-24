#pragma once
#include "repo.h"
#include <exception>
class ValException {
private:
	string msg;
public:
	ValException(string& msg) : msg{ msg } {};
	string get_mesaj() { return msg; }
};

class Validator {
private:
	Repo& repo;
public:
	Validator(Repo& repo) : repo{ repo } {};
	void valideaza(const Tractor& t)
	{
		string error = "";
		vector<Tractor>v{ repo.get_all() };
		auto f = find_if(v.begin(), v.end(), [&](const Tractor& o) {return t.get_id() == o.get_id(); });
		if (f != v.end())
			error += "id existent ";
		if (t.get_denumire() == "")
			error += "denumire invalida ";
		if (t.get_tip() == "")
			error += "tip invalid ";
		if (t.get_roti() % 2 == 1 || t.get_roti() < 2 || t.get_roti() > 16)
			error += "nr roti invalid ";
		if (error != "")
			throw::ValException(error);
	}
	void valideaza_modifica(const Tractor& t)
	{
		string error = "";
		if (t.get_denumire() == "")
			error += "denumire invalida ";
		if (t.get_tip() == "")
			error += "tip invalid ";
		if (t.get_roti() % 2 == 1 || t.get_roti() < 2 || t.get_roti() > 16)
			error += "nr roti invalid ";
		if (error != "")
			throw::ValException(error);
	}
};