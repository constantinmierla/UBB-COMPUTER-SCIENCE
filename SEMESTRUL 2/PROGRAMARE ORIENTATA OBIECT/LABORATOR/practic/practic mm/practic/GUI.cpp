#include "GUI.h"
#include<QPainter>
void GUI::load_table(vector<Melodie>melodii)
{
	table->clearContents();
	table->setRowCount(melodii.size());
	int line = 0;
	for (int i = 0; i < melodii.size(); i++)
	{
		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(to_string(melodii[i].get_id()))));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(melodii[i].get_titlu())));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(melodii[i].get_artist())));
		table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(melodii[i].get_gen())));
	}

}

void GUI::connect()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, this, [&]() {
		try {
			string artist = edit_artist->text().toStdString();
			string gen = edit_gen->text().toStdString();
			string titlu = edit_titlu->text().toStdString();
			qDebug() << artist << " " << gen << " " << titlu;
			edit_artist->clear();
			edit_gen->clear();
			edit_titlu->clear();
			service.adauga(titlu, artist, gen);
			load_table(service.sorteaza_autor());
			reload_table();
			QMessageBox::information(this, "info", QString::fromStdString("Melodie adaugata cu succes!"));
		}
		catch (ValException& val)
		{
			QMessageBox::warning(this, "info", QString::fromStdString("Melodia nu s-a putut adauga " + val.get_mesaj()));
		}
		});
	QObject::connect(btn_sterge, &QPushButton::clicked, this, [&]() {
		if (tbl->selectionModel()->selectedIndexes().isEmpty())
			QMessageBox::warning(this, "info", QString::fromStdString("nu ati selectat nimic"));
		else {
			auto row = tbl->selectionModel()->selectedIndexes()[0].row();
			int id = tbl->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			qDebug() << id;
			service.sterge(id);
			reload_table();
			load_table(service.sorteaza_autor());
			QMessageBox::information(this, "info", QString::fromStdString("Element sters cu succes"));
		}
		});
}

void GUI::init_gui()
{
	painter = new Painter{ service };
	painter->setLayout(layout_paint);
	QHBoxLayout* main = new QHBoxLayout;
	this->setLayout(main);
	QWidget* left = new QWidget;
	QWidget* right = new QWidget;
	QVBoxLayout* lleft = new QVBoxLayout;
	QVBoxLayout* lright = new QVBoxLayout;
	left->setLayout(lleft);
	right->setLayout(lright);
	table = new QTableWidget{ 10,4 };
	table->setHorizontalHeaderLabels({ "id", "titlu", "artist", "gen" });
	lleft->addWidget(table);
	lleft->addWidget(tbl);
	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow(lbl_artist, edit_artist);
	lform->addRow(lbl_titlu, edit_titlu);
	lform->addRow(lbl_gen, edit_gen);
	lright->addWidget(form);
	lright->addWidget(btn_adauga);
	lright->addWidget(btn_sterge);
	main->addWidget(left);
	main->addWidget(right);

}

void GUI::reload_table()
{
	modelTable->setOferte(service);
}
void Painter::paintEvent(QPaintEvent* ev) {

}
void GUI::paintEvent(QPaintEvent* ev) {

	QPainter p{ this };
	p.setPen(Qt::darkMagenta);
	int pop = 0, rock = 0, folk = 0, disco = 0;
	for (auto& m : service.get_all())
	{
		if (m.get_gen() == "pop") {
			pop++;
			p.drawEllipse(QPoint(10, 10), pop * 8, pop * 8);
		}
		if (m.get_gen() == "folk") {
			folk++;
			p.drawEllipse(QPoint(p.device()->width() - 10, 10), folk * 8, folk * 8);
		}
		if (m.get_gen() == "disco") {
			disco++;
			p.drawEllipse(QPoint(10, p.device()->height() - 10), disco * 8, disco * 8);
		}
		if (m.get_gen() == "rock") {
			rock++;
			p.drawEllipse(QPoint(p.device()->width() - 10, p.device()->height() - 10), rock * 8, rock * 8);
		}
	}
}