#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(fisier);
	if (!file.is_open())
		throw::exception("nu se poate decshide");
	else {
		string line;
		while (getline(file, line))
		{
			int id, rank;
			string titlu, artist;
			stringstream linestream(line);
			string current_item;
			int item_no = 0;
			while (getline(linestream, current_item, ' '))
			{
				if (item_no == 0)id = stoi(current_item);
				if (item_no == 1)titlu = current_item;
				if (item_no == 2)artist = current_item;
				if (item_no == 3)rank = stoi(current_item);
				item_no++;
			}
			Melodie m{ id,titlu,artist,rank };
			adauga(m);
		}
		file.close();
	}
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open())
		throw::exception("nu se poate decshide");
	for (auto& m : melodii)
	{
		file << m.get_id() << " " << m.get_titlu() << " " << m.get_artist() << " " << m.get_rank() << endl;
	}
	file.close();
}

void Repo::adauga(const Melodie& m)
{
	auto f = find_if(melodii.begin(), melodii.end(), [&](const Melodie& o) {return m.get_id() == o.get_id(); });
	if (f == melodii.end())
	{
		melodii.push_back(m);
		write_to_file();
	}
	else
		throw::exception("id existent");
}

void Repo::modifica(const Melodie& m)
{
	for (auto& mel : melodii)
	{
		if (mel == m) {
			mel = m;
			write_to_file();
		}
	}
}

void Repo::sterge(int id)
{
	auto f = find_if(melodii.begin(), melodii.end(), [&](const Melodie& o) {return id == o.get_id(); });
	if (f != melodii.end())
	{
		melodii.erase(f);
		write_to_file();
	}
	else
		throw::exception("nu exista id");
}
