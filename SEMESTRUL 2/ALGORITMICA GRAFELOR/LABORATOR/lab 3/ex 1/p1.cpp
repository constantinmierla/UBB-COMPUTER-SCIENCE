#include <iostream>
#include <fstream>
using namespace std;
#define inf 99999

// Vector pentru a stoca distantele minime de la sursa la fiecare nod
int dist[10001];

struct bellman
{
    int x; //Nodul sursa
    int y; //Nodul destinatie
    int c; //costul muchiei
} muchie[10001];


void relax(int m, int v, int c)
{
    if (dist[v] > dist[m] + c)
        dist[v] = dist[m] + c;
}

bool bellman_ford(int n, int v, int s)
{
    for (int i = 0; i < n; i++)
        dist[i] = inf;

    dist[s] = 0;

    for (int i = 0; i < n; i++)
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
        if (dist[muchie[j].y] > dist[muchie[j].x] + muchie[j].c)
            return false;
    }

    return true;
}

//int main() {
//ifstream in("graf.in");
//ofstream out("graf.out");
int main(int argc, char *argv[])
{
    int n, m, s;

    if(argc < 3) {
        cout << "Numar insuficient de argumente!";
        return 0;
    }

    ifstream in(argv[1]);
    ofstream out(argv[2]);

    in >> n >> m >> s;

    for (int i = 1; i <= m; i++)
    {
        in >> muchie[i].x >> muchie[i].y >> muchie[i].c;
    }
    in.close();

    if (!bellman_ford(n, m, s))
    {
        out << "Este un ciclu negativ!";
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (dist[i] == inf)
                out << "inf ";
            else
                out << dist[i] << ' ';
        }
    }

    out.close();
    return 0;
}