#include "validator.h"

void Validator::valideaza(const Produs& p)
{
	string eroare = "";
	vector<Produs>r = repo.get_all();
	auto f = find_if(r.begin(), r.end(), [&](const Produs& o) {return p.get_id() == o.get_id(); });
	if (f != r.end())
		eroare += "id existent\n";
	if (p.get_nume() == "")
		eroare += "nume invalid\n";
	if (p.get_tip() == "")
		eroare += "tip invalid\n";
	if (p.get_pret() > 100.0 || p.get_pret() < 1.0)
		eroare += "pret invalid\n";
	if (eroare != "")
		throw ValException(eroare);

}
