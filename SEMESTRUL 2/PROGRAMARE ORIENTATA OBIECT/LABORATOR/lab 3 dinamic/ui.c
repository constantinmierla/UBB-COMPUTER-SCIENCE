#include <stdio.h>
//#include "domain.h"
//#include "repository.h"
#include "service.h"
#include "ui.h"
#include "string.h"
//#include "tests.h"
void updateOfe(BigList* list)
{
    char tip[30], destinatie[30], data_plecarii[30];
    printf("Introduceti Id-ul:\n");
    int id;
    scanf("%d",&id);
    printf("Introduceti tip(mare sau MUNTE) : \n");
    scanf("%s", tip);
    printf("Introduceti destinatie : \n");
    scanf("%s", destinatie);
    printf("Introduceti data plecarii : \n");
    scanf("%s", data_plecarii);
    printf("Introduceti noul pret:\n");
    int pret;
    scanf("%d",&pret);
    if (!updateEnt(list,tip,destinatie,data_plecarii,pret,id))
        printf("Modificarea a avut loc cu succes!\n");
    else
        printf("Oferta cu id-ul dat nu exista!\n");

}
void readOfe(BigList* list)
{
    printf("Adauga oferta : tip, destinatie, data plecarii, pret, id\n");
    char tip[30], destinatie[30], data_plecarii[30];
    int pret;
    printf("Introduceti id:\n");
    int id=-1;
    scanf("%d",&id);
    if (checkId(list, id) == 0)
    {
        printf("Introduceti tip(mare sau MUNTE) : \n");
        scanf("%s", tip);
        printf("Introduceti destinatie : \n");
        scanf("%s", destinatie);
        printf("Introduceti data plecarii : \n");
        scanf("%s", data_plecarii);
        printf("Introduceti pret : \n");
        scanf("%d", &pret);
        if(addEnt(list, tip,destinatie,data_plecarii,pret,id))
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
        printf("Id: %d; Tip: %s; Destinatie: %s; Data_plecarii: %s; Pret: %d\n",m->id,m->tip,m->destinatie,m->data_plecarii,m->pret);
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
    printf("alegeti sortarea : destinatie, pret: ");
    char crit[20],t[20];
    scanf("%s", t);
    if (strcmp(t, "pret")==0)
    {
        printf("crescator sau descrescator : ");
        scanf("%s",crit);
        if(strcmp(crit,"crescator") == 0) {
            BigList* filt = sortPret(list);
            printOfferte(filt);
        }
        else
        {
            BigList* filt = sortPretD(list);
            printOfferte(filt);
        }
    }
    else if (strcmp(t, "destinatie") == 0)
    {
        printf("crescator sau descrescator : ");
        scanf("%s",crit);
        if(strcmp(crit,"crescator") == 0) {
            BigList* filt = sortDestinatie(list);
            printOfferte(filt);
        }
        else
        {
            BigList* filt = sortDestinatieD(list);
            printOfferte(filt);
        }
    }
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
        printf("Id: %d; Tip: %s; Destinatie: %s; Data_plecarii: %s; Pret: %d\n",m->id,m->tip,m->destinatie,m->data_plecarii,m->pret);
    }

    destroyOfferte(f);

}

void filtrareTip(BigList* list)
{
    printf("Dati o litera(M pentru MUNTE, m pentru mare:");
    char litera[2];
    scanf("%s",litera);
    Offerte* f = filterTip(list,litera[0]);
    for(int i=0;i<f->dimensiune;i++)
    {
        Oferta* m = get(f,i);
        printf("Id: %d; Tip: %s; Destinatie: %s; Data_plecarii: %s; Pret: %d\n",m->id,m->tip,m->destinatie,m->data_plecarii,m->pret);
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