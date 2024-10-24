#pragma once
#include "car.h"
#include "carRepo.h"

class UndoAction
{
public:
	// metoda pur virtuala pentru executarea operatiei de undo
	virtual void doUndo() = 0;

	// destructorul clasei
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction
{
	// masina adaugata
	Car addedCar;

	// repository-ul de masini
	AbstractRepo& repo;

public:
	// constructorul clasei
	UndoAdd(AbstractRepo& repo, const  Car& c) : repo{ repo }, addedCar{ c } {}

	// metoda pentru executarea operatiei de undo
	void doUndo() override
	{
		const __int64 position = repo.find(addedCar.getLicensePlate());
		repo.remove(position);
	}
};

class UndoRemove : public UndoAction
{
	// masina stearsa
	Car deletedCar;

	// repository-ul de masini
	AbstractRepo& repo;

public:
	// constructorul clasei
	UndoRemove(AbstractRepo& repo, const  Car& c) : repo{ repo }, deletedCar{ c } {}

	// metoda pentru executarea operatiei de undo
	void doUndo() override
	{
		repo.add(deletedCar);
	}
};

class UndoModify : public UndoAction
{
	// masina modificata
	Car oldCar;
	Car newCar;

	// repository-ul de masini
	AbstractRepo& repo;

public:
	// constructorul clasei
	UndoModify(AbstractRepo& repo, const  Car& oldC, const Car& newC) : repo{ repo }, oldCar{ oldC }, newCar{ newC } {}

	// metoda pentru executarea operatiei de undo
	void doUndo() override
	{
		const __int64 position = repo.find(newCar.getLicensePlate());
		repo.modify(position, oldCar);
	}
};