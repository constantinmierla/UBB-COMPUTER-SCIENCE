#pragma once
#include<QWidget>
#include<QTableWidget>
#include<QLabel>
#include<QPushButton>
#include<QComboBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"model.h"
#include<QTableView>
#include"service.h"
#include<qlineedit.h>
#include<qformlayout.h>
#include<QMessageBox>
#include<qpainter.h>
#include<qevent.h>
#include <qradiobutton.h>
#include<cmath>
#include<qapplication.h>

using namespace std;
class Painter :public QWidget {
private:
	Service& service;
public:
	explicit Painter(Service& service) :service{ service } {
		/*
		* Functie care actualizeaza desenul
		*/
		this->repaint();
	}
	void paintEvent(QPaintEvent* ev)override;

};
class GUI :public QWidget {
private:
	Service& service;
	QTableView* table = new QTableView;
	ModelTable* model;
	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_nume = new QLineEdit;
	QLineEdit* edit_tip = new QLineEdit;
	QLineEdit* edit_nr = new QLineEdit;
	QPushButton* btn_modifica = new QPushButton{ "&Update" };
	QPushButton* btn_sterge = new QPushButton{ "&Sterge" };
	Painter* painter;
	QVBoxLayout* layout_paint = new QVBoxLayout;
	QRadioButton* buttonradio1 = new QRadioButton("1 cilindru", this);
	QRadioButton* buttonradio2 = new QRadioButton("2 cilindru", this);
	QRadioButton* buttonradio3 = new QRadioButton("4 cilindru", this);
	QRadioButton* buttonradio4 = new QRadioButton("8 cilindru", this);
	int nr = 0;
	void paintEvent(QPaintEvent* event)override;

	/*
	* Functie care incarca tabela
	*/
	void load_table();
	
	/*
	* Functie care conecteaza butoanele
	*/
	void conectare();

	/*
	* Functie care initializeaza interfata
	*/
	void init_gui();
public:
	GUI(Service& service) :service{ service } {
		init_gui();
		model = new ModelTable{ service };
		table->setModel(model);
		model->select_tip("");
		conectare();
		load_table();
		repaint();
	}
};