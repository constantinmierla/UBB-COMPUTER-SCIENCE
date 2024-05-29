#pragma once
#include <QtWidgets/QListWidget>
#include <QAbstractListModel>
#include <QAbstractTableModel>
#include "car.h"
#include <vector>
using namespace std;

class CarListModel : public QAbstractTableModel
{
private:
	// vectorul curent de masini
	vector<Car> carList;
public:

	// constructorul clasei model
	CarListModel(QObject* parent);

	// suprascriem metoda data pentru a afisa datele unei masini
	QVariant data(const QModelIndex& index, int role) const override;

	// suprascriem metoda rowCount ca sa returneze corect pentru tabelul nostru
	int rowCount(const QModelIndex& parent = QModelIndex()) const noexcept override;

	// suprascriem metoda columnCount ca sa returneze corect pentru tabelul nostru
	int columnCount(const QModelIndex& parent = QModelIndex()) const noexcept override;

	// suprascriem metoda headerData ca sa afiseze antetul corespunzator
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	// punem lista corespunzatoare
	void setList(const vector<Car>& _carList);
};