#include "serv.h"

void Service::addService(int id, string& titlu, string& artist, int rank)
{
	Melodie m(id, titlu, artist, rank);
	repo.add(m);
}

void Service::removeService(int id, string& titlu, string& artist, int rank)
{
	Melodie m(id, titlu, artist, rank);
	repo.remove(m);
}
void Service::modifyService(int id, string& titlu, int rank)
{
	repo.modify(id,titlu,rank);
}

vector<Melodie> Service::getAllService() const {
	return repo.getAll();
}
vector<int> Service::rankService() const{
	vector<int> a;
	for (int i = 1; i <= 10; i++)
	{
		int nr = 0;
		for (auto& e : getAllService())
		{
			if (e.get_rank() == i)
				nr++;
		}
		a.push_back(nr);
	}
	return a;
}
int Service::findArtist(string& nume) {
	int nr = 0;
	for (auto& e : getAllService())
	{
		if (e.get_artist() == nume)
			nr++;
	}
	return nr;
}

map<string, int> Service::raport(vector<Melodie> all) {
	map<string, int> a;
	for(auto& e: all)
	{
		a[e.get_artist()]++;
	}
	return a;
}