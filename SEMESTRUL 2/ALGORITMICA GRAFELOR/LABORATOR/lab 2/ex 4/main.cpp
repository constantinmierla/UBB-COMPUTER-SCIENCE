/*
 * 4. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de
 * algoritmul BFS și distanța față de vârful sursă (arborele descoperit).
 */
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("graf.txt");

int viz[102],mat[102][102], c[1002];

void bfs(int nod, int n)
{
    int d = 1, first = 0, last = 0, i;
    c[last++] = nod;
    viz[nod] = 1;
    while(first != last)
    {
        for(i = 1; i <= n; i++)
        {
            if(mat[c[first]][i] and !viz[i])
            {
                cout << i << " " << d << '\n';
                c[last] = i;
                last++;
                viz[i] = 1;
            }
        }
        first++;
        d++;
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
    bfs(nod, n);
    return 0;
}
