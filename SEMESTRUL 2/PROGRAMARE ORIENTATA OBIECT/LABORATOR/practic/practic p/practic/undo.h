#pragma once
#include"repo.h"
class Undo {
public:
	virtual void doUndo() = 0;
	virtual ~Undo() {};
};
class UndoAdauga :public Undo {
private:
	Produs p;
	Repo& repo;
public:
	UndoAdauga(Repo& repo, Produs& p) :repo{ repo }, p{ p } {};
	void doUndo()override {
		repo.sterge(p.get_id());
	}
};