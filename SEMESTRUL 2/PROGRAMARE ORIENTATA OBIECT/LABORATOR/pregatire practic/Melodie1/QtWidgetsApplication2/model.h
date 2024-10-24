#pragma once
#include "serv.h"
#include <QWidget>
#include <QAbstractTableModel>

class ModelTable : public QAbstractTableModel {
private:
	Service& serv;
	string text;
public:
	ModelTable(Service& serv) : serv{ serv } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return serv.getAll().size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole)
		{
			Tractor t = serv.getAll()[index.row()];
			if (index.column() == 0)
				return QString::number(t.get_id());
			if (index.column() == 1)
				return QString::fromStdString(t.get_denumire());
			if (index.column() == 2)
				return QString::fromStdString(t.get_tip());
			if (index.column() == 3)
				return QString::number(t.get_roti());
			if (index.column() == 4)
				return QString::number(serv.tip(t.get_tip()));
		}
		if (role == Qt::BackgroundRole)
		{
			Tractor t = serv.getAll()[index.row()];
			if (t.get_tip() == text)
				return QBrush(Qt::red);
		}
		return QVariant{};
	}
	void set(Service& serv) {
		auto f = createIndex(0, 0);
		auto b = createIndex(rowCount() - 1, columnCount() - 1);
		emit layoutChanged();
		emit dataChanged(f, b);
	}
	void select_tip(const string& text1) {
		text = text1;
		set(serv);
	}
	Qt::ItemFlags flags(const QModelIndex&) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}
};