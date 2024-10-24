#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(fisier);
	if (!file.is_open())
	{
		throw exception("nu se poate deschide fisierul");
	}
	string line;
	while (getline(file, line))
	{
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		int id;
		double pret;
		string tip;
		string nume;
		while (getline(linestream, current_item, ' '))
		{
			if (item_no == 0)id = stoi(current_item);
			if (item_no == 1)nume = current_item;
			if (item_no == 2)tip = current_item;
			if (item_no == 3)pret = stod(current_item);
			item_no++;
		}
		Produs p{ id,nume,tip,pret };
		adauga(p);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open())
	{
		throw exception("nu se poate deschide fisierul");
	}
	for (const auto& l : produse)
	{
		file << l.get_id() << " " << l.get_nume() << " " << l.get_tip() << " " << l.get_pret() << endl;
	}
	file.close();
}

void Repo::adauga(const Produs& p)
{
	auto f = find_if(produse.begin(), produse.end(), [&](const Produs& o) {return p.get_id() == o.get_id(); });
	if (f != produse.end())
	{
		throw exception("nu exista");

	}
	else
	{
		produse.push_back(p);
		write_to_file();
	}
}


void Repo::sterge(const int id)
{
	auto f = find_if(produse.begin(), produse.end(), [&](const Produs& o) {return id == o.get_id(); });
	if (f == produse.end())
	{
		throw exception("nu exista");

	}
	else
	{
		produse.erase(f);
		write_to_file();
	}
}
