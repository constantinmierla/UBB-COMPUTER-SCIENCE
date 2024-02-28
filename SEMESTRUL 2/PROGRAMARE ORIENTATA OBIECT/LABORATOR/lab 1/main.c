#include <stdio.h>

//9. Citeste un sir de numere naturale nenule terminat cu 0 si determina
//    numarul cifrelor 0 in care se termina numarul produs al numerelor citite.
int produs_numere(int produs)
{
    /*
     Functia produs_numere calculeaza produsul a numerelor introduse
     input : produs
     type input : int
     output: produs
     type output: produs
     */
    int numar;
    printf("%s","introduceti numerele : \n");
    do {
        scanf("%d", &numar);
        if(numar != 0)
            produs = produs * numar;
    }while(numar != 0);

    return produs;
}

int cifre_zero(int rezultat)
{
    /*
     * Functie cifre_zero calculeaza numarul de zero uri al unui numar
     * input: rezultat
     * type input : int
     * output: count
     * type output: int
     */
    int count = 0;
    if (rezultat == 0)
        return 1;
    else
    {
        while(rezultat > 0)
        {
            if(rezultat%10 == 0)
                count++;

            rezultat/=10;
        }
    }
    return count;
}
int main()
{
    int ok = 1;
    while(ok == 1)
    {
        int produs = 1, rezultat, cifre;

        rezultat = produs_numere(produs);

        cifre = cifre_zero(rezultat);

        printf("%d", cifre);
        printf("%s","\nRulati din nou programul: Da (1), Nu (0) : \n");
        scanf("%d", &ok);

    }
    printf("%s", "iesire din aplicatie...");
    return 0;
}
