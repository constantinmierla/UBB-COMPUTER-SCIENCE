#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <qheaderview.h>
#include <QPushButton>
#include "service.h"
class gui : public QWidget {
private :
	Service& s;
public:

	QHBoxLayout* mainL = new QHBoxLayout;
	QVBoxLayout* listL = new QVBoxLayout;
	QTableWidget* listW = new QTableWidget;
	QVBoxLayout* btnL = new QVBoxLayout;
	QComboBox* combo = new QComboBox;
	QPushButton* sortarepret = new QPushButton("sortare pret");
	QPushButton* sortarenumar = new QPushButton("sortare numar");
	QPushButton* nesortat = new QPushButton("nesortat");
	void init_gui();
	void connectbutton();
	void refresh(vector<Produs> list);

	gui(Service& s)
		: s{ s } {
		init_gui();
		//connectbutton();
		refresh(s.get_all());
	}
};