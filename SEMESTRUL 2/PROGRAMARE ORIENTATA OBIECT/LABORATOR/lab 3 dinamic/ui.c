//
// Created by Costi on 12-Mar-24.
//
#include <stdio.h>
#include "ui.h"
#include "tests.h"
#include <stdlib.h>

//Ruleaza toate testele definite pentru functionalitatile aplicatiei.
void testAll()
{
    printf("Rulare teste...\n");
    test_creeazaOferta();

    test_destroyOferta();

    test_ValideazaOferta();

    test_createEmpty();

    testAddAndGet();

    test_addCantitate();

    test_delete();

    test_size();

    test_adaugaService();

    test_modificaService();

    test_stergeService();

    test_filtru();

    test_sort();

    printf("\nRulare reusita!\n");
}

/*
 * Afiseaza meniul pentru adaugarea unei noi oferte si solicita utilizatorului sa introduca datele.
 * Parametri:
 *   - v: lista de oferte in care se adauga oferta (List*)
 */
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

/*
 * Afiseaza meniul pentru modificarea unei oferte si solicita utilizatorului sa introduca noile date.
 * Parametri:
 *   - v: lista de oferte in care se modifica oferta (List*)
 */
void uiModify(List *v) //de modificat
{
    printf("Modifica oferta : tip, destinatie, data plecarii si introduceti noul pret\n");
    char tip[30], destinatie[30], data_plecarii[30];
    float pret;
    printf("Introduceti tip : \n");
    scanf("%s", tip);
    printf("Introduceti destinatie : \n");
    scanf("%s", destinatie);
    printf("Introduceti data plecarii : \n");
    scanf("%s", data_plecarii);
    printf("Introduceti noul pret : \n");
    scanf("%f", &pret);
    int ok = modificaOferta(v,tip,destinatie,data_plecarii,pret);
    if (ok)
        printf("Oferta modificata cu succes! \n");
    else
        printf("Oferta nu este valida! \n");
}

/*
 * Afiseaza meniul pentru stergerea unei oferte si solicita utilizatorului sa introduca datele ofertei de sters.
 * Parametri:
 *   - v: lista de oferte din care se sterge oferta (List*)
 */
void uiDelete(List *v)
{
    printf("Sterge oferta : tip, destinatie, data plecarii\n");
    char tip[30], destinatie[30], data_plecarii[30];
    printf("Introduceti tip : \n");
    scanf("%s", tip);
    printf("Introduceti destinatie : \n");
    scanf("%s", destinatie);
    printf("Introduceti data plecarii : \n");
    scanf("%s", data_plecarii);
    int ok = stergeOferta(v,tip,destinatie,data_plecarii);
    if (ok)
        printf("Oferta stearsa cu succes! \n");
    else
        printf("Oferta nu este valida! \n");
}

/*
 * Afiseaza meniul pentru sortarea ofertelor.
 * Parametri:
 *   - v: lista de oferte care urmeaza sa fie sortata (List*)
 */
void uiSort(List *v)
{
    printf("alegeti sortarea : destinatie, pret: ");
    char crit[20],t[20];
    scanf("%s", t);
    if (strcmp(t, "pret")==0)
    {
        printf("crescator sau descrescator : ");
        scanf("%s",crit);
        if(strcmp(crit,"crescator") == 0) {
            List filt = sortOfertaPretCrescator(v);
            getAll(&filt);
        }
        else
        {
            List filt = sortOfertaPretDescrescator(v);
            getAll(&filt);
        }
    }
    else if (strcmp(t, "destinatie") == 0)
    {
        printf("crescator sau descrescator : ");
        scanf("%s",crit);
        if(strcmp(crit,"crescator") == 0) {
            List filt = sortOfertaDestinatieCrescator(v);
            getAll(&filt);
        }
        else
        {
            List filt = sortOfertaDestinatieDescrescator(v);
            getAll(&filt);
        }
    }
}

/*
 * Afiseaza meniul pentru filtrarea ofertelor si solicita utilizatorului sa introduca criteriile de filtrare.
 * Parametri:
 *   - v: lista de oferte care urmeaza sa fie filtrata (List*)
 */
void uiFilter(List *v)
{
    printf("alegeti filtrarea : destinatie, tip, pret: ");
    char t[13], crit[20];
    float pret;
    scanf("%s", t);
    if (strcmp(t, "destinatie")==0)
    {
        printf("introduceti destinatia : ");
        scanf("%s",crit);
        List filt = filtruOfertaDestinatie(v,crit);
        getAll(&filt);
    }
    else if (strcmp(t, "tip") == 0)
    {
        printf("introduceti tipul : ");
        scanf("%s",crit);
        List filt = filtruOfertaTip(v,crit);
        getAll(&filt);
    }
    else if (strcmp(t, "pret") == 0)
    {
        printf("introduceti pretul : ");
        scanf("%f",&pret);
        List filt = filtruOfertaPret(v,pret);
        getAll(&filt);
    }
    else
        printf("Nu exista aceasta filtrare!");
}

/*
 * Afiseaza toate ofertele din lista.
 * Parametri:
 *   - v: lista de oferte care urmeaza sa fie afisata (List*)
 */
void getAll(List *v)
{
    for (int i = 0; i < size(v); i++)
    {
        oferta o = get(v,i);
        printf("Tip: %s | Destinatie: %s | Data plecarii: %s | Pret: %f\n",o.tip,o.destinatie,o.data_plecarii,o.pret);
    }
    printf("\n");
}

/*
 * Afiseaza meniul principal al aplicatiei.
 */
void menu()
{
    printf("1. Adaugarea de noi oferte.\n");
    printf("2. Actualizare oferte.\n");
    printf("3. Stergere oferta.\n");
    printf("4. Vizualizare oferete ordonat dupa pret, destinatie (crescator/descrescator).\n");
    printf("5. Vizualizare oferta filtrate dupa un criteriu (destinatie, tip, pret).\n");
    printf("6. Iesire aplicatie\n");
    printf("7. Afisare elemente\n");
}

/*
 * Porneste executia aplicatiei.
 */
void run()
{
    List v = createEmpty();
    int option, ok;
    ok = 1;
    printf("\nBine ati venit in aplicatie!\n");
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
                destroy(&v);
                ok = 0;
                break;
            case 7:
                getAll(&v);
                break;
            default:
                printf("Comanda gresita!\n");
                break;
        }
    }
}
