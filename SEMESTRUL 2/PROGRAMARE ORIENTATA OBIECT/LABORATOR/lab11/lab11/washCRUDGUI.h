#pragma once
#include <qwidget.h>
#include "observer.h"
#include "CarGUI.h"

class WashCRUDGUI : public QWidget, public Observer
{
	friend class CarGUI;
	// cos CRUD GUI

public:
	// service-ul curent
	CarService& service;
private:
	CarGUI* main;

	// lista de masini de spalat
	QListWidget* windowList;

	// butoanele pentru meniul de masini de spalat
	QPushButton* butonEmptyWash, * butonPopulateWash;
	QPushButton* butonAcasa;


	// labels
	QLabel* labelAddWash = new QLabel("Introduceti un numar de inmatriculare:");
	QLabel* labelPopulateWash = new QLabel("Introduceti un numar:");

	QLineEdit* populateWash;


	// populam lista de masini de spalat
	void generateWashGUI();

	// initializam fereastra pentru lista de spalat
	void initWashGUI();

	// reincarcam lista de masini de spalat
	void reloadWashList(vector<Car> carList);

	// conectam butoanele
	void connectSignalSlots();

	void update() override
	{
		reloadWashList(service.getWashList());
	}

public:
	WashCRUDGUI(CarService& cS) : service{ cS } {};
	~WashCRUDGUI()
	{
		service.removeObserver(this);
	}
};