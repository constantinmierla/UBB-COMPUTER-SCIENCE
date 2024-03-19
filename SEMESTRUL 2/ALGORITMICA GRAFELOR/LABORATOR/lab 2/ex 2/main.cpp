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

int main()
{
    int n,m,mat[102][102] = {0}, x, y,i,j, c[1002] = {0},first,last, d[102][102] = {0};

    in>> n;
    while (in >> x >> y)
        mat[x][y] = 1;
    in.close();
    for(i = 1; i <= n; i++)
    {
        first = 0;
        c[0] = i;
        last = 1;

        while(last > first)
        {
            for(j = 1; j <= n; j++)
            {
                if(mat[c[first]][j]!=0)
                {
                    c[last] = j;
                    last++;
                }
            }
            first++;
            if(first != last)
                d[i][c[last]] = 1;
        }
    }
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
            cout << d[i][j]<< " ";
        cout << '\n';
    }
    return 0;
}
