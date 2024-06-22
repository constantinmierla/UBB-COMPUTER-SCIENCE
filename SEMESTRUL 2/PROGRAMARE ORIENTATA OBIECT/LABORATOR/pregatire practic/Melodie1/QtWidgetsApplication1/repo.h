#pragma once
#include "domain.h"

#include <vector>
#include <fstream>

class Repo {
private:
	vector<Melodie> melodii;
public:
	void add(Melodie& melodie);
	void remove(Melodie& melodie);
	void modify(int id, string& titlu, int rank);
	vector<Melodie> getAll() const;
};

class RepoFile : public Repo {
private:
	string filename;
	void load_from_file();
	void save_to_file();
	void clearfile() {
		ofstream in(filename);
		in.clear();
	}
public:
	RepoFile(string fisier) : filename{ fisier } {
		load_from_file();
	};
	void add(Melodie& melodie)
	{
		Repo::add(melodie);
		save_to_file();
	}
	void remove(Melodie& melodie)
	{
		Repo::remove(melodie);
		save_to_file();
	}
	void modify(int id, string& titlu, int rank)
	{
		Repo::modify(id, titlu, rank);
		save_to_file();
	}
};