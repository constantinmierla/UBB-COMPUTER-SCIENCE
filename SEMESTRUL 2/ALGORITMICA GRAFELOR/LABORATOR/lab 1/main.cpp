#include <iostream>
#include <fstream>
using namespace std;
int n, mat[100][100] = {0},viz[100], x, y, i,j, nr_muchii = 0,inc[100][100] = {0}, ok;

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
int main()
{
    ifstream in ("in.txt");

    in >> n;
    //construiesc matricea de adiacenta
    while (in >> x and in >> y)
    {
        mat[x][y] = 1;
        mat[y][x] = 1;
        nr_muchii++;
        inc[x][nr_muchii] = 1;
        inc[y][nr_muchii] = 1;
    }
    //1.1 afisez matricea de adiacenta
    cout << "matricea de adiacenta este : \n";
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }

    //1.2 afisez lista adiacenta
    cout <<"\nlista adiacenta este : \n";
    for (i = 1; i <= n; i++)
    {
        cout << i << ": ";
        for (j = 1; j <= n; j++)
        {
            if (mat[i][j]!= 0 or mat[j][i]!= 0)
                cout << j << " ";
        }
        cout << "\n";
    }
    //1.3 afisez matricea de incidenta
    cout <<"\nmatricea de incidenta este: \n";
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= nr_muchii; j++)
        {
            cout << inc[i][j] << " ";
        }
        cout << "\n";
    }
    //2.1 noduri izolate
    cout <<"\nnodurile izolate sunt: \n";
    for (i = 1; i <=n; i++)
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
