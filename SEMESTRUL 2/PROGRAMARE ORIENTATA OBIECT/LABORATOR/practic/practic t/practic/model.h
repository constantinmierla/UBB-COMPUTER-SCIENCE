#pragma once
#include"service.h"
#include<QWidget>
#include<QAbstractTableModel>

class ModelTable :public QAbstractTableModel {
private:
	Service& service;
	string text;
public:
	ModelTable(Service& service) :service{ service } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return service.get_all().size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole)
		{
			Tractor t = service.get_all()[index.row()];
			if (index.column() == 0)
			{
				return QString::number(t.get_id());
			}
			if (index.column() == 1)
			{
				return QString::fromStdString(t.get_denumire());
			}
			if (index.column() == 2)
			{
				return QString::fromStdString(t.get_tip());
			}
			if (index.column() == 3)
			{
				return QString::number(t.get_nr());
			}
			if (index.column() == 4)
			{
				return QString::number(service.tip(t.get_tip()));
			}
		}
		return QVariant{};
	}
	void set(Service& service)//,const string& text)
	{

		auto f = createIndex(0, 0);
		auto b = createIndex(rowCount() - 1, columnCount() - 1);
		emit layoutChanged();
		emit dataChanged(f, b);
	}
	void select_tip(const string& text1) {
		text = text1;
		set(service);
	}
	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}
};