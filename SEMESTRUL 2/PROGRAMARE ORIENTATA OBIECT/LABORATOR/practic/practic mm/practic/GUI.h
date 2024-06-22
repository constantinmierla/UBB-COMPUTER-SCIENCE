#pragma once
#include<iostream>
#include"service.h"
#include<QListWidget>
#include<QWidget>
#include<QTableWidget>
#include<qlabel.h>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include"model.h"
#include<QLineEdit>
#include<QPushButton>
#include<QFormLayout>
#include<QmessageBox>
#include<Qdebug.h>
using namespace std;
class Painter :public QWidget {
private:
	Service& service;
public:
	explicit Painter(Service& service) :service{ service } {
		this->repaint();
	}
	void paintEvent(QPaintEvent* ev)override;
};
class GUI : public QWidget {
private:
	Service& service;
	QTableWidget* table;
	TableModel* modelTable;
	QTableView* tbl = new QTableView;
	QLabel* lbl_artist = new QLabel{ "Artist:" };
	QLabel* lbl_titlu = new QLabel{ "Titlu:" };
	QLabel* lbl_gen = new QLabel{ "Gen:" };
	QLineEdit* edit_artist = new QLineEdit;
	QLineEdit* edit_titlu = new QLineEdit;
	QLineEdit* edit_gen = new QLineEdit;
	QPushButton* btn_adauga = new QPushButton("Adauga");
	QPushButton* btn_sterge = new QPushButton("Sterge");
	Painter* painter;
	QVBoxLayout* layout_paint = new QVBoxLayout;
	void load_table(vector<Melodie>lista);
	void connect();
	void init_gui();
	void reload_table();
	void paintEvent(QPaintEvent* ev)override;
public:
	GUI(Service& service) :service{ service } {
		init_gui();
		modelTable = new TableModel{ service };
		tbl->setModel(modelTable);
		connect();
		load_table(service.sorteaza_autor());
		reload_table();
		this->repaint();
	};

};