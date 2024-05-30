#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Nod {
    char c; // Carac
    int frecventa; // Frecventa carac
    Nod* stanga; // Pointer catre copilul stang
    Nod* dreapta; // Pointer catre copilul drept

    Nod(char caracter, int frecv) : c(caracter), frecventa(frecv), stanga(nullptr), dreapta(nullptr) {}
};

// comparator
struct Comparator {
    bool operator()(Nod* stanga, Nod* dreapta) {
        return stanga->frecventa > dreapta->frecventa; // Nodul cu frecventa mai mica are prioritate mai mare
    }
};

//generarea codurilor Huffman
void generareCoduri(Nod* radacina, const string& cod, vector<pair<char, string>>& coduriHuffman) {
    if (!radacina) return; // Daca nodul este nul, return
    if (!radacina->stanga && !radacina->dreapta) { // Daca nodul este frunza
        coduriHuffman.push_back({radacina->c, cod}); // Adaugam caracterul si codul sau in vector
    }
    generareCoduri(radacina->stanga, cod + "0", coduriHuffman); // Apelam pentru copilul stang
    generareCoduri(radacina->dreapta, cod + "1", coduriHuffman); // Apelam pentru copilul drept
}

Nod* construesteArboreHuffman(const string& mesaj) {
    vector<int> frecvente(256, 0); // Vector pentru frecv
    for (char c : mesaj) {
        frecvente[c]++; // Calculam frecv
    }

    priority_queue<Nod*, vector<Nod*>, Comparator> pq;
    for (int i = 0; i < 256; ++i) {
        if (frecvente[i] > 0) {
            pq.push(new Nod(i, frecvente[i])); // Adaugam nodurile in coada
        }
    }

    // arborele Huffman
    while (pq.size() != 1) {
        Nod* stanga = pq.top(); pq.pop(); // Extragem nodul cu frecv minima
        Nod* dreapta = pq.top(); pq.pop(); // Extragem urmatorul nod cu frecvminima
        Nod* nou = new Nod('\0', stanga->frecventa + dreapta->frecventa); // Cream un nod nou
        nou->stanga = stanga; // Setam copilul stang
        nou->dreapta = dreapta; // Setam copilul drept
        pq.push(nou); // Adaugam noul nod in coada de prioritati
    }

    return pq.top(); // radacina arborelui
}

string comprima(const string& mesaj, const vector<pair<char, string>>& coduriHuffman) {
    string mesaj_comprimat = "";
    for (char c : mesaj) {
        for (const auto& pereche : coduriHuffman) {
            if (pereche.first == c) {
                mesaj_comprimat += pereche.second; // Adaugam codul corespunzator caracterului
                break;
            }
        }
    }
    return mesaj_comprimat;
}

string decomprima(const string& mesaj_comprimat, Nod* radacina) {
    string mesaj_decomprimat = "";
    Nod* curent = radacina;
    for (char bit : mesaj_comprimat) {
        if (bit == '0') curent = curent->stanga; // Navigam spre stanga daca bitul este '0'
        else curent = curent->dreapta; // Navigam spre dreapta daca bitul este '1'
        if (!curent->stanga && !curent->dreapta) { // Daca am ajuns la o frunza
            mesaj_decomprimat += curent->c; // Adaugam caracterul la mesajul decomprimat
            curent = radacina; // Revenim la radacina pentru urmatorul caracter
        }
    }
    return mesaj_decomprimat;
}

int main() {
    string mesaj = "Treeaaassuureee";
    vector<pair<char, string>> coduriHuffman;
    Nod* radacina = construesteArboreHuffman(mesaj);
    generareCoduri(radacina, "", coduriHuffman);

    string mesaj_comprimat = comprima(mesaj, coduriHuffman);
    cout << "Mesaj comprimat: " << mesaj_comprimat << endl;

    string mesaj_decomprimat = decomprima(mesaj_comprimat, radacina);
    cout << "Mesaj decomprimat: " << mesaj_decomprimat << endl;

    return 0;
}
