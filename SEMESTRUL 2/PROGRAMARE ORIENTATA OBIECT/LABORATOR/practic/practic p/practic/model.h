#pragma once
#include"service.h"
#include<QWidget>
#include<QAbstractTableModel>
class TableModel :public QAbstractTableModel {
private:
	Service& service;
	int value = 0;
public:
	TableModel(Service& service) :service{ service } {};
	//constructor primeste referinta la service
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return service.sorteaza().size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole)
		{
			Produs p = service.sorteaza()[index.row()];
			if (index.column() == 0)
			{
				return QString::number(p.get_id());
			}
			if (index.column() == 1)
			{
				return QString::fromStdString(p.get_nume());
			}
			if (index.column() == 2)
			{
				return QString::fromStdString(p.get_tip());
			}
			if (index.column() == 3)
			{
				return QString::number(p.get_pret());
			}
		}
		if (role == Qt::BackgroundRole)
		{
			Produs p = service.sorteaza()[index.row()];
			if (p.get_pret() <= value)
				return QBrush{ Qt::red };
		}
		return QVariant{};
	}
	void set(Service& service) {
		auto top = createIndex(0, 0);
		auto buttom = createIndex(rowCount(), columnCount());
		emit dataChanged(top, buttom);
		emit layoutChanged();
	}
	void setVal(int v) {
		auto top = createIndex(0, 0);
		auto buttom = createIndex(rowCount(), columnCount());
		emit dataChanged(top, buttom);
		emit layoutChanged();
		value = v;
	}
};