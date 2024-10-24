#include "validator.h"
#include<exception>
void Validator::valideaza(const Melodie& m)
{
	string eror = "";
	if (m.get_id() < 0)
		eror += "id invalid ";
	if (m.get_titlu() == "")
		eror += "titlu invalid ";
	if (m.get_artist() == "")
		eror += "artist invalid ";
	if (m.get_gen() != "pop" && m.get_gen() != "jazz" && m.get_gen() != "rock" && m.get_gen() != "folk" && m.get_gen() != "disco")
		eror += "gen invalid";
	if (eror != "")
		throw::ValException(eror);
}
