#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(fisier);
	if (!file.is_open())
		throw::exception("nu se poate deschide");
	else {
		string line;
		while (getline(file, line))
		{
			stringstream linestream(line);
			string current_item;
			int item_no = 0;
			string denumire, tip;
			int nr, id;
			while (getline(linestream, current_item, ' '))
			{
				if (item_no == 0)id = stoi(current_item);
				if (item_no == 1)denumire = current_item;
				if (item_no == 2)tip = current_item;
				if (item_no == 3)nr = stoi(current_item);
				item_no++;
			}
			Tractor t{ id,denumire,tip,nr };
			adauga(t);
		}
		file.close();
	}
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open())
		throw::exception("nu se poate deschide");
	for (const auto& t : tractoare)
	{
		file << t.get_id() << " " << t.get_denumire() << " " << t.get_tip() << " " << t.get_nr() << endl;
	}
	file.close();
}


void Repo::adauga(const Tractor& t)
{
	auto f = find_if(tractoare.begin(), tractoare.end(), [&](const Tractor& o) {return t.get_id() == o.get_id(); });
	if (f == tractoare.end())
	{
		tractoare.push_back(t);
		write_to_file();
	}
	else
		throw::exception("nu exista id");
}

void Repo::sterge(int id)
{
	auto f = find_if(tractoare.begin(), tractoare.end(), [&](const Tractor& o) {return id == o.get_id(); });
	if (f != tractoare.end())
	{
		tractoare.erase(f);
		write_to_file();
	}
}

void Repo::modifica(Tractor& t)
{
	for (auto& tract : tractoare)
	{
		if (tract == t) {
			tract = t;
			write_to_file();
		}

	}
}
