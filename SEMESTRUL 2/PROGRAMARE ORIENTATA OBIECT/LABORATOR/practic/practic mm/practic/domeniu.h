#pragma once
#include<iostream>
using namespace std;
class Melodie
{
private:
	int id;
	string titlu;
	string artist;
	string gen;
public:
	Melodie(int id, const string& titlu, const string& artist, const string& gen) :id{ id }, titlu{ titlu }, artist{ artist }, gen{ gen } {};
	//constructor Melodie id:int,titlu:string artist:string gen:string
	int get_id()const { return id; }
	//metoda getter returneaza id-int
	string get_titlu()const { return titlu; }
	//metoda getter returneaza titlu string
	string get_artist()const { return artist; }
	//metoda getter returneaza artist string
	string get_gen()const { return gen; }
	//metoda getter returneaza gen string
};