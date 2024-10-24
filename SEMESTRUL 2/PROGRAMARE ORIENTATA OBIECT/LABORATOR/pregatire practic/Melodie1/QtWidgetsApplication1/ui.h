#pragma once
#include "qwidget.h"
#include "serv.h"
#include "qlineedit.h"
#include "qboxlayout.h"
#include "qmessagebox.h"
#include "qformlayout.h"
#include "qtablewidget.h"
#include <algorithm>
#include <qpushbutton>
#include "qslider.h"
#include "MyTable.h"
#include "qpainter.h"
#include "qcombobox.h"

class gui : public QWidget {
private:
	Service& serv;
public:
	gui(Service& s) :serv{ s } {
		initGUI();
		connectButtons();
		loadData();
	}
	//Painter* painter;
	QHBoxLayout* lyWindow = new QHBoxLayout;

	QTableView* table = new QTableView;
	MyTable* model = new MyTable{ serv.getAllService(),serv.rankService(),comboText,0 };
	QHBoxLayout* lymain = new QHBoxLayout;
	QPushButton* update = new QPushButton{ "Update" };
	QPushButton* remove = new QPushButton{ "Remove" };
	QLineEdit* id = new QLineEdit;
	QLineEdit* titlu = new QLineEdit;
	QSlider* slider = new QSlider(Qt::Horizontal);
	QSlider* slider2 = new QSlider(Qt::Horizontal);
	QComboBox* combo = new QComboBox;
	string comboText;
	QFormLayout* stanga = new QFormLayout;
	void initGUI() {
		slider->setMinimum(1);
		slider->setMaximum(10);
		table->setModel(model);
		setLayout(lymain);
		lymain->addWidget(table);
		stanga->addRow("Introduceti id-ul:", id);
		stanga->addRow("Introduceti titlul", titlu);
		stanga->addRow(update);
		stanga->addRow(remove);
		stanga->addRow(slider);
		stanga->addRow(combo);
		stanga->addRow(slider2);
		lymain->addLayout(stanga);
		slider2->setMaximum(10);
		slider2->setMinimum(1);
		vector<Melodie> all = serv.getAllService();
		sort(all.begin(), all.end(),
			[](Melodie& a, Melodie& b) {
				return a.get_rank() < b.get_rank();
			});
		map<string, int> rap = serv.raport(all);
		for (auto e : rap)
			combo->addItem(QString::fromStdString(e.first));

	}
	void loadData() {
		vector<Melodie> all = serv.getAllService();
		vector<int> rank = serv.rankService();
		sort(all.begin(), all.end(),
			[](Melodie& a, Melodie& b) {
				return a.get_rank() < b.get_rank();
			});
		model->setData2(all, rank, comboText, slider2->value());
		this->repaint();
	}

	void connectButtons() {
		QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this] {
			if (table->selectionModel()->selectedIndexes().isEmpty()) {
				titlu->setText("");
				return;
			}
			else
			{
				auto row = table->selectionModel()->selectedIndexes().at(0).row();
				auto valoare = table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString();
				titlu->setText(valoare);

			}
			});
		QObject::connect(update, &QPushButton::clicked, [this] {
			if (table->selectionModel()->selectedIndexes().isEmpty()) {
				return;
			}
			else {
				auto row = table->selectionModel()->selectedIndexes().at(0).row();
				auto idtext = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
				auto newTitle = titlu->text().toStdString();
				auto sliderVal = slider->value();
				serv.modifyService(idtext, newTitle, sliderVal);
				loadData();
			}
			});
		QObject::connect(remove, &QPushButton::clicked, [this] {
			if (table->selectionModel()->selectedIndexes().isEmpty())
				return;
			else {
				auto row = table->selectionModel()->selectedIndexes().at(0).row();
				auto idtext = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
				auto titletext = table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString();
				auto autortext = table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString();
				auto ranktext = table->model()->data(table->model()->index(row, 3), Qt::DisplayRole).toInt();
				auto txt = autortext.toStdString();
				auto txt2 = titletext.toStdString();
				if (serv.findArtist(txt) == 1) {
					QMessageBox::information(this, "Eroare", "Nu putem sterge deoarece artistul mai are o singura melodie!");
				}
				else
					serv.removeService(idtext, txt2, txt, ranktext);
				loadData();

			}

			});
		QObject::connect(combo, &QComboBox::currentTextChanged, [&](const QString& val) {
			comboText = val.toStdString();
			qDebug() << val;
			});
		QObject::connect(slider2, &QSlider::valueChanged, [&] {
			loadData();
			});
	}
	void paintEvent(QPaintEvent* ex)
	{
		QPainter painter(this);
		painter.setPen(Qt::yellow);
		for (auto e : serv.getAllService())
			painter.drawLine(e.get_rank(), e.get_rank() * 100, e.get_rank() * 10, e.get_rank() * 10);
	}
};
