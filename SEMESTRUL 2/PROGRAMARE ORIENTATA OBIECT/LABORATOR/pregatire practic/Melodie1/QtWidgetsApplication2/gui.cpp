#include "gui.h"
#include "qformlayout.h"
#include<qitemselectionmodel.h>
#include <qpainter.h>
void GUI::paintEvent(QPaintEvent* event)
{
	if (!(table->selectionModel()->selectedIndexes().isEmpty()))
	{
		QPainter p(this);
		p.setPen(Qt::blue);
		auto row = table->selectionModel()->selectedIndexes()[0].row();
		int x = table->model()->data(table->model()->index(row, 3), Qt::DisplayRole()).toInt();
		qDebug() << x;
		for (int i = 0; i < x; i++)
		{
			p.drawEllipse(QPoint(50, p.device()->height() - 10), (i * 5 + 10) * 2, (i * 5 + 10) * 2);
			raza = QPoint(50, p.device()->height() - 10);
			nr = x;
		}
	}
}

void GUI::mousePressEvent(QMouseEvent* event)
{
	QPoint clickPos = event->pos();
	int radius = (nr * 5 + 10) * 2;
	/*if (sqrt(pow(raza.x() - clickPos.x(), 2) + pow(raza.y() - clickPos.y(), 2)) <= radius) {
		qDebug() << "bbb";
		auto row = table->selectionModel()->selectedIndexes()[0].row();
		int currentWheels = table->model()->data(table->model()->index(row, 3), Qt::DisplayRole).toInt();
		qDebug() << currentWheels;
		if (currentWheels > 2)
		{
			currentWheels -= 2;
			string denumire = table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString().toStdString();
			string gen = table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
			int id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			service.modifica(id, denumire, gen, currentWheels);
			model->set(service);
			repaint();
			//break;
		}
	}
	*/
	if (QPoint(raza - clickPos).manhattanLength() <= radius)
	{
		// Circle clicked, decrement the number of wheels by 2
		qDebug() << "aaa";
		auto row = table->selectionModel()->selectedIndexes()[0].row();
		int currentWheels = table->model()->data(table->model()->index(row, 3), Qt::DisplayRole).toInt();
		qDebug() << currentWheels;
		if (currentWheels > 2)
		{
			currentWheels -= 2;
			string denumire = table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString().toStdString();
			string gen = table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
			int id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			serv.modifica(id, denumire, gen, currentWheels);
			model->set(serv);
			repaint();
		}
	}
}
void GUI::load_table()
{
	model->set(serv);
	map<string, int> rez = serv.returneaza();
	combo->clear();
	repaint();
	combo->addItem("None");
	combo->setCurrentIndex(0);
	for (auto& l : rez)
	{
		combo->addItem(QString::fromStdString(l.first));
	}
}

void GUI::conectare()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, this, [&]() {
		try {
			int id = edit_id->text().toInt();
			int nr = edit_nr->text().toInt();
			string denumire = edit_nume->text().toStdString();
			string tip = edit_tip->text().toStdString();
			serv.adauga(id, denumire, tip, nr);
			load_table();
			repaint();
			QMessageBox::information(this, "info", QString::fromStdString("adaugat cu succes"));
		}
		catch (ValException val) {
			QMessageBox::warning(this, "info", QString::fromStdString("erori:" + val.get_mesaj()));
		}});
			QObject::connect(combo, &QComboBox::currentIndexChanged, this, [&]() {
				string text = combo->currentText().toStdString();
				model->select_tip(text);
				
				});
			QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
				if (table->selectionModel()->selectedIndexes().isEmpty()) {
					return;
				}
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
			QObject::connect(button, &QPushButton::clicked, this, [&]() {
				repaint();
				});
}
void GUI::init_gui() {
	painter = new Painter{ serv };
	//painter->setLayout{ lpaint };
	QHBoxLayout* main = new QHBoxLayout;
	auto lright = new QVBoxLayout;
	auto lleft = new QVBoxLayout;
	auto right = new QWidget;
	auto left = new	QWidget;
	setLayout(main);
	main->addWidget(left);
	main->addWidget(right);
	left->setLayout(lleft);
	right->setLayout(lright);
	lleft->addWidget(table);
	auto form = new QWidget;
	auto lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow("ID: ", edit_id);
	lform->addRow("Denumire: ", edit_nume);
	lform->addRow("Tip: ", edit_tip);
	lform->addRow("Nr roti: ", edit_nr);

	lform->addWidget(btn_adauga);
	lleft->addWidget(form);
	combo->clear();
	lright->addWidget(combo);
	lright->addWidget(button);
}
