#pragma once
#include <iostream>
using namespace std;

class Tractor {
private:
	int id;
	string denumire;
	string tip;
	int cilindri;
public:
	Tractor(int id, string denumire, string tip, int cilindri) : id{ id }, denumire{ denumire }, tip{ tip }, cilindri{ cilindri } {};
	int get_id() { return this->id; }
	string get_denumire() { return this->denumire;}
	string get_tip() { return this->tip; }
	int get_cilindri() { return this->cilindri; }
	~Tractor() = default;
	void set_denumire(string d)
	{
		this->denumire = d;
	}
	void set_tip(string t)
	{
		this->tip = t;
	}
	void set_cilindri(int c)
	{
		this->cilindri = c;
	}
};