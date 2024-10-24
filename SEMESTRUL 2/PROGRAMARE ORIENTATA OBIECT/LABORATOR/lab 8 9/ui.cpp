#include "ui.h"
#include "service.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;


void UI::citireAdaugareMasina() {
    string nr_inmatriculare;
    string producator;
    string model;
    string tip;
    cout << "\nIntroduceti numarul de inmatriculare:\n";
    cin >> nr_inmatriculare;
    cout << "\nIntroduceti producatorul:\n";
    cin >> producator;
    cout << "\nIntroduceti modelul:\n";
    cin >> model;
    cout << "\nIntroduceti tipul:\n";
    cin >> tip;
    try {
        service.adaugaMasinaService(nr_inmatriculare, producator, model, tip);
    }
    catch (MasinaException& e) {
        cout << e.get_msg() << "\n";
    }
}

void UI::citireStergereMasina() {
    string nr_inmatriculare;
    cout << "Introduceti numarul de inmatriculare:\n";
    cin >> nr_inmatriculare;
    try {
        service.stergeMasinaService(nr_inmatriculare);
    }
    catch (MasinaException& e) {
        cout << e.get_msg() << "\n";
    }
}

void UI::run() {
    int optiune = -1;
    while (true) {
        menu();
        cout << "Introduceti optiunea:\n";
        cin >> optiune;
        switch (optiune) {
        case 1:
            citireAdaugareMasina();
            break;
        case 2:
            citireStergereMasina();
            break;
        case 3:
            citireModificareMasina();
            break;
        case 4:
            afisareMasini();
            break;
        case 5:
            citireFiltrareProducator();
            break;
        case 6:
            citireFiltrareTip();
            break;
        case 7:
            sortare();
            break;
        case 8:
            menuManager();
            int cmd2;
            cin >> cmd2;
            switch (cmd2)
            {
                case 1:
                    createManager();
                    break;
                case 2:
                    clearAllManager();
                    break;
                case 3:
                    citireAdaugaManager();
                    break;
                case 4:
                    generateRandomManagerUI();
                    break;
                case 5:
					break;
                case 6:
                    printAllManager();
                    break;
                case 0:
                    break;
                default:
                    cout << "\nComanda invalida!";
                    break;
            }
            break;
        case 0:
            return;
        default:
            cout << "Optiune invalida!\n";
            break;
        }
    }
}

void UI::menu() {
    cout << "1. Adaugare masina\n";
    cout << "2. Stergere masina\n";
    cout << "3. Modificare masina\n";
    cout << "4. Afisare masini\n";
    cout << "5. Filtrare masini dupa producator\n";
    cout << "6. Filtrare masini dupa tip\n";
    cout << "7. Sortare\n";
    cout << "8. Lista masini de spalat\n";
    cout << "0. Exit\n";
}

void UI::afisareMasini() {
    vector<Masina> masini = service.getAllMasiniService();
    for(auto& masina: masini) {
		cout << "Numar de inmatriculare: " << masina.get_nr_inmatriculare() << " Producator: " << masina.get_producator() << " Model: " << masina.get_model() << " Tip: " << masina.get_tip() << "\n";
    }
}

void UI::citireModificareMasina() {
    string nr_inmatriculare;
    string producator;
    string model;
    string tip;
    cout << "\nIntroduceti numarul de inmatriculare:\n";
    cin >> nr_inmatriculare;
    cout << "\nIntroduceti producatorul:\n";
    cin >> producator;
    cout << "\nIntroduceti modelul:\n";
    cin >> model;
    cout << "\nIntroduceti tipul:\n";
    cin >> tip;
    try {
        service.modificaMasinaService(nr_inmatriculare, producator, model, tip);
    }
    catch (MasinaException& e) {
        cout << e.get_msg() << "\n";
    }
}

void UI::citireFiltrareProducator() {
    string producator;
    cout << "Introduceti producatorul:\n";
    cin >> producator;
    vector<Masina> masini = service.filterMasiniProducer(producator);
    if (masini.size() == 0) {
        cout << "Nu exista masini cu acest producator!\n";
        return;
    }
    else
        for (auto& masina : masini) {
            cout << "Numar de inmatriculare: " << masina.get_nr_inmatriculare() << " Producator: " << masina.get_producator() << " Model: " << masina.get_model() << " Tip: " << masina.get_tip() << "\n";
        }
}

void UI::citireFiltrareTip() {
    string tip;
    cout << "Introduceti tipul:\n";
    cin >> tip;
    vector<Masina> masini = service.filterMasiniType(tip);
    if (masini.size() == 0) {
        cout << "Nu exista masini de acest tip!\n";
        return;
    }
    else
        for (auto& masina : masini) {
            cout << "Numar de inmatriculare: " << masina.get_nr_inmatriculare() << " Producator: " << masina.get_producator() << " Model: " << masina.get_model() << " Tip: " << masina.get_tip() << "\n";
        }
}


void UI::sortare() {
    cout << "SORTARE" << endl;
    cout << "1. Numar de inmatriculare \n 2. Tip \n 3. Producator si model" << endl;
    string optiune;
    cout << ">>> ";
    cin >> optiune;
    if (optiune == "1") {
        vector<Masina> lista_sortata = service.sortMasini(sortNrInmatriculare);
        for(auto& masina : lista_sortata) {
			cout << "Numar de inmatriculare: " << masina.get_nr_inmatriculare() << " Producator: " << masina.get_producator() << " Model: " << masina.get_model() << " Tip: " << masina.get_tip() << "\n";
        }
    }
    else if (optiune == "2") {
        vector<Masina> lista_sortata = service.sortMasini(sortTip);
        for (auto& masina : lista_sortata) {
            cout << "Numar de inmatriculare: " << masina.get_nr_inmatriculare() << " Producator: " << masina.get_producator() << " Model: " << masina.get_model() << " Tip: " << masina.get_tip() << "\n";
        }
    }
    else if (optiune == "3") {
        vector<Masina> lista_sortata = service.sortMasini(sortProducatorModel);
        for (auto& masina : lista_sortata) {
			cout << "Numar de inmatriculare: " << masina.get_nr_inmatriculare() << " Producator: " << masina.get_producator() << " Model: " << masina.get_model() << " Tip: " << masina.get_tip() << "\n";
		}
    }
}

void UI::menuManager()
{
    cout << "1. Creaza lista noua\n";
    cout << "2. Goleste lista\n";
    cout << "3. Adauga masina\n";
    cout << "4. Genereaza random\n";
    cout << "5. Salveaza in fisier\n";
    cout << "6. Afiseaza lista\n";
    cout << "0. Inapoi\n";
}

void UI::citireAdaugaManager()
{
    string nr_inmatriculare;
    cout << "Introduceti numarul de inmatriculare:\n";
    cin >> nr_inmatriculare;
    try {
		service.adaugaManagerService(nr_inmatriculare);
	}
    catch (MasinaException& e) {
		cout << e.get_msg() << "\n";
	}
    cout << "\n" << service.getAllManager().size() << "\n";
}

void UI::clearAllManager()
{
	service.clearAllManager();
    cout << "\n" << service.getAllManager().size() << "\n";
}

void UI::createManager()
{
    try {
		service.createManager();
	}
    catch (MasinaException& e) {
		cout << e.get_msg() << "\n";
	}
    cout<< "\n" << service.getAllManager().size() << "\n";
}

void UI::generateRandomManagerUI()
{
    int n;
	cout << "Introduceti numarul de masini:\n";
	cin >> n;
	service.generateRandom(n);
	cout << "\n" << service.getAllManager().size() << "\n"; 
}

void UI::printAllManager() {
    vector<Masina>& manager = service.getAllManager();
    for (auto& masina : manager) {
		cout << "Numar de inmatriculare: " << masina.get_nr_inmatriculare() << " Producator: " << masina.get_producator() << " Model: " << masina.get_model() << " Tip: " << masina.get_tip() << "\n";
	}
    cout << "\n" << manager.size() << "\n";
}

