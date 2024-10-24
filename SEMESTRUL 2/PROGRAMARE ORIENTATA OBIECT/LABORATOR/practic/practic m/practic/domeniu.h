#pragma once
#include<iostream>
#include<vector>
using namespace std;
class Melodie {
private:
	int id;
	string titlu;
	string artist;
	int rank;
public:
	Melodie(int id, const string& titlu, const string& artist, int rank) :id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {};
	//constrctor id-int,titlu-string,artist-string,rank int
	int get_id()const { return id; };
	//metoda getter returneaza id-int
	string get_titlu()const { return titlu; };
	//metoda getter returneaza titlu string
	string get_artist()const { return artist; };
	//metoda getter returneaza artist string
	int get_rank()const { return rank; };
	//metoda getter returneaza rannk int
	bool operator==(const Melodie& m) {
		return m.get_id() == id;
	}
	Melodie& operator=(const Melodie& m)
	{
		//if (this == &m)
			//return *this;
		id = m.get_id();
		titlu = m.get_titlu();
		artist = m.get_artist();
		rank = m.get_rank();
		return *this;
	}
};