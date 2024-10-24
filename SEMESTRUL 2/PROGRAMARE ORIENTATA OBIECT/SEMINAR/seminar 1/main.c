typedef struct{
    int id;
    char nume[50];
    char artist[50];
    double durata;
}Melodie;

Melodie creeaza_melodie(int id, char nume[], char artist[], double durata)
{
    /*
     * Creeaza o melodie
     * Returneaza o melodie cu datele date
     */

}

int main()
{

}

/*#include <stdio.h>

void afisareNote(int* note)
{
    for(int i = 0; i < 5; i++)
    {
        printf("%d ", note[i]);;
    }
}

float get_average(int note[])
{
    int sum = 0;
    for(int i = 0 ; i < 5; i++)
    {
        sum = sum+note[i];
    }
    return sum/5;
}
int main()
{
    int note[5];
    for(int i = 0; i < 5; i++)
    {
        scanf("%d", &note[i]);
    }
    afisareNote(note);
    printf("Average: %f", get_average(note));
}
*/