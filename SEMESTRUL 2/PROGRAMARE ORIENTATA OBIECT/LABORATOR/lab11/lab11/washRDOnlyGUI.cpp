#include "washRDOnlyGUI.h"
#include "washCRUDGUI.h"
#include "qpainter.h"
#include "observer.h"
#pragma warning( disable : 4100 )

WashRDOnlyGUI::WashRDOnlyGUI(WashCRUDGUI* c) : cos{ c }
{
	this->build_UI();
	cos->service.addObserver(this);
}
void WashRDOnlyGUI::build_UI()
{

	QHBoxLayout* mainly = new QHBoxLayout;
	this->setLayout(mainly);
}
void WashRDOnlyGUI::update()
{
	this->repaint();
}

void WashRDOnlyGUI::paintEvent(QPaintEvent* ev)
{

	QPainter p(this);
	srand(time(nullptr));

	int x = -20;
	for (int i = 1; i <= cos->service.getWashList().size(); i++)
	{
		x += 40;
		const int forma = rand() % 4;
		const int inaltime = rand() % 130;
		const int start_y = rand() % 60;
		QColor color;

		const int color_num = rand() % 10;
		switch (color_num)
		{
		case 0:
			color = Qt::red;
			break;
		case 1:
			color = Qt::green;
			break;
		case 2:
			color = Qt::black;
			break;
		case 3:
			color = Qt::blue;
			break;
		case 4:
			color = Qt::lightGray;
			break;
		case 5:
			color = Qt::yellow;
			break;
		case 6:
			color = Qt::cyan;
			break;
		case 7:
			color = Qt::magenta;
			break;
		case 8:
			color = Qt::darkGreen;
			break;
		case 9:
			color = Qt::darkBlue;
			break;
		default:
			break;
		}

		switch (forma)
		{
		case 0: // dreptunghi
			p.drawRect(x, start_y, 20, inaltime);
			break;
		case 1: // elipsa
			p.drawEllipse(x, start_y, 20, inaltime);
			break;
		case 2: // dreptunghi colorat
			p.fillRect(x, start_y, 20, inaltime, color);
			break;
		default: // dreptunghi colorat
			p.fillRect(x, start_y, 20, inaltime, color);
			break;
		}
	}
}

WashRDOnlyGUI::~WashRDOnlyGUI()
{
	cos->service.removeObserver(this);
}