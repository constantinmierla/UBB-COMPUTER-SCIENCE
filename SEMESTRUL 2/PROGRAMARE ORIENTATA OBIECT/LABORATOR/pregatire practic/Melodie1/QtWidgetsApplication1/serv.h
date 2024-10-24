#pragma once
#include "repo.h"
#include <map>
class Service
{
private:
	RepoFile& repo;
public:
	Service(RepoFile& r) : repo{ r } {};

	void addService(int id, string& titlu, string& artist, int rank);
	void removeService(int id, string& titlu, string& artist, int rank);
	void modifyService(int id, string& titlu, int rank);
	vector<Melodie> getAllService() const;
	vector<int> rankService() const;
	int findArtist(string& nume);
	map<string, int> raport(vector<Melodie> all);
};