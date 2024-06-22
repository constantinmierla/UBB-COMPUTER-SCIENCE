#pragma once
#include "domain.h"
#include "repo.h"
#include "validator.h"
#include "serv.h"
#include<QWidget>
#include<QTableWidget>
#include<QLabel>
#include<QPushButton>
#include<QComboBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"model.h"
#include<QTableView>
#include<qlineedit.h>
#include<qformlayout.h>
#include<QMessageBox>
#include<qpainter.h>
#include<qevent.h>
#include<cmath>
#include<qapplication.h>

class Painter : public QWidget {
private:
	Service& serv;
public:
	explicit Painter(Service& serv) : serv{ serv } {
		this->repaint();
	};
	void paintEvent(QPaintEvent* event)override {
	}
};
class GUI : public QWidget {
private:
	Service& serv;
	QPushButton* button = new QPushButton{ "Select" };
	QTableView* table = new QTableView;

	ModelTable* model;

	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_nume = new QLineEdit;
	QLineEdit* edit_tip = new QLineEdit;
	QLineEdit* edit_nr = new QLineEdit;

	QPushButton* btn_adauga = new QPushButton{ "Adauga" };

	QComboBox* combo = new QComboBox;
	
	Painter* painter;
	QVBoxLayout* lpaint = new QVBoxLayout;
	QPoint raza;
	int nr = 0;

	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void load_table();
	void init_gui();
	void conectare();
public:
	GUI(Service& serv) : serv {serv} 
	{
		init_gui();
		model = new ModelTable{ serv };
		table->setModel(model);
		model->select_tip("");
		conectare();
		load_table();
	}
};