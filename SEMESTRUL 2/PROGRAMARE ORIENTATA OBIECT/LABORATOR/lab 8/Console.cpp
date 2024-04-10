#include "Console.h"

void ConsoleUI::tipareste(const DynamicArray<Masina>& masini) {
    if (masini.size() == 0) {
        cout << "Nu exista masini!\n";
    }
    else {
        for (auto const& masina : masini) {
            cout << masina;
        }
    }
}

void ConsoleUI::adaugaUI() const{
    string nrInmatriculare, producator, model, tip;

    cout << "Numar inmatriculare: ";
    cin >> nrInmatriculare;

    cout << "Producator: ";
    cin >> producator;

    cout << "Model:";
    cin >> model;

    cout << "Tip: ";
    cin >> tip;

    service.addMasina(nrInmatriculare, producator, model, tip);
}

void ConsoleUI::stergeUI() const {
    string nrInmatriculare;

    cout << "Numar inmatriculare: ";
    cin >> nrInmatriculare;

    service.eraseMasina(nrInmatriculare);
}

void ConsoleUI::modificaUI() const {
    string nrInmatriculare, producatorNou, modelNou, tipNou;

    cout << "Numar inmatriculare: ";
    cin >> nrInmatriculare;

    cout << "Producator nou: ";
    cin >> producatorNou;

    cout << "Model nou: ";
    cin >> modelNou;

    cout << "Tip nou: ";
    cin >> tipNou;

    service.modifyMasina(nrInmatriculare, producatorNou, modelNou, tipNou);
}

void ConsoleUI::afisareUI() const {
    tipareste(service.getAll());
}

void ConsoleUI::cautaUI() const {
    string nrInmatriculare;

    cout << "Numar inmatriculare: ";
    cin >> nrInmatriculare;

    Masina masina = service.findMasina(nrInmatriculare);

    cout << masina;
}

void ConsoleUI::filtrareUI() const {
    string filterString;
    int tip{ 0 };
    cout << "1 - producator\n2 - tip\n";
    cin >> tip;

    if (tip == 1) {
        cout << "Producator: ";
        cin >> filterString;

        tipareste(service.filterByProducator(filterString));
    }
    else if (tip == 2) {
        cout << "Tip: ";
        cin >> filterString;

        tipareste(service.filterByTip(filterString));
    }
    else {
        cout << "Mod invalid!";
    }
}

void ConsoleUI::sortareUI() const {
    int tip{ 0 };
    cout << "1 - numar inmatriculare\n2 - tip\n3 - producator + model\n";
    cin >> tip;

    switch (tip)
    {
        case 1:
            tipareste(service.sortByNtInmatriculare());
            break;
        case 2:
            tipareste(service.sortByTip());
            break;
        case 3:
            tipareste(service.sortByProducatorAndModel());
            break;
        default:
            cout << "Mod invalid!\n";
            break;
    }
}

void ConsoleUI::run() const {
    while (true) {
        cout << "0 - iesire\n1 - adauga\n2 - sterge\n3 - modifica\n4 - afisare\n5 - cauta masina\n6 - filtrare\n7 - sortare\n";
        int cmd;
        cin >> cmd;

        try {
            switch (cmd) {
                case 1:
                    adaugaUI();
                    break;
                case 2:
                    stergeUI();
                    break;
                case 3:
                    modificaUI();
                    break;
                case 4:
                    afisareUI();
                    break;
                case 5:
                    cautaUI();
                    break;
                case 6:
                    filtrareUI();
                    break;
                case 7:
                    sortareUI();
                    break;
                case 0:
                    return;
                default:
                    cout << "Comanda invalida!\n";
            }
        }
        catch (const CarRepoException& re) {
            cout << re << '\n';
        }
        catch (const ValidateException& ve) {
            cout << ve << '\n';
        }
    }
}