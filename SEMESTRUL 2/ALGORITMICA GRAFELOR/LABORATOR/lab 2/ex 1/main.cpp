#include <iostream>
#include <fstream>
using namespace std;
ifstream in("graf.txt");

int mat[102][102],viz[102][102], rezultat[102];
void dfs(int nod, int nr, int n,int &mini)
{
    int count = 0;
    for(int i = 0; i <= n; i++)
    {
        if(mat[nod][i] and viz[nod][i] == 0)
        {
            rezultat[nr] = i;
            viz[nod][i] = 1;
            dfs(i, nr+1, n, mini);
            viz[nod][i] = 0;
            count++;
        }
    }
    if (count == 0 and (mini == -1 or nr < mini))
        mini = nr;
}
int main()
{
    int n, x , y, i, vf, mini = -1;
    in >> n;
    while (in >> x >> y)
    {
        mat[x][y] = 1;
    }
    cout<<"Introduceti varful sursa:  ";
    cin >> vf;
    dfs(vf,0,n,mini);

    cout << vf << " ";
    for(i = 0; i < mini; i++)
        cout << rezultat[i] << " ";
    return 0;
}
