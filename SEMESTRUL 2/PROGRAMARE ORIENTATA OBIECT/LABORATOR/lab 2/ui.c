//
// Created by Costi on 12-Mar-24.
//
#include <stdio.h>
#include "ui.h"
void testAll()
{
    printf("Rulare teste...\n");

    printf("\nRulare reusita!\n");
}
void uiAdd(List *v)
{
    printf("Adauga oferta : tip, destinatie, data plecarii, pret\n");
    char tip[30], destinatie[30], data_plecarii[30];
    float pret;
    printf("Introduceti tip : \n");
    scanf("%s", tip);
    printf("Introduceti destinatie : \n");
    scanf("%s", destinatie);
    printf("Introduceti data plecarii : \n");
    scanf("%s", data_plecarii);
    printf("Introduceti pret : \n");
    scanf("%f", &pret);
    int ok = adaugaOferta(v,tip,destinatie,data_plecarii,pret);
    if (ok)
        printf("Oferta adaugata cu succes! \n");
    else
        printf("Oferta nu este valida! \n");
}
void uiModify(List *v)
{
    printf("add");
}
void uiDelete(List *v)
{
    printf("add");
}
void uiSort(List *v)
{
    printf("add");
}
void uiFilter(List *v)
{
    printf("add");
}
void menu()
{
    printf("1. Adaugarea de noi oferte.\n");
    printf("2. Actualizare oferte.\n");
    printf("3. Stergere oferta.\n");
    printf("4. Vizualizare oferete ordonat dupa pret, destinatie (crescator/descrescator).\n");
    printf("5. Vizualizare oferta filtrate dupa un criteriu (destinatie, tip, pret).\n");
    printf("6. Iesire aplicatie\n");

}
void run()
{
    List v = createEmpty();
    int option, ok;
    ok = 1;
    printf("Bine ati venit in aplicatie!\n");
    while(ok)
    {
        menu();
        printf("Alegeti optiunea: \n");
        scanf("%d", &option);
        switch(option){
            case 1:
                uiAdd(&v);
                break;
            case 2:
                uiModify(&v);
                break;
            case 3:
                uiDelete(&v);
                break;
            case 4:
                uiSort(&v);
                break;
            case 5:
                uiFilter(&v);
                break;
            case 6:
                printf("Iesire aplicatie...");
                ok = 0;
                break;
            default:
                printf("Comanda gresita!\n");
                break;
        }
    }
}
