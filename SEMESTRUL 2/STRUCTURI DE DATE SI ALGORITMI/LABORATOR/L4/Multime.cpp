#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}

//WC=AC=BC=Theta(n), =>  theta(n) n-capacitate initiala
Multime::Multime() {
    this->ldi.capacitate = cap;
    this->ldi.inceput = -1;
    this->ldi.sfarsit = -1;
    this->ldi.size = 0;
    this->ldi.firstEmpty = 0;

    this->ldi.nodes = new nod[cap];

    for (int i = 0; i < cap - 1; i++) {
        this->ldi.nodes[i].urm = i + 1;
    }
    this->ldi.nodes[cap - 1].urm = -1;

    for (int i = 1; i < cap; i++) {
        this->ldi.nodes[i].ant = i - 1;
    }
    this->ldi.nodes[0].ant = -1;

}

//WC=AC=Theta(n), BC = Theta(1) => overall  O(n)
//insereaza pe pozitia potrivita in ldi noul element
void Multime::insertPosition(TElem e, int pos)
{
    int newElem = allocate();
    if (newElem == -1) {
        resize();
        newElem = allocate();
    }
    ldi.nodes[newElem].info = e;
    if (pos == 0) {
        //primul element din ldi
        if (ldi.inceput == -1) {
            ldi.inceput = newElem;
            ldi.sfarsit = newElem;
        }
            //in loc primul elem din ldi
        else {
            ldi.nodes[newElem].urm = ldi.inceput;
            ldi.nodes[ldi.inceput].ant = newElem;
            ldi.inceput = newElem;
        }
    }
    else {
        int currentNode = ldi.inceput;
        int currentPos = 0;

        //realizeaza legaturile dintre elementul anterior si urmator
        while (currentNode != -1 && currentPos < pos - 1) {
            currentNode = ldi.nodes[currentNode].urm;
            currentPos++;
        }
        if (currentNode != -1) {
            int nodNext = ldi.nodes[currentNode].urm;
            ldi.nodes[newElem].urm = nodNext;
            ldi.nodes[newElem].ant = currentNode;
            ldi.nodes[currentNode].urm = newElem;
            if (nodNext == -1) {
                ldi.sfarsit = newElem;
            }
            else {
                ldi.nodes[nodNext].ant = newElem;
            }
        }
    }
}

//WC=AC=BC=Theta(n), => overall theta(n), n-capacitate
void Multime::resize()
{
    nod* newElems = new nod[ldi.capacitate * 2];

    //copiaza prima jumatate
    for (int i = 0; i < ldi.capacitate; i++)
        newElems[i] = ldi.nodes[i];

    //initializeaza urm pentru a 2a jum
    for (int i = ldi.capacitate; i < 2 * ldi.capacitate - 1; i++)
    {
        newElems[i].urm = i + 1;
    }
    newElems[ldi.capacitate * 2 - 1].urm = -1;

    //initializeaza ant pentru a 2a jum
    for (int i = ldi.capacitate + 1; i < 2 * ldi.capacitate; i++)
    {
        newElems[i].ant = i - 1;
    }
    newElems[ldi.capacitate].ant = -1;

    //copy the other stuff and double capacity
    ldi.firstEmpty = ldi.capacitate;
    ldi.capacitate *= 2;
    delete[] ldi.nodes;
    ldi.nodes = newElems;
}

//WC=AC=BC=Theta(1) => overall theta(1)
//"aloca" locul in ldi pentru element
int Multime::allocate()
{
    int newElem = ldi.firstEmpty;
    if (newElem != -1) {
        ldi.nodes[ldi.firstEmpty].ant = -1;
        ldi.firstEmpty = ldi.nodes[ldi.firstEmpty].urm;
        ldi.nodes[newElem].urm = -1;
        ldi.nodes[newElem].ant = -1;
    }
    return newElem;
}

//WC=AC=BC=Theta(1) => overall theta(1)
//"elibereaza" spatiul unui elem
void Multime::free(int poz)
{
    ldi.nodes[poz].urm = ldi.firstEmpty;
    ldi.nodes[poz].ant = -1;
    ldi.nodes[ldi.firstEmpty].ant = poz;
    ldi.firstEmpty = poz;
}

//WC=AC=Theta(n), BC = Theta(1) => overall O(n)
bool Multime::adauga(TElem e) {

    if (cauta(e))
        return false;
    int current = ldi.inceput;
    int poz_curenta = 0;
    while (current != -1 && poz_curenta < this->dim() && ldi.nodes[current].info != e && rel(ldi.nodes[current].info, e)) {
        current = ldi.nodes[current].urm;
        poz_curenta++;
    }
    insertPosition(e, poz_curenta);
    this->ldi.size++;
    return true;
}

//WC=AC=Theta(n), BC = theta(1) => overall O(n)
bool Multime::sterge(TElem e) {
    int currentNode = this->ldi.inceput;
    int previousNode = -1;

    while (currentNode != -1 && rel(this->ldi.nodes[currentNode].info, e)) {
        if (this->ldi.nodes[currentNode].info == e) {
            if (currentNode == this->ldi.inceput) {
                this->ldi.inceput = this->ldi.nodes[currentNode].urm;
                if (this->ldi.inceput != -1) {
                    this->ldi.nodes[this->ldi.inceput].ant = -1;
                }
            }
            if (currentNode == this->ldi.sfarsit) {
                this->ldi.sfarsit = this->ldi.nodes[currentNode].ant;
                if (this->ldi.sfarsit != -1) {
                    this->ldi.nodes[this->ldi.sfarsit].urm = -1;
                }
            }
            if (this->ldi.nodes[currentNode].urm != -1) {
                this->ldi.nodes[this->ldi.nodes[currentNode].urm].ant = this->ldi.nodes[currentNode].ant;
            }
            if (this->ldi.nodes[currentNode].ant != -1) {
                this->ldi.nodes[this->ldi.nodes[currentNode].ant].urm = this->ldi.nodes[currentNode].urm;
            }
            this->free(currentNode);
            this->ldi.size--;
            return true;
        }
        previousNode = currentNode;
        currentNode = this->ldi.nodes[currentNode].urm;
    }
    return false;
}




//WC=AC=Theta(n), BC = theta(1) => overall O(n)
bool Multime::cauta(TElem elem) const {

    if (vida())
        return false;
    int nod_curent = ldi.inceput;
    while (nod_curent != -1 && ( rel(this->ldi.nodes[nod_curent].info, elem))) {
        if (ldi.nodes[nod_curent].info == elem)
            return true;
        nod_curent = ldi.nodes[nod_curent].urm;
    }
    return false;
}

/*
* Intersecteaza elementele din b cu cele din a
* daca un el. din b nu exista in a, il sterge
* la fel si invers
*
* Pseudocod:
*	subalgoritm intersectie( Mulime b )
*		Iterator i = b.@iterator
*		cat timp(i.valid) executa
* 		daca(!cauta i.element in a)
* 		@sterge i.element
* 		i.urmator
* 	Sf. cat timp
*
* 	i = b.@iterator
* 	cat timp(i.valid) executa
* 		daca(!cauta i.element in b)
* 		@sterge i.element
* 		i.urmator
*		Sf. cat timp
*	Sf. subalgoritm
*
* Complexitate timp:
*		n-dimensiunea lui a
*		m-dimensiunea lui b
*		trebuie sa parcurg multimea a de m ori,
*       iar apoi multimea b de n ori
*		caz favorabil = theta(1)
		caz defavorabil = theta(m*max(m,n))
		caz mediu = O(m*max(m,n))
*
*/
void Multime::intersectie(const Multime& b) {
    IteratorMultime i = b.iterator();
    TElem elem;

    while (i.valid()) {
        elem=i.element();
        if(cauta(elem)==false)
            sterge(i.element());
        i.urmator();
    }
    IteratorMultime i1 = this->iterator();

    while (i1.valid()) {
        elem = i1.element();
        if (b.cauta(elem)==false)
            sterge(i1.element());
        i1.urmator();
    }


}



//theta(1)
int Multime::dim() const {

    return this->ldi.size;
}



//theta(1)
bool Multime::vida() const {

    return this->ldi.size == 0;
}


//theta(1)
IteratorMultime Multime::iterator() const {
    return IteratorMultime(*this);
}


/*Destructorul multimii
 theta(1)
*/
Multime::~Multime() {

    delete[]ldi.nodes;
}



/*void Multime::afisare() {

	int iterator = prim;
	while (iterator != -1) {
		cout << iterator << " " << elems[iterator] << " " << urm[iterator] << endl;
		iterator = urm[iterator];
	}

}*/

