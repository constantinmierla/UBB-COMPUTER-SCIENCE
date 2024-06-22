#pragma once
#include <string>
using namespace std;

class Melodie
{
private:
	int id;
	string titlu;
	string artist;
	int rank;
public:
	Melodie(int id, string &titlu, string &artist, int rank) : id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {};
	int get_id() const
	{
		return this->id;
	}
	void set_rank(int r)
	{
		this->rank = r;
	}
	int get_rank() const
	{
		return this->rank;
	}
	string get_titlu() const
	{
		return this->titlu;
	}
	string get_artist() const
	{
		return this->artist;
	}
	void set_titlu(string t)
	{
		this->titlu = t;
	}
	~Melodie() = default;
};