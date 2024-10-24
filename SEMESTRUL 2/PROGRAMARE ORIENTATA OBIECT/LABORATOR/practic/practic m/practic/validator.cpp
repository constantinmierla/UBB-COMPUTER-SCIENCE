#include "validator.h"
#include"domeniu.h"
void Validator::valideaza(const Melodie& m)
{
	string error = "";
	if (m.get_id() < 0)
		error += "id invalid";
	if (m.get_titlu() == "")
		error += "titlu invalid";
	if (m.get_artist() == "")
		error += "artist invalid";
	if (m.get_rank() < 0 || m.get_rank() > 10)
		error += "rank invalid";
	if (error != "")
		throw::ValException(error);
}
