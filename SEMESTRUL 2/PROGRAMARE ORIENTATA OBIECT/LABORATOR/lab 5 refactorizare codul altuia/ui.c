#include <stdio.h>
//#include "domain.h"
//#include "repository.h"
#include "service.h"
#include "ui.h"
#include "string.h"
//#include "tests.h"
void updateOfe(BigList* list)
{
    char tip[30], model[30], producator[30];
    printf("Introduceti Id-ul:\n");
    int id;
    scanf("%d",&id);
    printf("Introduceti tip : \n");
    scanf("%s", tip);
    printf("Introduceti model : \n");
    scanf("%s", model);
    printf("Introduceti producator : \n");
    scanf("%s", producator);
    printf("Introduceti noul pret:\n");
    int pret;
    scanf("%d",&pret);
    int stoc;
    printf("Introduceti noul stoc:\n");
    scanf("%d",&stoc);
    if (!updateEnt(list, tip, model, producator, pret, id, stoc))
        printf("Modificarea a avut loc cu succes!\n");
    else
        printf("Oferta cu id-ul dat nu exista!\n");

}
void readOfe(BigList* list)
{
    printf("Adauga oferta : tip, model, producatorul, pret, id, stoc\n");
    char tip[30], destinatie[30], data_plecarii[30];
    int pret;
    printf("Introduceti id:\n");
    int id=-1;
    scanf("%d",&id);
    if (checkId(list, id) == 0)
    {
        printf("Introduceti tip : \n");
        scanf("%s", tip);
        printf("Introduceti model : \n");
        scanf("%s", destinatie);
        printf("Introduceti producatorul : \n");
        scanf("%s", data_plecarii);
        printf("Introduceti pret : \n");
        scanf("%d", &pret);
        printf("Introduceti stoc : \n");
        int stoc;
        scanf("%d", &stoc);
        if(addEnt(list, tip,destinatie,data_plecarii,pret,id, stoc))
            printf("Oferta a fost adaugata cu succes!\n");
        else
            printf("Oferta invalida!\n");
    }

}

void printOfferte(BigList* list)
{
    for(int i = 0; i< list->lista->dimensiune;i++)
    {
        Oferta* m = get(list->lista,i);
        printf("Id: %d; Tip: %s; model: %s; producatorul: %s; Pret: %d; Stoc: %d\n",m->id,m->tip,m->model,m->producer,m->pret, m->stoc);
    }
}

void deleteOfe(BigList* list)
{
    printf("Id-ul ofertei pe care doriti sa il stergeti:\n");
    int id;
    scanf("%d",&id);
    if(!deleteEnt(list,id))
        printf("Aceasta oferta nu exista!\n");
    else
        printf("Oferta stearsa cu succes!\n");
}
void destroy(BigList *list)
{
    destroyAll(list);
}

void sortare(BigList *list)
{
    char nume[20];
    printf("Alegeti tipul de sortare: bubble, selection\n");
    scanf("%s",nume);
    if(strcmp(nume,"selection") == 0) {
        printf("alegeti sortarea : stoc, pret: ");
        char crit[20], t[20];
        scanf("%s", t);
        if (strcmp(t, "pret") == 0) {
            printf("crescator sau descrescator : ");
            scanf("%s", crit);
            if (strcmp(crit, "crescator") == 0) {
                BigList *filt = sortPret(list);
                printOfferte(filt);
            } else {
                BigList *filt = sortPretD(list);
                printOfferte(filt);
            }
        } else if (strcmp(t, "stoc") == 0) {
            printf("crescator sau descrescator : ");
            scanf("%s", crit);
            if (strcmp(crit, "crescator") == 0) {
                BigList *filt = sortStoc(list);
                printOfferte(filt);
            } else {
                BigList *filt = sortStocD(list);
                printOfferte(filt);
            }
        }
    }
    else if(strcmp(nume,"bubble") == 0)
    {
        printf("alegeti sortarea : stoc, pret: ");
        char crit[20], t[20];
        scanf("%s", t);
        if (strcmp(t, "pret") == 0) {
            printf("crescator sau descrescator : ");
            scanf("%s", crit);
            if (strcmp(crit, "crescator") == 0) {
                BigList *filt = sortPretb(list);
                printOfferte(filt);
            } else {
                BigList *filt = sortPretDb(list);
                printOfferte(filt);
            }
        } else if (strcmp(t, "stoc") == 0) {
            printf("crescator sau descrescator : ");
            scanf("%s", crit);
            if (strcmp(crit, "crescator") == 0) {
                BigList *filt = sortStocb(list);
                printOfferte(filt);
            } else {
                BigList *filt = sortStocDb(list);
                printOfferte(filt);
            }
        }
    }
    else
        printf("Sortare invalida!\n");
}

void filtrarePret(BigList* list)
{
    printf("Dati o valoare intrega, pozitiva, nenula:\n");
    int val;
    scanf("%d",&val);
    Offerte* f = filterPret(list,val);
    for(int i=0;i<f->dimensiune;i++)
    {
        Oferta* m = get(f,i);
        printf("Id: %d; Tip: %s; model: %s; producatorul: %s; Pret: %d; Stoc: %d\n",m->id,m->tip,m->model,m->producer,m->pret, m->stoc);
    }

    destroyOfferte(f);

}

void filtrareTip(BigList* list)
{
    printf("Dati o litera: ");
    char litera[2];
    scanf("%s",litera);
    Offerte* f = filterTip(list,litera[0]);
    for(int i=0;i<f->dimensiune;i++)
    {
        Oferta* m = get(f,i);
        printf("Id: %d; Tip: %s; model: %s; producatorul: %s; Pret: %d; Stoc: %d\n",m->id,m->tip,m->model,m->producer,m->pret, m->stoc);
    }

    destroyOfferte(f);
}

void run()
{
    BigList list = createBigList();

    while(1)
    {
        int cmd;
        printf("0. Exit; 1. Adaugare; 2. Modificare; 3.Stergere; 4.Afisare Oferte;\n"
               "5. Sortare; 6. Filtrare Pret; 7. Filtrare tip\n");
        scanf("%d",&cmd);
        if(cmd == 1)
            readOfe(&list);
        else if(cmd == 2)
            updateOfe(&list);
        else if(cmd == 3)
            deleteOfe(&list);
        else if(cmd == 4)
            printOfferte(&list);
        else if(cmd == 5)
            sortare(&list);
        else if(cmd == 6)
            filtrarePret(&list);
        else if(cmd == 7)
            filtrareTip(&list);
        else if(cmd==0)
        {
            destroy(&list);
            break;
        }
    }

}