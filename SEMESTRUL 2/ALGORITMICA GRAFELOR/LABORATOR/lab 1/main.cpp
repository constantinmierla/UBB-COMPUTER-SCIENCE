#include <iostream>
#include <fstream>
using namespace std;
int n, mat[100][100] = {0},viz[100], x, y, i,j, nr_muchii = 0,inc[100][100] = {0}, ok, lista_ad[100][100] = {0}, mat_ind[100][100]={0}, contor,lista_ad2[100][100] = {0}, mat_adiac[100][100] = {0}, lista[100][3] = {0};

void roy_floyd(int n)
{
    int i,j,k;
    for (k = 1; k <= n; k++)
    {
        for (i = 1; i <=n; i++)
        {
            for (j = 1; j <=n; j++)
            {
                if (mat[i][k]!= 0 and mat[k][i]!=0)
                    if (mat[i][j] > mat[i][k] + mat[k][j] || (mat[i][j] == 0 and i!=j))
                        mat[i][j] = mat[i][j]+mat[k][j];
            }
        }
    }
}
void dfs(int x)
{
    int i;
    viz[x] = 1;
    for (i = 1; i <=n; i++)
        if (mat[x][i] and viz[i] == 0)
            dfs(i);
}
int conex()
{
    int i;
    dfs(1);
    for (i = 1; i<=n; i++)
        if (viz[i] == 0)
            return 0;
    return 1;
}
void citire()
{
    ifstream in ("in.txt");
    in >> n;

    //1.1 construiesc din fisier matricea de adiacenta
    while (in >> x and in >> y)
    {
        mat[x][y] = 1;
        mat[y][x] = 1;
    }

    in.close();
}
void afisare_mat_ad()
{
    cout << "matricea de adiacenta este : \n";
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
}
void lista_adiac()
{
    for (i = 1; i<= n; i++)
    {
        contor = 1;
        for (j = 1; j <= n; j++)
        {
            if (mat[i][j])
                lista_ad[i][contor++] = j;
        }
    }
}
void afisare_lista_adiac()
{
    cout <<"\nlista adiacenta este : \n";
    for (i = 1; i <= n; i++)
    {
        cout << i << ": ";
        for (j = 1; j <= n; j++)
        {
            if (lista_ad[i][j])
                cout << lista_ad[i][j] << " ";
        }
        cout << "\n";
    }
}
void mat_incidenta()
{
    int val;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            val = lista_ad[i][j];
            if (val)
            {
                nr_muchii++;
                mat_ind[i][nr_muchii] = 1;
                mat_ind[val][nr_muchii] = 1;
                //daca am muchia 1,2 nu vreau sa trec prin muchia 2,1
                for (int z = 1; z <= n; z++)
                {
                    if (lista_ad[val][z] == i)
                        lista_ad[val][z] = 0;
                }
            }
        }
    }
}
void afisare_mat_incidenta()
{
    cout <<"\nmatricea de incidenta este: \n";
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= nr_muchii; j++)
        {
            cout << mat_ind[i][j] << " ";
        }
        cout << endl;
    }
}
void lista_din_incidenta()
{
    int val1, val2, z;
    for (j = 1; j <= nr_muchii; j++)
    {
        val1 = 0;
        val2 = 0;
        for (i = 1; i <= n; i++)
        {
            if (mat_ind[i][j])
            {
                if (val1 == 0)
                    val1 = i;
                else
                    val2 = i;
            }
        }

        z = 1;
        while(lista_ad2[val1][z])
            z++;
        lista_ad2[val1][z] = val2;
        z = 1;
        while(lista_ad2[val2][z])
            z++;
        lista_ad2[val2][z] = val1;
    }
}
void afisare_lista_din_incidenta()
{
    cout <<"\nlista adiacenta este : \n";
    for (i = 1; i <= n; i++)
    {
        cout << i << ": ";
        for (j = 1; j <= n; j++)
        {
            if (lista_ad2[i][j])
                cout << lista_ad2[i][j] << " ";
        }
        cout << "\n";
    }
}
void matrice_adiac_din_lista()
{
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (lista_ad2[i][j])
            {
                mat_adiac[i][lista_ad2[i][j]] = 1;
            }
        }
    }
}
void afisare_matrice_adiac_din_lista()
{
    cout << "\nMatricea de adiacenta noua: \n";
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            cout << mat_adiac[i][j] << " ";
        }
        cout << "\n";
    }
}
void lista_din_matrice()
{
    contor = 1;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (mat_adiac[i][j])
            {
                lista[contor][1] = i;
                lista[contor][2] = j;
                mat_adiac[j][i] = 0;
                contor++;
            }
        }
    }
    contor--;
}
void afisare_lista()
{
    cout << "\nlista noua: \n";
    for (i = 1; i <= contor; i++)
    {
        for (j = 1; j <= 2; j++)
        {
            cout << lista[i][j] << " ";
        }
        cout << "\n";
    }
}
int main()
{
    citire();

    //1.1 afisez matricea de adiacenta
    afisare_mat_ad();

    //1.2 din matricea de adiacenta afisez lista adiacenta
    lista_adiac();
    afisare_lista_adiac();

    //1.3 din lista de adiacenta in matrice de incidenta
    mat_incidenta();
    afisare_mat_incidenta();

    //1.4 din matrice de incidenta in lista de adiacenta
    lista_din_incidenta();
    afisare_lista_din_incidenta();

    //1.5 din lista de adiacenta in matrice de adiacenta
    matrice_adiac_din_lista();
    afisare_matrice_adiac_din_lista();

    //1.6 din matrice de adiacenta in lista
    lista_din_matrice();
    afisare_lista();

    //2.1 noduri izolate
    cout <<"\nnodurile izolate sunt: \n";
    for (i = 1; i <= n; i++)
    {
        ok = 0;
        for (j = 1; j <= n; j++)
        {
            if (mat[i][j])
                ok = 1;
        }
        if (ok == 0)
            cout << i << " ";
    }
    cout << "\n";

    //2.2 graf regular
    cout << "\neste graf regular? \n";
    int nrcurent = 0, last = 0;
    ok = 1;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (mat[i][j])
                nrcurent++;
        }
        if (last == 0)
            last = nrcurent;
        if(last!= nrcurent)
        {
            ok = 0;
        }
    }
    if (ok == 1)
        cout <<"DA\n";
    else
        cout <<"NU\n";
    //2.4 graf conex
    ok = conex();
    if (ok == 1)
        cout <<"\ngraful este conex\n";
    else
        cout <<"\ngraful nu este conex\n";

    //2.3 matricea distantelor
    roy_floyd(n);
    cout << "\nmatricea distantelor este: \n";
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
