#include "GUI.h"

void GUI::load_table(vector<Melodie> m)
{
	table->clearContents();
	table->setRowCount(m.size());
	for (int i = 0; i < m.size(); i++)
	{
		table->setItem(i, 0, new QTableWidgetItem(QString::number(m[i].get_id())));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(m[i].get_titlu())));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(m[i].get_artist())));
		table->setItem(i, 3, new QTableWidgetItem(QString::number(m[i].get_rank())));
	}
}
void Painter::paintEvent(QPaintEvent* ev) {

}
void GUI::paintEvent(QPaintEvent* ev) {
	QPainter p(this);
	p.setPen(Qt::blue);
	for (int i = 0; i <= 10; i++)
	{
		int x = service.rank(i);
		p.drawRect(300 + i * 10, p.device()->height() - 100, 10, -(x + 1) * 20);
	}
}
void GUI::conectare()
{
	QObject::connect(slider, &QSlider::sliderReleased, this, [&]() {
		lbl->setText(QString::number(slider->value()));
		});
	QObject::connect(btn_modifica, &QPushButton::clicked, this, [&]() {
		if (tbl->selectionModel()->selectedIndexes().isEmpty())
			QMessageBox::warning(this, "info", QString::fromStdString("nu ati selectat nimic"));
		else {
			auto row = tbl->selectionModel()->selectedIndexes()[0].row();
			string titlu = edit_titlu->text().toStdString();
			int id = tbl->model()->data(tbl->model()->index(row, 0), Qt::DisplayRole).toInt();
			qDebug() << id;
			string artist = tbl->model()->data(tbl->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
			int rank = slider->value();
			try {
				service.modifica(id, titlu, artist, rank);
				reload();
				QMessageBox::information(this, "info", QString::fromStdString("S-a modificat"));
			}
			catch (ValException ex) {
				QMessageBox::information(this, "info", QString::fromStdString("nu s-a modificat" + ex.get_mesaj()));
			}
		}
		});
	QObject::connect(btn_sterge, &QPushButton::clicked, this, [&]() {
		if (tbl->selectionModel()->selectedIndexes().isEmpty())
			QMessageBox::warning(this, "info", QString::fromStdString("nu ati selectat nimic"));
		else {
			auto row = tbl->selectionModel()->selectedIndexes()[0].row();
			int id = tbl->model()->data(tbl->model()->index(row, 0), Qt::DisplayRole).toInt();
			qDebug() << id;
			try {
				service.sterge(id);
				reload();
				QMessageBox::information(this, "info", QString::fromStdString("S-a sters"));
			}
			catch (exception ex) {
				QMessageBox::information(this, "info", QString::fromStdString("nu s-a sters"), QMessageBox::Save | QMessageBox::Discard);

			}
		}
		});

	QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
		if (tbl->selectionModel()->selectedIndexes().isEmpty())
			QMessageBox::warning(this, "info", QString::fromStdString("nu ati selectat nimic"));
		else {
			auto row = tbl->selectionModel()->selectedIndexes()[0].row();
			qDebug() << tbl->model()->data(tbl->model()->index(row, 1), Qt::DisplayRole).toString();
			edit_titlu->setText(tbl->model()->data(tbl->model()->index(row, 1), Qt::DisplayRole).toString());
		}
		});
}

void GUI::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	setLayout(main);
	QVBoxLayout* lleft = new QVBoxLayout;
	QVBoxLayout* lright = new QVBoxLayout;
	QWidget* right = new QWidget;
	QWidget* left = new QWidget;
	right->setLayout(lright);
	left->setLayout(lleft);
	main->addWidget(left);
	main->addWidget(right);
	table = new QTableWidget{ 10,4 };
	table->setHorizontalHeaderLabels({ "id","titlu","artist","rank" });
	lleft->addWidget(table);
	lleft->addWidget(tbl);
	lright->addWidget(btn_modifica);
	lright->addWidget(btn_sterge);
	lright->addWidget(edit_titlu);
	slider->setRange(0, 10);
	QWidget* l = new QWidget;
	QFormLayout* ll = new QFormLayout;
	l->setLayout(ll);
	ll->addWidget(lbl);
	ll->addWidget(slider);
	lright->addWidget(l);
	painter = new Painter{ service };
	painter->setLayout(layout_p);
}

void GUI::reload()
{
	model->set(service);
	load_table(service.sorteaza_rank());
}
