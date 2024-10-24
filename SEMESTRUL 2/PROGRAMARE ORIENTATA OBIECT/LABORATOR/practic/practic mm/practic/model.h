#pragma once
#include"service.h"
#include"QWidget"
#include<QAbstractTableModel>
class TableModel :public QAbstractTableModel
{
private:
	Service& service;
public:
	TableModel(Service& service) :service{ service } {};
	//constructor
	int columnCount(const QModelIndex& parent = QModelIndex())const override {
		return 6;
	}
	//seteaza numar coloane
	int rowCount(const QModelIndex& parent = QModelIndex())const override {
		return service.get_all().size();
	}
	//seteaza numar linii
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override {
		if (role == Qt::DisplayRole) {
			Melodie m = service.get_all()[index.row()];
			if (index.column() == 0) {
				return QString::number(m.get_id());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(m.get_titlu());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(m.get_artist());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(m.get_gen());
			}
			else if (index.column() == 4) {
				return QString::number(service.artist(m.get_artist()));
			}
			else if (index.column() == 5) {
				return QString::number(service.gen(m.get_gen()));
			}
		}
		return QVariant{};
	}
	//seteaza in fiecare coloana informatia utila
	void setOferte(Service& service) {
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft, bottomR);
	}
	//emite semnale cand se schimba ceva
};