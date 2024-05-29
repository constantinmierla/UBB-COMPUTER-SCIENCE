
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <qformlayout.h>
#include <QtWidgets/QWidget>
#include <QCheckBox>
#include <QStandardItemModel>
#include <qwindow.h>
#include "CarGUI.h"
#include "car.h"
#include "exception.h"
#include <map>
#include "washCRUDGUI.h"

using namespace std;
void CarGUI::initGUI()
{
	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout{};
	this->setLayout(lyMain);

	//left part
	QWidget* left = new QWidget;
	QVBoxLayout* lyleft = new QVBoxLayout;
	left->setLayout(lyleft);

	// schimba pe lista de masini de spalat
	QWidget* form0 = new QWidget;
	QFormLayout* lyform0 = new QFormLayout;
	form0->setLayout(lyform0);
	butonLista = new QPushButton("Schimba pe cos CRUD");
	butonRDOnly = new QPushButton("Schimba pe cos ReadOnly");
	lyform0->addWidget(butonLista);
	lyform0->addWidget(butonRDOnly);
	lyleft->addWidget(form0);

	//add
	QWidget* form1 = new QWidget;
	QFormLayout* lyform1 = new QFormLayout;
	form1->setLayout(lyform1);
	addLicensePlate = new QLineEdit;
	addProducer = new QLineEdit;
	addModel = new QLineEdit;
	addType = new QLineEdit;
	lyform1->addRow(labelLPAdd, addLicensePlate);
	lyform1->addRow(labelPAdd, addProducer);
	lyform1->addRow(labelMAdd, addModel);
	lyform1->addRow(labelTAdd, addType);
	buttonAdd = new QPushButton("Adauga masina");
	lyform1->addWidget(buttonAdd);
	lyleft->addWidget(form1);

	//sterge
	QWidget* form2 = new QWidget;
	QFormLayout* lyForm2 = new QFormLayout;
	form2->setLayout(lyForm2);

	deleteLP = new QLineEdit;
	lyForm2->addRow(labelDelete, deleteLP);
	buttonRemove = new QPushButton("Sterge masina");
	lyForm2->addWidget(buttonRemove);
	lyleft->addWidget(form2);

	//modifica
	QWidget* form3 = new QWidget;
	QFormLayout* lyForm3 = new QFormLayout;
	form3->setLayout(lyForm3);

	modifyLicensePlate = new QLineEdit;
	modifyProducer = new QLineEdit;
	modifyModel = new QLineEdit;
	modifyType = new QLineEdit;
	lyForm3->addRow(labelLPModify, modifyLicensePlate);
	lyForm3->addRow(labelPModify, modifyProducer);
	lyForm3->addRow(labelMModify, modifyModel);
	lyForm3->addRow(labelTModify, modifyType);
	buttonModify = new QPushButton("Modifica masina");
	lyForm3->addWidget(buttonModify);
	lyleft->addWidget(form3);

	//sortare
	QWidget* form4 = new QWidget;
	QVBoxLayout* lyv4 = new QVBoxLayout;
	QWidget* lyh4 = new QWidget;
	QHBoxLayout* lyForm4 = new QHBoxLayout;
	QWidget* lyhord4 = new QWidget;
	QHBoxLayout* lyord4 = new QHBoxLayout;
	lyhord4->setLayout(lyord4);
	lyord4->addWidget(descLabel);
	lyord4->addWidget(desc);
	form4->setLayout(lyv4);
	lyh4->setLayout(lyForm4);
	buttonSortByLicensePlate = new QPushButton("Sortare dupa nr inmatriculare");
	buttonSortByType = new QPushButton("Sortare dupa tip");
	buttonSortByProdModel = new QPushButton("Sortare dupa produs si model");
	lyv4->addWidget(sortLabel);
	lyv4->addWidget(lyhord4);
	lyForm4->addWidget(buttonSortByLicensePlate);
	lyForm4->addWidget(buttonSortByType);
	lyForm4->addWidget(buttonSortByProdModel);
	lyv4->addWidget(lyh4);
	lyleft->addWidget(form4);

	//filtrare
	QWidget* form5 = new QWidget;
	QFormLayout* lyform5 = new QFormLayout;
	form5->setLayout(lyform5);
	filterByType = new QLineEdit();
	buttonFilterByType = new QPushButton("Filtreaza dupa tip");
	filterByProducer = new QLineEdit();
	buttonFilterByProducer = new QPushButton("Filtreaza dupa producator");
	lyform5->addRow(labelTFilter, filterByType);
	lyform5->addWidget(buttonFilterByType);
	lyform5->addRow(labelPFilter, filterByProducer);
	lyform5->addWidget(buttonFilterByProducer);
	lyleft->addWidget(form5);


	QWidget* right = new QWidget;
	QVBoxLayout* lyright = new QVBoxLayout;
	right->setLayout(lyright);

	table = new QTableView();
	model = new CarListModel(table);
	table->setModel(model);
	QStringList HeaderList;
	HeaderList << "Nr inmatriculare" << "Producator" << "Model" << "Tip";
	lyright->addWidget(table);

	undo = new QPushButton("UNDO");
	lyright->addWidget(undo);


	map report = service.report();
	if (report["ALTELE"] > 0)
	{
		btnAltele = new QPushButton("Nr Altele");
		lyright->addWidget(btnAltele);
	}
	if (report["SPORT"] > 0)
	{
		btnSport = new QPushButton("Nr Sport");
		lyright->addWidget(btnSport);
	}
	if (report["SUV"] > 0)
	{
		btnSuv = new QPushButton("Nr Suv");
		lyright->addWidget(btnSuv);
	}
	if (report["MINI"] > 0)
	{
		btnMini = new QPushButton("Nr Mini");
		lyright->addWidget(btnMini);
	}

	lyMain->addWidget(left);
	lyMain->addWidget(right);

	QWidget* wid = new QWidget;
	QVBoxLayout* layout = new QVBoxLayout;
	wid->setLayout(layout);

	populateWash = new QPushButton("Populeaza lista de masini de spalat");
	populate = new QLineEdit();
	addWash = new QPushButton("Adauga masini in lista de spalat");
	add = new QLineEdit();
	emptyWash = new QPushButton("Goleste lista de masini de spalat");
	layout->addWidget(populate);
	layout->addWidget(populateWash);
	layout->addWidget(labelLPAdd);
	layout->addWidget(add);
	layout->addWidget(addWash);
	layout->addWidget(emptyWash);
	lyMain->addWidget(wid);

}

void CarGUI::reloadList(const std::vector<Car> carList)
{
	model->setList(carList);
}

void CarGUI::connectSignalSlots()
{
	service.addObserver(wash);
	QObject::connect(btnSuv, &QPushButton::clicked, [&]()
		{
			map report = service.report();
			QMessageBox::information(this, "Info", QString::number(report["SUV"]));
		});
	QObject::connect(btnMini, &QPushButton::clicked, [&]()
		{
			map report = service.report();
			QMessageBox::information(this, "Info", QString::number(report["MINI"]));
		});
	QObject::connect(btnSport, &QPushButton::clicked, [&]()
		{
			map report = service.report();
			QMessageBox::information(this, "Info", QString::number(report["SPORT"]));
		}
	);
	QObject::connect(btnAltele, &QPushButton::clicked, [&]()
		{
			map report = service.report();
			QMessageBox::information(this, "Info", QString::number(report["ALTELE"]));
		});
	QObject::connect(buttonAdd, &QPushButton::clicked, this, &CarGUI::addGUI);
	QObject::connect(buttonRemove, &QPushButton::clicked, this, &CarGUI::removeGUI);
	QObject::connect(buttonModify, &QPushButton::clicked, this, &CarGUI::modifyGUI);
	QObject::connect(buttonSortByLicensePlate, &QPushButton::clicked, this, &CarGUI::sortByLicensePlateGUI);
	QObject::connect(buttonSortByType, &QPushButton::clicked, this, &CarGUI::sortByTypeGUI);
	QObject::connect(buttonSortByProdModel, &QPushButton::clicked, this, &CarGUI::sortByProdModelGUI);
	QObject::connect(desc, &QCheckBox::stateChanged, this, &CarGUI::sortOrderChanged);
	QObject::connect(buttonFilterByType, &QPushButton::clicked, [&]()
		{
			string type = this->filterByType->text().toStdString();
			filterByType->clear();
			this->reloadList(service.filterByType(type));
		});
	QObject::connect(buttonFilterByProducer, &QPushButton::clicked, [&]()
		{
			string prod = this->filterByProducer->text().toStdString();
			filterByProducer->clear();
			this->reloadList(service.filterByProd(prod));
		});
	QObject::connect(undo, &QPushButton::clicked, this, &CarGUI::undoGUI);
	QObject::connect(butonLista, &QPushButton::clicked, [&]()
		{

			WashCRUDGUI* new_wash = new WashCRUDGUI(service);
			new_wash->initWashGUI();
			new_wash->connectSignalSlots();
			new_wash->reloadWashList(service.getWashList());
			new_wash->show();
			wash->service.addObserver(new_wash);

		});

	QObject::connect(butonRDOnly, &QPushButton::clicked, [&]()
		{
			WashRDOnlyGUI* new_rdonly = new WashRDOnlyGUI(wash);
			new_rdonly->show();

		});

	QObject::connect(addWash, &QPushButton::clicked, [&]()
		{
			string licPlate = add->text().toStdString();
			add->clear();
			service.addWash(licPlate);
			wash->service.notify();
		});

	QObject::connect(populateWash, &QPushButton::clicked, [&]()
		{
			int nr = populate->text().toInt();
			populate->clear();
			try
			{
				service.populateWash(nr);
				wash->service.notify();
			}
			catch (...)
			{
				QMessageBox::warning(this, "Warning", "Numarul dat este prea mare");
			}
			wash->service.notify();
		});

	QObject::connect(emptyWash, &QPushButton::clicked, [&]()
		{
			service.emptyWash();
			wash->service.notify();
		});
}



void CarGUI::addGUI()
{
	try
	{
		string lic = addLicensePlate->text().toStdString();
		addLicensePlate->clear();
		string prod = addProducer->text().toStdString();
		addProducer->clear();
		string _model = addModel->text().toStdString();
		addModel->clear();
		string tip = addType->text().toStdString();
		addType->clear();
		this->service.addCar(lic, prod, _model, tip);
		this->reloadList(this->service.getCarList());
		QMessageBox::information(this, "Info", QString::fromStdString("Masina a fost adaugata cu succes!"));

	}
	catch (const ExistentCarError& err)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(err.getMessage()));
	}
	catch (const InvalidCarError& err)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(err.getMessage()));
	}
}

void CarGUI::removeGUI()
{
	try
	{
		string denum = deleteLP->text().toStdString();
		deleteLP->clear();
		this->service.removeCar(denum);
		this->reloadList(service.getCarList());

		QMessageBox::information(this, "Info", QString::fromStdString("Masina stearsa cu succes!"));
	}

	catch (const InvalidCarError& err)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(err.getMessage()));
	}

	catch (const InexistentCarError& err)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(err.getMessage()));
	}
}

void CarGUI::modifyGUI()
{
	try
	{
		string lic = modifyLicensePlate->text().toStdString();
		modifyLicensePlate->clear();
		string prod = modifyProducer->text().toStdString();
		modifyProducer->clear();
		string _model = modifyModel->text().toStdString();
		modifyModel->clear();
		string tip = modifyType->text().toStdString();
		modifyType->clear();
		this->service.modifyCar(lic, lic, prod, _model, tip);
		this->reloadList(this->service.getCarList());
		QMessageBox::information(this, "Info", QString::fromStdString("Masina modificata cu succes!"));
	}
	catch (const InexistentCarError& err)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(err.getMessage()));
	}
	catch (const InvalidCarError& err)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(err.getMessage()));
	}
}

void CarGUI::sortByLicensePlateGUI()
{
	this->reloadList(service.sortByLicPlate(mode));
}

void CarGUI::sortByTypeGUI()
{
	this->reloadList(service.sortByType(mode));
}

void CarGUI::sortByProdModelGUI()
{
	this->reloadList(service.sortByProdModel(mode));
}

void CarGUI::sortOrderChanged(int state)
{
	if (state == Qt::Checked)
	{
		mode = 'd';
	}
	else
		mode = 'c';
}

void CarGUI::undoGUI()
{
	try
	{
		service.undo();
		reloadList(service.getCarList());
		QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes!"));
	}
	catch (const Error& err)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(err.getMessage()));
	}
}


CarGUI::CarGUI(CarService& cS) : service{ cS }
{
	wash = new WashCRUDGUI(service);
	wash->initWashGUI();
	wash->reloadWashList(service.getWashList());
	wash->connectSignalSlots();

	washRDOnly = new WashRDOnlyGUI(wash);
	washRDOnly->build_UI();

	initGUI();
	connectSignalSlots();
	reloadList(service.getCarList());
}