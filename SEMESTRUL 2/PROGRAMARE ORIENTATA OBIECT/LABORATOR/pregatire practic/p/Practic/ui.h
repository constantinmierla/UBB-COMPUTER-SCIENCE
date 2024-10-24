#pragma once
#include "service.h"
#include <qwidget.h>
#include <qtableview.h>
#include <qcombobox.h>
#include <qslider.h>
#include "qmessagebox.h"
#include "qlabel.h"
#include "qlayout.h"
#include "QWidget"
#include <qlineedit.h>
#include <QPushButton>

class UI : public QWidget
{
private:
	Service& serv;
	QWidget* app = new QWidget;
	QTableView* table = new QTableView;
	QSlider* slider = new QSlider;
	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_nume = new QLineEdit;
	QLineEdit* edit_tip = new QLineEdit;
	QLineEdit* edit_pret = new QLineEdit;
	QPushButton* btn_adauga = new QPushButton{ "Adauga" };
	QPushButton* btn_undo = new QPushButton{ "Undo" };
	QSlider* slider = new QSlider;
	QLabel* label = new QLabel;
	void init_gui();
	void connect_btn();
	void load_data();

public:
	UI(Service& serv) : serv{ serv } {
		init_gui();
		connect_btn();
		load_data();
	}
};