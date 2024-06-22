#include "gui.h"
#include<qitemselectionmodel.h>
void Painter::paintEvent(QPaintEvent* ev) {

}

void GUI::paintEvent(QPaintEvent* ev) {

	QPainter p{ this };
	p.setPen(Qt::darkMagenta);
	int unu = 0, doi = 0, patru = 0, opt = 0;
	for (auto& m : service.get_all())
	{
		if (m.get_nr() == 1) {
			unu++;
		}
		if (m.get_nr() == 2) {
			doi++;
		}
		if (m.get_nr() == 4) {
			patru++;
		}
		if (m.get_nr() == 8) {
			opt++;
		}
	}
	p.drawEllipse(QPoint(10, 10), unu * 8, unu * 8);
	p.drawEllipse(QPoint(p.device()->width() - 10, 10), doi * 8, doi * 8);
	p.drawEllipse(QPoint(10, p.device()->height() - 10), patru * 8, patru * 8);
	p.drawEllipse(QPoint(p.device()->width() - 10, p.device()->height() - 10), opt * 8, opt * 8);
}
void GUI::load_table()
{
	model->set(service);
	map<string, int>rez = service.returneaza_tip();
	repaint();

}

void GUI::conectare()
{
	QObject::connect(btn_modifica, &QPushButton::clicked, this, [&]() {
		if (table->selectionModel()->selectedIndexes().isEmpty())
			QMessageBox::warning(this, "info", QString::fromStdString("nu ati selectat nimic"));
		else {
			auto row = table->selectionModel()->selectedIndexes()[0].row();
			string titlu = edit_nume->text().toStdString();
			int id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			qDebug() << id;
			string artist = table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
			int rank = edit_nr->text().toInt();
			try {
				service.modifica(id, titlu, artist, rank);
				load_table();
				QMessageBox::information(this, "info", QString::fromStdString("S-a modificat"));
			}
			catch (ValException ex) {
				QMessageBox::information(this, "info", QString::fromStdString("nu s-a modificat" + ex.get_mesaj()));
			}
		}
		});
	QObject::connect(btn_sterge, &QPushButton::clicked, this, [&]() {
		if (table->selectionModel()->selectedIndexes().isEmpty())
			QMessageBox::warning(this, "info", QString::fromStdString("nu ati selectat nimic"));
		else {
			auto row = table->selectionModel()->selectedIndexes()[0].row();
			int id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			qDebug() << id;
			try {
				service.sterge(id);
				load_table();
				QMessageBox::information(this, "info", QString::fromStdString("S-a sters"));
			}
			catch (exception ex) {
				QMessageBox::information(this, "info", QString::fromStdString("nu s-a sters"), QMessageBox::Save | QMessageBox::Discard);

			}
		}
		});

	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
		if (table->selectionModel()->selectedIndexes().isEmpty())
			QMessageBox::warning(this, "info", QString::fromStdString("nu ati selectat nimic"));
		else {
			auto row = table->selectionModel()->selectedIndexes()[0].row();
			qDebug() << table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString();
			edit_nume->setText(table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString());
		}
		});
	QObject::connect(btn_sterge, &QPushButton::clicked, this, [&]() {
		try {
			load_table();
			repaint();
			QMessageBox::information(this, "info", QString::fromStdString("sters cu succes"));
		}
		catch (ValException val) {
			QMessageBox::warning(this, "info", QString::fromStdString("erori:" + val.get_mesaj()));
		}});
	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (table->selectionModel()->selectedIndexes().isEmpty()) {
			qDebug() << "BLLLL";
			return;
		}
		qDebug() << "hahah";
		int selRow = table->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = table->model()->index(selRow, 0);
		auto cel0Value = table->model()->data(cel0Index, Qt::DisplayRole).toString();
		edit_id->setText(cel0Value);
		auto cel1Index = table->model()->index(selRow, 1);
		auto cel1Value = table->model()->data(cel1Index, Qt::DisplayRole).toString();
		edit_nume->setText(cel1Value);
		auto cel2Index = table->model()->index(selRow, 2);
		auto cel2Value = table->model()->data(cel2Index, Qt::DisplayRole).toString();
		edit_tip->setText(cel2Value);
		auto cel3Index = table->model()->index(selRow, 3);
		auto cel3Value = table->model()->data(cel3Index, Qt::DisplayRole).toString();
		edit_nr->setText(cel3Value);
		qDebug() << "x";
		repaint();
		});
}

void GUI::init_gui()
{
	painter = new Painter{ service };
	painter->setLayout(layout_paint);
	QHBoxLayout* main = new QHBoxLayout;
	QVBoxLayout* lright = new QVBoxLayout;
	QVBoxLayout* lleft = new QVBoxLayout;
	QWidget* right = new QWidget;
	QWidget* left = new QWidget;
	setLayout(main);
	main->addWidget(left);
	main->addWidget(right);
	left->setLayout(lleft);
	right->setLayout(lright);
	lleft->addWidget(table);
	lright->addWidget(buttonradio1);
	lright->addWidget(buttonradio2);
	lright->addWidget(buttonradio3);
	lright->addWidget(buttonradio4);

	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow("ID:", edit_id);
	lform->addRow("Denumire:", edit_nume);
	lform->addRow("Tip:", edit_tip);
	lform->addRow("Nr cilindri:", edit_nr);
	lform->addWidget(btn_modifica);
	lform->addWidget(btn_sterge);
	lleft->addWidget(form);
}
