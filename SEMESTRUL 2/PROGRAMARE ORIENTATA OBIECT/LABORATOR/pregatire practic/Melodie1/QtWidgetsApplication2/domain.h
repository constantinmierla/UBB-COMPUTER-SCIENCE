#pragma once
#include <iostream>
using namespace std;
class Tractor {
private:
	int id;
	string denumire;
	string tip;
	int roti;
public:
	Tractor(int id, string denumire, string tip, int roti) : id{ id }, denumire{ denumire }, tip{ tip }, roti{ roti } {};

	int get_id() const
	{
		return this->id;
	}
	string get_denumire() const {
		return this->denumire;
	}
	string get_tip() const {
		return this->tip;
	}
	int get_roti() const {
		return this->roti;
	}
	bool operator==(const Tractor& t) { return t.get_id() == id; }
	Tractor& operator=(const Tractor& other)
	{
		id = other.id;
		denumire = other.denumire;
		tip = other.tip;
		roti = other.roti;
		return *this;
	}
	~Tractor() = default;
};