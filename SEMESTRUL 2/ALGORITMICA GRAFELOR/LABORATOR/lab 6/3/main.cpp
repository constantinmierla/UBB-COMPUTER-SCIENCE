#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("input.txt");

int nr_noduri;
vector<int> ciclu;
vector<vector<int>> graf;

void Eulerian(int nod_curent)
{
    for (int i = 0; i < nr_noduri; i++)
        if (graf[nod_curent][i] != 0)  {                     // exista vecini
            graf[nod_curent][i] = graf[i][nod_curent] = 0;   // sterg muchia
            Eulerian(i);                                     // merg la urmatorul nod (vecin)
        }
    ciclu.emplace_back(nod_curent);                          // adaug nodul la ciclul eulerian
}

void Citire()
{
    int x, y, nr_muchii;
    fin >> nr_noduri >> nr_muchii;

    // initializare graf cu 0
    graf = vector<vector<int>>(nr_noduri);
    for (int i = 0; i < nr_noduri; i++)
        graf[i] = vector<int>(nr_noduri, 0);

    // citirea muchiilor
    for (int i = 1; i <= nr_muchii; i++) {
        fin >> x >> y;
        graf[x][y] = graf[y][x] = 1;
    }
}

void Afisare()
{
    for(int i = 0; i < ciclu.size(); i++) {
        cout << ciclu[i];

        if(i != ciclu.size() - 1) {
            cout << " ";
        }
    }
}

int main()
{
    Citire();
    Eulerian(0);
    Afisare();
    return 0;
}