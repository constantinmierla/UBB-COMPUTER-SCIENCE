//
// Created by Costi on 29-Mar-24.
//

#ifndef LAB_6_STATIC_UI_H
#define LAB_6_STATIC_UI_H
#include "service.h"
#include "domain.h"

class UI{
    MasinaService &ctr;

    void adaugaUI();

    void stergeUI();

    void modificaUI();

    static void afiseazaUI(const vector<Masina> &masini);

public:
    UI(MasinaService &c) : ctr{c} {

    }
    UI(const UI &ot) = delete;

    void run();
};
#endif //LAB_6_STATIC_UI_H
