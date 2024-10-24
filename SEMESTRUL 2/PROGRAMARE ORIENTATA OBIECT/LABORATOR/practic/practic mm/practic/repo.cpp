#include "repo.h"

void Repo::write_to_file()
{
	ofstream f(file);
	if (!f.is_open())throw::exception("nu se poate deschide fisierul");
	for (const auto& m : melodii)
		f << m.get_id() << " " << m.get_titlu() << " " << m.get_artist() << " " << m.get_gen() << endl;
	f.close();
}

void Repo::load_from_file()
{
	ifstream f(file);
	if (!f.is_open())
	{
		throw::exception("nu se poate deschide");
	}
	string line;
	while (getline(f, line))
	{
		string titlu, artist, gen;
		int id;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ' '))
		{
			if (item_no == 0)id = stoi(current_item);
			if (item_no == 1)titlu = current_item;
			if (item_no == 2)artist = current_item;
			if (item_no == 3)gen = current_item;
			item_no++;
		}
		Melodie m{ id,titlu,artist,gen };
		adauga(m);
	}
	f.close();
}

void Repo::adauga(const Melodie& m)
{
	auto f = find_if(melodii.begin(), melodii.end(), [&](const Melodie& o) {return o.get_id() == m.get_id(); });
	if (f != melodii.end())
		throw::exception("id existent");
	else {
		melodii.push_back(m);
		write_to_file();
	}
}

void Repo::sterge(int id)
{
	auto f = find_if(melodii.begin(), melodii.end(), [&](const Melodie& o) {return o.get_id() == id; });
	if (f != melodii.end()) {
		melodii.erase(f);
		write_to_file();
	}
	else
		throw::exception("nu exista elementul");
}
int Repo::id_nou()
{
	int id = 1;
	auto f = find_if(melodii.begin(), melodii.end(), [&](const Melodie& o) {return o.get_id() == id; });
	while (f != melodii.end()) {
		id++;
		f = find_if(melodii.begin(), melodii.end(), [&](const Melodie& o) {return o.get_id() == id; });
	}
	return id;
}