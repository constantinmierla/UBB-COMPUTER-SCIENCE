/*
 * 3. Să se scrie un program care găsește o soluție pentru unul din următoarele labirinturi:
 * labirint_1.txt, labirint_2.txt, labirint_cuvinte.txt.
 * Pentru labirintul 1 si 2 punctul de pornire este indicat de litera S
 * și punctul de oprire este indicat de litera F, spre deosebire de
 * labirintul 1 și 2, labirintul 3 nu are o soluție unică.
 */
#include <fstream>
#include <cstring>

using namespace std;

ifstream in("labirint_1.txt");
ofstream out("labirint1_rezolvat.txt");

int mat[1000][1000],n,m,XS,YS,XF,YF,i,j;
char sir[1000];

void bordare_matrice()
{
    //bordarea matricei
    for(i = 0; i <= n+1; i++)
    {
        mat[i][0] = -1;
        mat[i][m + 1] = -1;
    }
    for(i = 0;i <= m+1; i++)
    {
        mat[0][i] = -1;
        mat[n + 1][i] = -1;
    }
}

void algoritm_lee(int x, int y)
{
    //algoritm specific algoritm_lee
    if(x == XF && y == YF) {
        return;
    }
    if(mat[x + 1][y] == 0 || mat[x][y] + 1 < mat[x + 1][y]) {
        mat[x + 1][y] = mat[x][y] + 1;
        algoritm_lee(x + 1, y);
    }
    if(mat[x - 1][y] == 0 || mat[x][y] + 1 < mat[x - 1][y]) {
        mat[x - 1][y] = mat[x][y] + 1;
        algoritm_lee(x - 1, y);
    }
    if(mat[x][y + 1] == 0 || mat[x][y] + 1 < mat[x][y + 1]) {
        mat[x][y + 1] = mat[x][y] + 1;
        algoritm_lee(x, y + 1);
    }
    if(mat[x][y - 1] == 0 || mat[x][y] + 1 < mat[x][y - 1]) {
        mat[x][y - 1] = mat[x][y] + 1;
        algoritm_lee(x, y - 1);
    }
}

int main()
{
    int x,y;

    while(in.getline(sir, 2000))
    {
        n++;
        m = strlen(sir);

        for(i = 0; i<strlen(sir); i++) {
            if(sir[i] == '1')
                mat[n][i + 1] = -1;

            else if(sir[i] == ' ')
                mat[n][i + 1]=0;

            else if(sir[i] == 'S')
            {
                mat[n][i + 1] = 1;
                XS = n;
                YS = i + 1;
            }
            else
            {
                XF = n;
                YF = i + 1;
            }
        }
    }

    bordare_matrice();
    algoritm_lee(XS, YS);

    out << "lungime drum ---> " << mat[XF][YF] << '\n';

    x = XF;
    y = YF;

    while(x != XS || y != YS)
    {
        if(mat[x - 1][y] + 1 == mat[x][y]) {
            mat[x][y] = -2;
            x--;
        }
        else if(mat[x + 1][y] + 1 == mat[x][y]) {
            mat[x][y] = -2;
            x++;
        }
        else if(mat[x][y - 1] + 1 == mat[x][y]) {
            mat[x][y] = -2;
            y--;
        }
        else if(mat[x][y + 1] + 1 == mat[x][y]) {
            mat[x][y] = -2;
            y++;
        }
    }

    mat[XF][YF] = -3;

    for(i = 1; i <= n; i++) {
        for(j = 1; j <= m; j++) {
            if(mat[i][j] == 1)
                out << 'S';
            else if(mat[i][j] == -2)
                out << 'X';
            else if(mat[i][j] == -3)
                out << 'F';
            else out << ' ';
        }
        out << '\n';
    }
    return 0;
}