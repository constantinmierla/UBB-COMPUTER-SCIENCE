#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>
#include <iostream>
#include <stdlib.h>


//WC=AC=BC=Theta(1) => overall theta(1)
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {

    this->list = mult.ldi;
    this->currentElement = mult.ldi.inceput;
}

//WC=AC=BC=Theta(1) => overall Theta(1)
void IteratorMultime::prim() {
    this->currentElement = mult.ldi.inceput;
}

//WC=AC=BC=Theta(1) =>  overall theta(1)
TElem IteratorMultime::element() const {
    if (!valid()) {
        throw std::exception();
    }
    return this->list.nodes[this->currentElement].info;

}

//WC=AC=BC=Theta(1) => overall theta(1)
bool IteratorMultime::valid() const {
    return this->currentElement != -1;
}


//WC=AC=BC=Theta(1) => overall theta(1)
void IteratorMultime::urmator() {

    if (!valid()) {
        throw std::exception();
    }
    this->currentElement = this->list.nodes[this->currentElement].urm;

}

//WC=AC=BC=Theta(1) => overall theta(1)
void IteratorMultime::anterior()
{
    if (!valid()) {
        std::exception();
    }
    else {
        if (this->currentElement == mult.ldi.inceput) {
            this->currentElement = -1;
        }
        else {
            this->currentElement = this->list.nodes[this->currentElement].ant;
        }
    }
}

