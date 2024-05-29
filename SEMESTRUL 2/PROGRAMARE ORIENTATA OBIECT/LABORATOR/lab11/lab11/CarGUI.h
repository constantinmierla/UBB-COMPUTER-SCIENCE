#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include "carService.h"
#include "observer.h"
#include <map>
#include "washCRUDGUI.h"
#include "washRDOnlyGUI.h"
#include "carListModel.h"
using namespace std;

class CarGUI : public QWidget
{
	friend class WashCRUDGUI;
	friend class WashRDOnlyGUI;

private:
	// service-ul curent
	CarService& service;

	WashCRUDGUI* wash;
	WashRDOnlyGUI* washRDOnly;

	// comutare
	QPushButton* butonLista, * butonRDOnly;

	// adaugare
	QPushButton* buttonAdd;
	QLabel* labelLPAdd = new QLabel("Numarul de inmatriculare al masinii: ");
	QLabel* labelPAdd = new QLabel("Producatorul masinii: ");
	QLabel* labelMAdd = new QLabel("Modelul masinii: ");
	QLabel* labelTAdd = new QLabel("Tipul masinii: ");
	QLineEdit* addLicensePlate, * addProducer, * addModel, * addType;

	// stergere
	QPushButton* buttonRemove;
	QLabel* labelDelete = new QLabel{ "Numarul de inmatriculare al masinii: " };
	QLineEdit* deleteLP;

	// modifica
	QPushButton* buttonModify;
	QLabel* labelLPModify = new QLabel("Numarul de inmatriculare al masinii: ");
	QLabel* labelPModify = new QLabel("Producatorul masinii: ");
	QLabel* labelMModify = new QLabel("Modelul masinii: ");
	QLabel* labelTModify = new QLabel("Tipul masinii: ");
	QLineEdit* modifyLicensePlate, * modifyProducer, * modifyModel, * modifyType;

	// sortare
	QLabel* descLabel = new QLabel("Descrescator:");
	QCheckBox* desc = new QCheckBox;
	QLabel* sortLabel = new QLabel("Sorteaza:");
	QPushButton* buttonSortByLicensePlate, * buttonSortByType, * buttonSortByProdModel;

	// filtrare
	QLabel* labelPFilter = new QLabel("Producatorul dupa care se filtreaza:");
	QLineEdit* filterByProducer, * filterByType;
	QLabel* labelTFilter = new QLabel("Tipul dupa care se filtreaza:");
	QPushButton* buttonFilterByProducer, * buttonFilterByType;

	QPushButton* addWash, * emptyWash, * populateWash;
	QLineEdit* add, * populate;


	QTableView* table;
	CarListModel* model;

	// initializarea interfetei
	void initGUI();

	// legatura dintre butoane si actiuni
	void connectSignalSlots();

	// reincarcam lista dupa fiecare operatiune
	void reloadList(const vector<Car> list);

	// undo
	QPushButton* undo;

	// butoane pentru tipuri
	QPushButton* btnAltele, * btnSuv, * btnMini, * btnSport;

	// variabila care retine modul in care sortam
	char mode = 'c';

	// adaugam o masina
	void addGUI();

	//stergem o masina
	void removeGUI();

	// modificam o masina
	void modifyGUI();

	// sortam dupa nr de inmatriculare
	void sortByLicensePlateGUI();

	// sortam dupa tip
	void sortByTypeGUI();

	// sortam dupa producator + model
	void sortByProdModelGUI();

	// schimbam mode daca s-a apasat butonul de descrescator
	void sortOrderChanged(int state);

	// undo
	void undoGUI();



public:
	// constructorul clasei GUI
	CarGUI(CarService& cS);
};
