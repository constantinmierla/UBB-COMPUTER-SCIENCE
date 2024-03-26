#include "../Service/service.h"

#ifndef LAB2_UI_H
#define LAB2_UI_H

typedef struct {
    Service *service;
} Console;

void showMenu();
void run(Console console);
void uiAdaugaProdus(Service *service);
void uiActualizareProdus(Service *service);
void uiStergereProdus(Service *service);
void uiVizualizareProduse(Service *service);
void uiListaProduseFiltrate(Service *service);
void undoUI(Service *service);
#endif //LAB2_UI_H
