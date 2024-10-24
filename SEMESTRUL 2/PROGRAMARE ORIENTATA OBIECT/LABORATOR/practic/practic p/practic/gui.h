#pragma once
#include"service.h"
#include"model.h"
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QTableView>
#include<QTableWidget>
#include<QHBoxLayout>
#include<QMessageBox>
#include<QLineEdit>
#include<QFormLayout>
#include<QSlider>
#include"ferestre.h"
class GUI :public QWidget {
private:
	Service& service;
	QTableView* tbl = new QTableView;
	TableModel* model;
	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_nume = new QLineEdit;
	QLineEdit* edit_tip = new QLineEdit;
	QLineEdit* edit_pret = new QLineEdit;
	QPushButton* btn_adauga = new QPushButton{ "Adauga" };
	QPushButton* btn_undo = new QPushButton{ "Undo" };
	QSlider* slider = new QSlider{ Qt::Horizontal };
	QLabel* label = new QLabel;
	void init_gui();
	//initializeaza gui
	void conectare();
	//conecteaza compunentele intre ele
	void load_data();
	//uploadeaza datele in fisier
	vector<Fereastra*>f;
public:
	GUI(Service& service) :service{ service } {
		model = new TableModel{ service };
		tbl->setModel(model);
		init_gui();
		conectare();
		load_data();
	}
	//constrctor gui apeleaza cele 3 metode private si initilizeaza table model
};
