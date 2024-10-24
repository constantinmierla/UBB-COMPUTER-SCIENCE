#include"teste.h"
void test_repo()
{
	string fi = "teste.txt";
	Repo repo{ fi };
	assert(repo.get_all().size() == 4);
	Validator val;
	Service service{ repo,val };
	assert(service.get_all().size() == 4);
	assert(repo.id_nou() == 5);
	Melodie m{ 100,"ana","bana","disco" };
	assert(m.get_id() == 100);
	assert(m.get_titlu() == "ana");
	assert(m.get_artist() == "bana");
	assert(m.get_gen() == "disco");
	repo.adauga(m);
	assert(repo.get_all().size() == 5);
	repo.sterge(100);
	assert(repo.get_all().size() == 4);
	try {
		Melodie mi{ 1,"","","" };
		repo.adauga(mi);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	try {
		repo.sterge(1000);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	service.adauga("x", "x", "pop");
	assert(repo.get_all().size() == 5);
	service.sterge(5);
	assert(repo.get_all().size() == 4);
	try {
		service.adauga(" ", "", "");
		assert(false);
	}
	catch (ValException val)
	{
		assert(true);
	}
	try {
		service.adauga("", "hj", "pop");
		assert(false);
	}
	catch (ValException& val)
	{
		assert(val.get_mesaj() == "titlu invalid ");
	}
	try {
		service.adauga("sdd", "hj", "");
		assert(false);
	}
	catch (ValException& val)
	{
		assert(val.get_mesaj() == "gen invalid");
	}
	try {
		service.sterge(1888);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	vector<Melodie>v = service.sorteaza_autor();
	assert(v[0].get_artist() == "Hannah");
	assert(v[1].get_artist() == "JB");
	assert(v[2].get_artist() == "MB");
	assert(service.gen("pop") == 1);
	assert(service.gen("folk") == 1);
	assert(service.gen("jazz") == 1);
	assert(service.artist("MB") == 1);
	assert(service.artist("JB") == 1);
}
void teste()
{
	test_repo();
}