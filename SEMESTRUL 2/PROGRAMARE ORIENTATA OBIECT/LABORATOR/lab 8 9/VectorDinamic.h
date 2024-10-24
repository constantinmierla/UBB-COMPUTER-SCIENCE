#pragma once

template<typename ElemType>
class Iterator;


template<typename ElemType>
class VectorDinamic {
public:
    /*
     * Constructor pentru VectorDinamic
     */
    VectorDinamic();

    /*
     * Constructor copiator pentru VectorDinamic
     */
    VectorDinamic(const VectorDinamic& ot);

    /*
     * Destructor pentru VectorDinamic
     */
    ~VectorDinamic();

    /*
     * Operator de atribuire pentru VectorDinamic
     */
    VectorDinamic& operator=(const VectorDinamic& ot);

    void push_back(const ElemType& el);

    ElemType& get(int poz) const noexcept;

    VectorDinamic& operator!=(const VectorDinamic& ot);

    [[nodiscard]] int size() const noexcept;

    void erase(int poz);

    friend class Iterator<ElemType>;
    Iterator<ElemType> begin() const;
    Iterator<ElemType> end() const;

private:
    void ensureCapacity();
    int lungime{ 0 };
    int capacitate{ 2 };
    ElemType* elems;
};

template<typename ElemType>
VectorDinamic<ElemType>::VectorDinamic() : elems{ new ElemType[capacitate] } {

}

template<typename ElemType>
VectorDinamic<ElemType>::VectorDinamic(const VectorDinamic& ot) {
    elems = new ElemType[ot.capacitate];
    for (int i = 0; i < ot.lungime; i++) {
        elems[i] = ot.elems[i];
    }
    lungime = ot.lungime;
    capacitate = ot.capacitate;
}

template<typename ElemType>
VectorDinamic<ElemType>::~VectorDinamic() {
    delete[] elems;
}

template<typename ElemType>
VectorDinamic<ElemType>& VectorDinamic<ElemType>::operator=(const VectorDinamic& ot) {
    if (this == &ot)
        return *this;
    delete[] elems;
    elems = new ElemType[ot.capacitate];
    for (int i = 0; i < ot.lungime; i++) {
        elems[i] = ot.elems[i];
    }
    lungime = ot.lungime;
    capacitate = ot.capacitate;
    return *this;
}

template<typename ElemType>
VectorDinamic<ElemType>& VectorDinamic<ElemType>::operator!=(const VectorDinamic<ElemType>& ot) {
    return *this != ot;
}

template<typename ElemType>
void VectorDinamic<ElemType>::push_back(const ElemType& el) {
    if (lungime == capacitate)
        ensureCapacity();
    elems[lungime++] = el;
}

template<typename ElemType>
ElemType& VectorDinamic<ElemType>::get(int poz) const noexcept {
    return elems[poz];
}

template<typename ElemType>
int VectorDinamic<ElemType>::size() const noexcept {
    return lungime;
}

template<typename ElemType>
void VectorDinamic<ElemType>::erase(int poz) {
    for (int i = poz; i < lungime - 1; i++) {
        elems[i] = elems[i + 1];
    }
    lungime--;
}

template<typename ElemType>
void VectorDinamic<ElemType>::ensureCapacity() {
    capacitate *= 2;
    ElemType* aux = new ElemType[capacitate];
    for (int i = 0; i < lungime; i++) {
        aux[i] = elems[i];
    }
    delete[] elems;
    elems = aux;
}

template<typename ElemType>
class Iterator {
private:
    const VectorDinamic<ElemType>& vector;
    int pozitie{};
public:
    explicit Iterator(const VectorDinamic<ElemType>& vector) noexcept;
    Iterator(const VectorDinamic<ElemType>& vector, int pozitie) noexcept;
    ElemType& element()const;
    void urmator();
    ElemType& operator*();
    Iterator& operator++();
    bool operator==(const Iterator& obiect)noexcept;
    bool operator!=(const Iterator& obiect)noexcept;
};


template<typename ElemType>
Iterator<ElemType>::Iterator(const VectorDinamic<ElemType>& vector) noexcept : vector{ vector } {}

template<typename ElemType>
Iterator<ElemType>::Iterator(const VectorDinamic<ElemType>& vector, int pozitie) noexcept : vector{ vector }, pozitie{ pozitie } {}

template<typename ElemType>
ElemType& Iterator<ElemType>::element() const {
    return vector.get(pozitie);
}

template<typename ElemType>
void Iterator<ElemType>::urmator() {
    pozitie++;
}

template<typename ElemType>
ElemType& Iterator<ElemType>::operator*() {
    return element();
}

template<typename ElemType>
Iterator<ElemType>& Iterator<ElemType>::operator++() {
    urmator();
    return *this;
}

template<typename ElemType>
bool Iterator<ElemType>::operator==(const Iterator& obiect) noexcept {
    return pozitie == obiect.pozitie;
}

template<typename ElemType>
bool Iterator<ElemType>::operator!=(const Iterator& obiect) noexcept {
    return !(*this == obiect);
}

template<typename ElemType>
Iterator<ElemType> VectorDinamic<ElemType>::begin() const {
    return Iterator<ElemType>(*this);
}

template<typename ElemType>
Iterator<ElemType> VectorDinamic<ElemType>::end() const {
    return Iterator<ElemType>(*this, lungime);
}







