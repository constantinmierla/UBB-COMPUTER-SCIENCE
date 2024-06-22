#include "repo.h"
#include <fstream>

void Repo::load_from_file()
{
	ifstream in(this->filename);
	int a;
	string b, c;
	double d;
	while (in >> a >> b >> c >> d)
	{
		Produs p = Produs(a, b, c, d);
		all.push_back(p);
	}
	in.close();
}

void Repo::save_to_file()
{
	ofstream out(this->filename);
	vector<Produs> al = get_all();
	for (auto& i : al)
	{
		out << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << '\n';
	}
	out.close();
}
void Repo::adauga(Produs& t) 
{
	all.push_back(t);
	save_to_file();
}