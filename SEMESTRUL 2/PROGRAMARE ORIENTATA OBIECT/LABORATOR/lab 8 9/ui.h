#pragma once
#include <utility>
#include <iostream>
#include "service.h"
using namespace std;

class UI {
private:
    ServiceMasina& service;
public:
    explicit UI(ServiceMasina& service) : service{ service } {

    }

    /*
     * functie de citire si adaugare a unei masini
     */
    void citireAdaugareMasina();

    /*
     * functie de citire al unui nr de inmatriculare si stergere a unei masini cu acel nr de inmatriculare
     */
    void citireStergereMasina();

    /*
     * functie de citire si modificare a unei masini avand un nr de inmatriculare dat
     */
    void citireModificareMasina();

    /*
     * functie de afisare a tuturor masinilor
     */
    void afisareMasini();

    /*
     * functie de afisare a meniului
     */
    static void menu();

    /*
     * functie de start a programului
     */
    void run();

    /*
     * functie de citire pentru filtrarea dupa producator
     */
    void citireFiltrareProducator();

    /*
     * functie de citire pentru filtrarea dupa tip
     */
    void citireFiltrareTip();

    /*
     * functie de citire pentru sortare
     */
    void sortare();

    /*
    * functie care afiseaza meniul manager
    */
    void menuManager();

    /*
     * functie de citire si adaugare a unei masini in lista manager
     */
    void citireAdaugaManager();

    /*
    functie de afisare a tuturor masinilor din manager
    */
    void printAllManager();

    /*
    * functie de stergere a tuturor masinilor din manager
    */
    void clearAllManager();

    /*
     * functie de creare a unui manager de masini ce urmeaza a fi spalate 
     */
    void createManager();

    /*
     * functie UI ce alege masini random din lista de masini si le adauga in manager 
     */
    void generateRandomManagerUI();
};

