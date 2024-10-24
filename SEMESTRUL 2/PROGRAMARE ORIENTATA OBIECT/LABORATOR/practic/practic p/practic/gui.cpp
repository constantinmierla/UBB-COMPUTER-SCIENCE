#include "gui.h"

void GUI::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	setLayout(main);
	main->addWidget(tbl);
	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow("id:", edit_id);
	lform->addRow("nume:", edit_nume);
	lform->addRow("tip:", edit_tip);
	lform->addRow("pret:", edit_pret);
	lform->addWidget(btn_adauga);
	lform->addWidget(btn_undo);
	lform->addWidget(slider);
	lform->addWidget(label);
	main->addWidget(form);
	map<string, int>rez = service.tipuri();
	for (auto l : rez)
	{
		Fereastra* qq = new Fereastra(service, l.first, l.second);
		f.push_back(qq);
		qq->show();
	}
}

void GUI::conectare()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, this, [&]() {
		int id = edit_id->text().toInt();
		string nume = edit_nume->text().toStdString();
		string tip = edit_tip->text().toStdString();
		double pret = edit_pret->text().toDouble();
		edit_id->clear();
		edit_nume->clear();
		edit_tip->clear();
		edit_pret->clear();
		try {
			service.adauga(id, nume, tip, pret);
			load_data();
			QMessageBox::information(this, "info", QString::fromStdString("adaugat cu succes"));
		}
		catch (ValException& ex)
		{
			QMessageBox::warning(this, "info", QString::fromStdString(ex.get_mesaj()));
		}
		});
	QObject::connect(slider, &QSlider::valueChanged, this, [&]() {
		int value = slider->value();
		label->setText(QString::number(value));
		model->setVal(value);
		});
	QObject::connect(btn_undo, &QPushButton::clicked, this, [&]() {
		try {
			service.undo();
			load_data();
		}
		catch (exception& ex)
		{
			QMessageBox::warning(this, "info", QString::fromStdString("nu se poate face undo"));
		}
		});
}

void GUI::load_data()
{
	model->set(service);
}
