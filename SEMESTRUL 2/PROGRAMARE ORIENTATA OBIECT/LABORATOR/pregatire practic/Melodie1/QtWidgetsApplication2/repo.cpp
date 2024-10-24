#include "repo.h"

void Repo::load_from_file() {
	int a, d;
	string b, c;
	ifstream in(filename);
	while (in >> a >> b >> c >> d)
	{
		Tractor t = Tractor(a, b, c, d);
		all.push_back(t);
	}
	in.close();
}
void Repo::save_to_file() {
	vector<Tractor> al = get_all();
	ofstream out(filename);
	for (auto& i : al)
	{
		out << i.get_id() << " " << i.get_denumire() << " " << i.get_tip() << " " << i.get_roti() << '\n';
	}
	out.close();
}
void Repo::adauga(const Tractor& t) {
	auto f = find_if(all.begin(), all.end(), [&](const Tractor& o) {
		return t.get_id() == o.get_id();
		});
	if (f == all.end())
	{
		all.push_back(t);
		save_to_file();
	}
	else
		throw::exception("nu exista id");
}
void Repo::sterge(int id) {
	auto f = find_if(all.begin(), all.end(), [&](const Tractor& o) {return id == o.get_id(); });
	if (f != all.end())
	{
		all.erase(f);
		save_to_file();
	}
}
void Repo::modifica(Tractor& t) {
	for (auto& tract : all)
	{
		if (tract == t)
		{
			tract = t;
			save_to_file();
		}
	}
}