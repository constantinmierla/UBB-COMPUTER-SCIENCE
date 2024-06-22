#include "repo.h"

void Repo::add(Melodie& melodie)
{
	melodii.push_back(melodie);
}

void Repo::remove(Melodie& melodie)
{
	int j = 0;
	for (auto& i : melodii)
	{
		if (i.get_id() == melodie.get_id())
			melodii.erase(melodii.begin() + j);
		else
			j++;
	}
}

void Repo::modify(int id, string& titlu, int rank)
{
	for (auto& e : melodii)
	{
		if (e.get_id() == id)
		{
			e.set_rank(rank);
			e.set_titlu(titlu);
		}
	}
}

vector<Melodie> Repo::getAll() const {
	return this->melodii;
}

void RepoFile::save_to_file() {
	ofstream out(filename);
	vector<Melodie> all = Repo::getAll();

	for (auto& e : all)
	{
		out << e.get_id() << " " << e.get_titlu() << " " << e.get_artist() << " " << e.get_rank() << "\n";
	}
}
void RepoFile::load_from_file() {
	ifstream in(filename);
	int a,d;
	string b, c;
	while (!in.eof())
	{
		in >> a >> b >> c >> d;
		if (in.eof())
			break;
		Melodie m(a, b, c, d);
		add(m);
	}
}