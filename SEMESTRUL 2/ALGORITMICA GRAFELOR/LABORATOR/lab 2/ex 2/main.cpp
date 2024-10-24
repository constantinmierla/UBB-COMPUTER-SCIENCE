/*
 * 2. Sa se determine închiderea transitivă a unui graf orientat.
 * (Închiderea tranzitivă poate fi reprezentată ca matricea care descrie,
 * pentru fiecare vârf în parte, care sunt vârfurile accesibile din acest vârf.
 * Matricea inchiderii tranzitive arată unde se poate ajunge din fiecare vârf.)
 * ex. figura inchidere_tranzitiva.png - pentru graful de sus
 * se construieste matricea de jos care arata inchiderea tranzitiva.
 */
#include <iostream>
#include <fstream>

using namespace std;

ifstream in("graf.txt");

int mat[50][50], n, m, i, j, z, x, y;

void inchide() {
    for(z = 1; z <= n; z++)
    {
        for(i = 1; i<=n; i++)
        {
            for(j = 1; j<=n; j++)
            {
                if(mat[i][j] == 0)
                {
                    if (mat[i][z] != 0)
                    {
                        if (mat[z][j] != 0)
                        {
                            mat[i][j] = 1;
                        }
                        else
                        {
                            mat[i][j] = 0;
                        }
                    }
                    else
                    {
                        mat[i][j] = 0;
                    }

                }
            }
        }
    }
}

void afis()
{
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << '\n';
    }
}

int main()
{
    //e graful din inchidere_tranzitiva.png doar ca numar de la 1 la 6
    in >> n >> m;

    //am adaugat si arcele corespunzatoare din matricea de adiacenta (1,1) (2,2)... (6,6)
    for(i = 1; i <= n; i++)
        mat[i][i] = 1;

    //acum pun arcele
    for(i = 1; i <= m; i++) {
        in >> x >> y;
        mat[x][y] = 1;
    }
    in.close();

    cout<<"Matricea de adiacenta mat grafului orientat:\n";
    afis();

    cout<<"\nMatricea inchiderii tranzitive:\n";
    inchide();
    afis();

    return 0;
}
