#include "teste.h"

void test()
{
	Repo repo{ "teste.txt" };
	Validator val{ repo };
	Service service{ repo,val };
	assert(repo.get_all().size() == 3);
	assert(service.get_all().size() == 3);
	Produs p{ 10,"a","radiera",12 };
	assert(p.get_id() == 10);
	assert(p.get_tip() == "radiera");
	assert(p.get_nume() == "a");
	assert(p.get_pret() == 12);
	repo.adauga(p);
	try {
		repo.adauga(p);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	assert(repo.get_all().size() == 4);
	repo.sterge(10);
	assert(repo.get_all().size() == 3);
	try {
		Repo r{ "aa" };
		assert(false);
	}
	catch (exception) {
		assert(true);
	}
	service.adauga(10, "a", "radiera", 12);
	assert(service.get_all().size() == 4);
	repo.sterge(10);
	try {
		service.adauga(1, "", "", 1111);
		assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "id existent\nnume invalid\ntip invalid\npret invalid\n");
	}
	assert(service.nr_vocale("wwww") == 0);
	assert(service.nr_vocale("aeiouuu") == 7);
	vector<Produs>pr = service.sorteaza();
	assert(pr.size() == 3);
	assert(pr[0].get_id() == 2);
	assert(pr[1].get_id() == 1);
	assert(pr[2].get_id() == 3);
	map<string, int>a = service.tipuri();
	assert(a.size() == 3);
	assert(a["papus"] == 1);
	assert(a["topor"] == 1);
	assert(a["pix"] == 1);
	assert(service.numar("topor") == 1);
	assert(service.numar("papus") == 1);
	assert(service.numar("pix") == 1);
}
