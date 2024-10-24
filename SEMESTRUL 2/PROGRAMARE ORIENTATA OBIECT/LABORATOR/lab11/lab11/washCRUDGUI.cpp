#include "washCRUDGUI.h"
#include "exception.h"

void WashCRUDGUI::initWashGUI()
{

	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout{};
	setLayout(lyMain);

	//left part
	QWidget* left = new QWidget;
	QVBoxLayout* lyleft = new QVBoxLayout;
	left->setLayout(lyleft);

	// schimba pe lista de masini de spalat
	QWidget* form0 = new QWidget;
	QFormLayout* lyform0 = new QFormLayout;
	form0->setLayout(lyform0);
	butonAcasa = new QPushButton("Schimba pe meniul principal");
	lyform0->addWidget(butonAcasa);
	lyleft->addWidget(form0);


	// popularea listei de masini de spalat
	QWidget* form2 = new QWidget;
	QFormLayout* lyform2 = new QFormLayout;
	form2->setLayout(lyform2);
	populateWash = new QLineEdit;
	lyform2->addRow(labelPopulateWash, populateWash);
	butonPopulateWash = new QPushButton("Genereaza masini");
	lyform2->addWidget(butonPopulateWash);
	lyleft->addWidget(form2);

	// golirea listei de masini de spalat
	butonEmptyWash = new QPushButton("Goleste lista de masini de spalat");
	lyleft->addWidget(butonEmptyWash);


	// lista curenta de masini
	QWidget* right = new QWidget;
	QHBoxLayout* lyright = new QHBoxLayout;
	right->setLayout(lyright);
	windowList = new QListWidget;
	lyright->addWidget(windowList);

	lyMain->addWidget(left);
	lyMain->addWidget(right);
}

void WashCRUDGUI::connectSignalSlots()
{
	service.addObserver(this);
	QObject::connect(butonEmptyWash, &QPushButton::clicked, [&]()
		{
			this->service.emptyWash();
			this->reloadWashList(this->service.getWashList());
			QMessageBox::information(this, "Info", QString::fromStdString("Lista a fost golita cu succes!"));
		});
	QObject::connect(butonPopulateWash, &QPushButton::clicked, this, &WashCRUDGUI::generateWashGUI);
	QObject::connect(butonAcasa, &QPushButton::clicked, [&]()
		{
			hide();
		});
}

void WashCRUDGUI::generateWashGUI()
{
	try
	{
		int nr = populateWash->text().toInt();
		populateWash->clear();
		this->service.populateWash(nr);
		this->reloadWashList(this->service.getWashList());
		QMessageBox::information(this, "Info", QString::fromStdString("Masinile au fost adaugate cu succes!"));
		service.notify();
	}
	catch (const InvalidGenerateNumber& err)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(err.getMessage()));
	}
}

void WashCRUDGUI::reloadWashList(const std::vector<Car> carList)
{
	windowList->clear();
	for (const auto& car : carList)
	{
		QString itemText =
			QString::fromStdString(car.getLicensePlate()) + " | " +
			QString::fromStdString(car.getProducer()) + " | " +
			QString::fromStdString(car.getModel()) + " | " +
			QString::fromStdString(car.getType());
		QListWidgetItem* item = new QListWidgetItem(itemText);
		windowList->addItem(item);
	}
}