//
// Created by Costi on 29-Mar-24.
//

#include "ui.h"
#include "domain.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::ws;

void UI::afiseazaUI(const vector<Masina> &masini) {
    if (masini.empty()) {
        cout << "Nu exista masini in lista!\n";
        return;
    }
    for (const auto &m : masini) {
        cout << "NrInmatriculare: " << m.getNR() << " | Producator: " << m.getProducator() << " | Model: " << m.getModel() << " | Tip:" << m.getTip() << "\n";
    }
    cout <<'\n';
}

void UI::adaugaUI() {
    string producator, model, tip;
    int nr;
    cout << "Introduceti numarul de inmatriculare: ";
    cin >> nr;
    cout << "Introduceti producatorul: ";
    cin >> producator;
    cout << "Introduceti modelul: ";
    cin >> model;
    cout << "Introduceti tipul: ";
    cin >> tip;
    if (ctr.addMasinaService(nr, producator, model, tip))
        cout << "Masina adaugata cu succes!\n";
    else
        cout << "Masina nu a putut fi adaugata!\n";
}

void UI::stergeUI() {
    int nr;
    cout << "Introduceti numarul de inmatriculare al masinii pe care doriti sa o stergeti: ";
    cin >> nr;
    if (ctr.delMasinaService(nr))
        cout << "Masina stearsa cu succes!\n";
    else
        cout << "Masina nu a putut fi stearsa!\n";
}

void UI::modificaUI() {
    string producator, model, tip;
    int nr;
    cout << "Introduceti numarul de inmatriculare al masinii pe care doriti sa o modificati: ";
    cin >> nr;
    cout << "Introduceti noul producator: ";
    cin >> producator;
    cout << "Introduceti noul model: ";
    cin >> model;
    cout << "Introduceti noul tip: ";
    cin >> tip;
    if (ctr.modifyMasinaService(nr, producator, model, tip))
        cout << "Masina modificata cu succes!\n";
    else
        cout << "Masina nu a putut fi modificata!\n";
}

void UI::run()
{
    while (true)
    {
        cout << "1. Adauga masina\n";
        cout << "2. Sterge masina\n";
        cout << "3. Modifica masina\n";
        cout << "4. Afiseaza masini\n";
        cout << "5. Exit\n";
        cout << "Introduceti optiunea: ";
        int opt;
        cin >> opt;
        if (opt == 1)
            adaugaUI();
        else if (opt == 2)
            stergeUI();
        else if (opt == 3)
            modificaUI();
        else if (opt == 4)
            afiseazaUI(ctr.getAll());
        else if (opt == 5) {
            cout << "Iesire aplicatie...";
            break;
        }
        else
            cout << "Optiune invalida!\n";
    }
}