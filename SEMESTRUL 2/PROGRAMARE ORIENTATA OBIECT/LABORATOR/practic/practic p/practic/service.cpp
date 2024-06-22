#include "service.h"
vector<Produs> Service::sorteaza()
{
	vector<Produs>rez = repo.get_all();
	sort(rez.begin(), rez.end(), [&](const Produs& o1, const Produs& o2) {return nr_vocale(o1.get_nume()) > nr_vocale(o2.get_nume()); });
	return rez;
}

int Service::nr_vocale(string text)
{
	vector<char>voc = { 'a','e','i','o','u','A','I','E','O','U' };
	int contor = 0;
	for (int i = 0; i < voc.size(); i++)
	{
		for (int j = 0; j < text.size(); j++)
		{
			if (voc[i] == text[j])
				contor++;
		}
	}
	return contor;
}

void Service::adauga(const int id, const string& denumire, const string& tip, const double pret)
{
	Produs p{ id,denumire,tip,pret };
	val.valideaza(p);
	repo.adauga(p);
	UndoAction.push_back(make_unique<UndoAdauga>(repo, p));
	notify();
}

int Service::numar(const string text)
{
	int count = 0;
	for (auto l : get_all())
	{
		if (l.get_tip() == text)
			count++;
	}
	return count;
}

map<string, int> Service::tipuri()
{
	map<string, int>rez;
	for (auto l : get_all())
	{
		if (rez.find(l.get_tip()) == rez.end())
			rez[l.get_tip()] = 1;
		else
			rez[l.get_tip()]++;
	}
	return rez;
}

void Service::undo()
{
	if (UndoAction.empty())
		throw exception("nu se mai poate face undo");
	else {
		UndoAction.back()->doUndo();
		UndoAction.pop_back();
	}
	notify();
}
