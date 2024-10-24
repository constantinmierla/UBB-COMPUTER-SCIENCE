#pragma once
#include"service.h"
#include"observer.h"
#include<QWidget>
#include<QLabel>
#include<QHBoxLayout>
class Fereastra :public QWidget, public Observer {
private:
	Service& service;
	string text;
	int numar;
	QLabel* lbl = new QLabel;
	void init_gui()
	{
		QHBoxLayout* main = new QHBoxLayout;
		setLayout(main);
		main->addWidget(lbl);
		setWindowTitle(QString::fromStdString(text));
	}
	void load_data() {
		lbl->setText(QString::number(service.numar(text)));
	}
public:
	Fereastra(Service& service, const string text, const int  numar) :service{ service }, text{ text }, numar{ numar } {
		service.addObserver(this);
		init_gui();
		load_data();
	}
	void update()override
	{
		load_data();
	}
	~Fereastra()
	{
		service.eraseObserver(this);
	}

};