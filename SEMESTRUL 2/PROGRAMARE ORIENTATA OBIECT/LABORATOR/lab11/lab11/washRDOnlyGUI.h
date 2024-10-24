#pragma once
#include "CarGUI.h"
#include "washCRUDGUI.h"
#include "observer.h"
#include <qpainter.h>

class WashRDOnlyGUI : public QWidget, public Observer
{
	// cos RDOnly
	friend class CarGUI;
	friend class WashCRUDGUI;

	// pointer la cosul curent
	WashCRUDGUI* cos;

public:

	// constructorul clasei
	WashRDOnlyGUI(WashCRUDGUI* c);

	// construim interfata
	void build_UI();

	// actualizam (redesenam figurile)
	void update() override;

	// desenam figurile
	void paintEvent(QPaintEvent* ev) override;

	// destructorul clasei
	~WashRDOnlyGUI();
};