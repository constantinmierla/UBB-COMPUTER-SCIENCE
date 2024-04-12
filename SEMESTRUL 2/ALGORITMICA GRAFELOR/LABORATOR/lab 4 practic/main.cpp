#include <iostream>
#include <fstream>
using namespace std;
#define inf 999

// Vector pentru a stoca distantele minime de la sursa la fiecare nod
int d[10005];

struct bellman
{
    int x, y, c; // Nodul sursa, nodul destinatie si costul muchiei
} muchie[10005];


void relax(int u, int v, int c)
{
    if (d[v] > d[u] + c)
        d[v] = d[u] + c;
}

bool bellman_ford(int n, int v, int s)
{
    for (int i = 1; i <= n; i++)
        d[i] = inf;

    d[s] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= v; j++)
        {
            relax(muchie[j].x, muchie[j].y, muchie[j].c);
        }
    }

    for (int j = 1; j <= v; j++)
    {
        // Daca distanta catre nodul de destinatie al unei muchii poate fi redusa
        // mai mult prin intermediul nodului sursa al acelei muchii, atunci exista un ciclu negativ
        if (d[muchie[j].y] > d[muchie[j].x] + muchie[j].c)
            return false;
    }

    return true;
}

int main() {
    int x, y, c;

    std::ifstream in("inputfile.txt");
//    std::ofstream out("fisier_iesire.txt");

    // Citim informatiile despre fiecare muchie si le stocam  n vectorul muchie
    int nr_noduri = 0;
    int nr_muchii = 0;
    while(in >> x >> y >> c) {
//        cout << x << y << c << '\n';
        nr_muchii++;
        muchie[nr_muchii].x = x;
        muchie[nr_muchii].y = y;
        muchie[nr_muchii].c = c;

        if(nr_noduri < x)
            nr_noduri = x;
        if(nr_noduri < y)
            nr_noduri = y;
    }
    cout << "nr de orase: " << nr_noduri << " nr de drumuri: " << nr_muchii << '\n';
    /*for(int i = 1; i <= nr_muchii; i++)
        cout << muchie[i].x <<  " " << muchie[i].y << " " << muchie[i].c << '\n';*/

    int sursa;
    cout << "Introduceti orasul de start: ";
    cin >> sursa;

    if (!bellman_ford(nr_noduri, nr_muchii, sursa))
        cout << "ciclu negativ";
    else {
        // Afisam distantele minime catre fiecare nod sau "inf" in cazul in care nu exista drum intre sursa si nodul respectiv
        for (int i = 1; i <= nr_noduri; i++) {
            if (d[i] == inf)
                cout << "inf ";
            else
            {
                cout << d[i] << ' ';
            }

        }
    }

    in.close();

    return 0;
}