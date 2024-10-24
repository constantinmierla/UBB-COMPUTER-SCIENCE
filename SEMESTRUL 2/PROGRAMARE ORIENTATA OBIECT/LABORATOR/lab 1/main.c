#include <stdio.h>

//9. Citeste un sir de numere naturale nenule terminat cu 0 si determina
//    numarul cifrelor 0 in care se termina numarul produs al numerelor citite.
//3. Determina toate reprezentarile posibile a unui numar natural ca suma
//   de numere naturale consecutive.

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
int suma(int start, int nr)
{
    /*
     * Functia calculeaza suma de numere consecutive incepand cu start
     * input : start, nr
     * type input : int
     * output : 1 (daca exista aceasta suma) sau 0 in caz contrar
     */
    int s = 0;
    while (s < nr)
    {
        s = s + start;
        start++;
    }
    if (s == nr)
        return 1;
    else
        return 0;
}
void afis(int start, int nr)
{
    /*
     * functia afiseaza suma de numere consecutive
     * input : start, nr
     * type input : int
     * output : sirul de numere consecutive
     */
    int s = 0;
    while (s < nr)
    {
        printf("%d ", start);
        s = s + start;
        start++;
    }
    printf("%s", "\n");
}
void solve(int n)
{
    /*
     * functia calculeaza suma de numere consecutive
     * input : n
     * type input : int
     */
    for (int start = 1; start <= n/2; start++)
    {
        if (suma(start, n) == 1)
            afis(start, n);
    }
}
int main()
{
    int ok = 1, option, nr;
    printf("%s","Alegeti cerinta : 1(pb 9) sau 2(pb 3) : \n");
    scanf("%d", &option);
    while(ok == 1)
    {
        int produs = 1, rezultat, cifre;

        if (option == 1) {
            rezultat = produs_numere(produs);

            cifre = cifre_zero(rezultat);

            printf("%d", cifre);
        }
        else if (option == 2)
        {
            printf("%s","Introduceti numarul : ");
            scanf("%d", &nr);
            solve(nr);
        }

        printf("%s","\nRulati din nou programul: Da (1), Nu (0) : \n");

        scanf("%d", &ok);

        if (ok == 1)
        {
            printf("%s", "\nAlegeti optiunea: \n");
            scanf("%d", &option);
        }
    }
    printf("%s", "iesire din aplicatie...");
    return 0;
}
