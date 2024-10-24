#include"teste.h"
void test() {
	Repo repo{ "test.txt" };
	Validator val;
	Service service{ repo,val };
	Melodie m{ 10,"a","b",1 };
	assert(m.get_id() == 10);
	assert(m.get_rank() == 1);
	assert(m.get_titlu() == "a");
	assert(m.get_artist() == "b");
	assert(repo.get_all().size() == 7);
	repo.adauga(m);
	try {
		repo.adauga(m);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	Melodie e{ 10,"a","a",1 };
	repo.modifica(e);
	assert(repo.get_all()[7].get_artist() == "a");
	assert(repo.get_all().size() == 8);
	repo.sterge(10);
	assert(repo.get_all().size() == 7);
	try {
		repo.sterge(-1);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	service.modifica(1, "a", "a", 1);
	assert(service.get_all()[0].get_artist() == "a");
	service.sterge(9);
	assert(service.get_all().size() == 6);
	Melodie n{ 9,"a","a",1 };
	repo.adauga(n);
	assert(service.get_all().size() == 7);
	try {
		service.sterge(111);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	try {
		service.modifica(111, "a", "a", 1);
	}
	catch (exception)
	{
		assert(true);
	}
	try {
		service.modifica(-1, "a", "a", 1);
		assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "id invalid");
	}
	try {
		service.modifica(1, "", "a", 1);
		assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "titlu invalid");
	}
	try {
		service.modifica(1, "a", "", 1);
		assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "artist invalid");
	}
	try {
		service.modifica(1, "a", "a", 200);
		assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "rank invalid");
	}
	assert(service.rank(5) == 3);
	assert(service.rank(1) == 2);
	assert(service.rank(0) == 0);
	assert(service.rank(7) == 0);
	vector<Melodie>rez = service.sorteaza_rank();
	assert(rez[0].get_rank() == 1);
	assert(rez[1].get_rank() == 1);
	assert(rez[2].get_rank() == 2);
	assert(rez[6].get_rank() == 5);
	try {
		Repo r{ "aa" };
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
}