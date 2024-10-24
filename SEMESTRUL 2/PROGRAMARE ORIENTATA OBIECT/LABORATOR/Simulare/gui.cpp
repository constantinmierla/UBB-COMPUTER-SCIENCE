#include "gui.h"

void gui::init_gui()
{
	setLayout(mainL);
	listW->setColumnCount(2);
	listW->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	listW->setSelectionBehavior(QAbstractItemView::SelectRows);
	listW->setSelectionMode(QAbstractItemView::SingleSelection);
	listW->setFocusPolicy(Qt::NoFocus);
	listL->addWidget(listW);
	btnL->addStretch();
	btnL->addWidget(sortarepret);
	btnL->addWidget(sortarenumar);
	btnL->addWidget(nesortat);

	mainL->addLayout(listL);
	mainL->addLayout(btnL);
}

void gui::connectbutton()
{

}
void gui::refresh(vector<Produs> list)
{
	listW->clear();
	listW->setRowCount(list.size() + 1);

	QTableWidgetItem* item;

	item = new QTableWidgetItem;
	item->setText(QString("Denumire"));
	listW->setItem(0, 0, item);

	item = new QTableWidgetItem;
	item->setText(QString("Pret"));
	listW->setItem(0, 1, item);
	int pos = 1;

	//item = new QTableWidgetItem;

	for (auto& p : list)
	{
		item = new QTableWidgetItem;
		item->setText(QString::fromStdString(p.get_denumire()));
		//item->setBackground(color);
		item->setForeground(Qt::white);
		listW->setItem(pos, 0, item);

		item = new QTableWidgetItem;
		item->setText(QString::number(p.get_pret()));
		//item->setBackground(color);
		item->setForeground(Qt::white);
		listW->setItem(pos, 1, item);

		++pos;
	}
}