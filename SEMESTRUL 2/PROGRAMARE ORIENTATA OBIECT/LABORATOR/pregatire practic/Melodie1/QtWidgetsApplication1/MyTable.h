#pragma once
#include "qtableview.h"
#include "serv.h"
#include "qbrush.h"
class MyTable : public QAbstractTableModel {
private:
	vector<Melodie> all;
	vector<int> ranking;
	string& val;
	int slider;
public:
	MyTable(vector<Melodie> a, vector<int> b, string& c, int d) :all{ a }, ranking{ b }, val{ c }, slider{ d } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return all.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::BackgroundRole) {
			Melodie b = all[index.row()];
			if (b.get_artist() == val)
			{
				QBrush p{ Qt::darkGreen };
				return p;
			}
			if (b.get_rank() == slider) {
				QBrush m{ Qt::darkCyan };
				return m;
			}
		}
		if (role == Qt::DisplayRole) {
			Melodie a = all[index.row()];
			if (index.column() == 0) {
				return QString::number(a.get_id());
			}
			if (index.column() == 1) {
				return QString::fromStdString(a.get_titlu());
			}
			if (index.column() == 2) {
				return QString::fromStdString(a.get_artist());
			}
			if (index.column() == 3) {
				return QString::number(a.get_rank());
			}
			if (index.column() == 4) {
				return QString::number(ranking[a.get_rank() - 1]);
			}
		}
		return QVariant();
	}
	void setData2(vector<Melodie> _all, vector<int> _rank, string& d, int e) {
		this->all = _all;
		this->val = d;
		this->slider = e;
		this->ranking = _rank;
		auto LeftTop = createIndex(0, 0);
		auto RightBotton = index(rowCount(), columnCount());
		layoutChanged();
		dataChanged(LeftTop, RightBotton);
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole)
			if (orientation == Qt::Horizontal)
				switch (section) {
				case 0:
					return tr("ID");
				case 1:
					return tr("Titlu");
				case 2:
					return tr("Artist");
				case 3:
					return tr("Rank");
				case 4:
					return tr("Clasament");
				default:
					return QString("");

				}
		return QVariant();
	}
};