#include "validator.h"
#include "service.h"

void Validator::valideaza(const Tractor& t)
{
	string error = "";
	vector<Tractor>v{ repo.get_all() };
	auto f = find_if(v.begin(), v.end(), [&](const Tractor& o) {return t.get_id() == o.get_id(); });
	if (f != v.end())
		error += "id existent ";
	if (t.get_denumire() == "")
		error += "denumire invalida ";
	if (t.get_tip() == "")
		error += "tip invalid ";
	if (t.get_nr() % 2 == 1 || t.get_nr() < 2 || t.get_nr() > 16)
		error += "nr cilindri invalid ";
	if (error != "")
		throw::ValException(error);
}
void Validator::valideaza_sterge(int id) {
	string error = "";
	if (id <= 1)
		error += "nr prea mic de cilindri";
	if (error != "")
		throw::ValException(error);
}
void Validator::valideaza_modifica(const Tractor& t)
{
	string error = "";
	if (t.get_denumire() == "")
		error += "denumire invalida ";
	if (t.get_tip() == "")
		error += "tip invalid ";
	if (t.get_nr() % 2 == 1 || t.get_nr() < 2 || t.get_nr() > 16)
		error += "nr cilindri invalid ";
	if (error != "")
		throw::ValException(error);
}
