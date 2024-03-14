/*
 * 5. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite
 * de apelul recursiv al procedurii DFS_VISIT(G, u) (apadurea descoperită de DFS).
 */
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("graf.txt");

int viz[102],mat[102][102];

void dfs(int nod, int n)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        if(!viz[i] and mat[nod][i])
        {
            cout << i << " ";
            viz[i] = 1;
            dfs(i,n);
        }
    }
}
int main()
{
    int x,y,n,nod;
    in >> n;
    while(in >> x >> y)
        mat[x][y] = 1;
    in.close();
    cin >> nod;
    dfs(nod, n);
    return 0;
}
