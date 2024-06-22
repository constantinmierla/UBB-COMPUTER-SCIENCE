#pragma once
#include<QAbstractTableModel>
#include<QWidget>
#include"service.h"
class TableModel : public QAbstractTableModel {
private:
	Service& service;
public:
	TableModel(Service& ser) :service{ ser } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return service.get_all().size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override
	{
		if (role == Qt::DisplayRole)
		{
			Melodie m = service.get_all()[index.row()];
			if (index.column() == 0)
			{
				return QString::number(m.get_id());
			}
			if (index.column() == 1)
			{
				return QString::fromStdString(m.get_titlu());
			}
			if (index.column() == 2)
			{
				return QString::fromStdString(m.get_artist());
			}
			if (index.column() == 3)
			{
				return QString::number(m.get_rank());
			}
			if (index.column() == 4)
			{
				return QString::number(service.rank(m.get_rank()));
			}
		}
		return QVariant{};
	}
	void set(Service& service)
	{
		auto top = createIndex(0, 0);
		auto button = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(top, button);
	}
};