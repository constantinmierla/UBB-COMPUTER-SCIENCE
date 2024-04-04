//
// Created by Costi on 29-Mar-24.
//

#ifndef LAB_6_STATIC_UI_H
#define LAB_6_STATIC_UI_H
#include "service.h"
#include "domain.h"

class UI{
    MasinaService &ctr;  // Referință către serviciul Masina

    // Funcție privată pentru adăugarea unei mașini
    void adaugaUI();

    // Funcție privată pentru ștergerea unei mașini
    void stergeUI();

    // Funcție privată pentru modificarea unei mașini
    void modificaUI();

    // Funcție statică privată pentru afișarea unei liste de mașini
    static void afiseazaUI(const vector<Masina> &masini);

public:
    // Constructor care primește o referință către un MasinaService pentru a inițializa UI
    UI(MasinaService &c) : ctr{c} {

    }

    // Constructor de copiere eliminat pentru a preveni copierea neautorizată a UI
    UI(const UI &ot) = delete;

    // Funcție pentru a rula interfața utilizatorului
    void run();
};

#endif //LAB_6_STATIC_UI_H
