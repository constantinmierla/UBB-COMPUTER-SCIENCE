#include "TestDynamicArray.h"
#include "Exceptions.h"

void TestDynamicArray::testPushBack() const{
    DynamicArray<Masina> array{};
    assert(array.size() == 0);

    Masina masina{ "BC12TRE", "Dacia", "Spring", "cross-over" };
    for (unsigned int i = 0; i < 100; ++i) {
        array.push_back(masina);
        assert(array.size() == i + 1);
    }
    assert(array.size() == 100);
    assert(array.at(0).GetNrInmatriculare() == "BC12TRE");
}

void TestDynamicArray::testClear() const{
    DynamicArray<Masina> array{};
    assert(array.size() == 0);

    Masina masina{ "BC12TRE", "Dacia", "Spring", "cross-over" };
    for (unsigned int i = 0; i < 100; ++i) {
        array.push_back(masina);
    }

    array.clear();
    assert(array.size() == 0);
}

void TestDynamicArray::testAt() const {
    DynamicArray<Masina> array{};
    assert(array.size() == 0);

    Masina masina{ "BC12TRE", "Dacia", "Spring", "cross-over" };
    array.push_back(masina);
    Masina masina1{ "BC12TRQ", "Dacia", "Spring", "cross-over" };
    array.push_back(masina1);

    try {
        array.at(2);
        assert(false);
    }
    catch (const OutOfRangeException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Index out of range!\n");
    }

    const Masina& found = array.at(1);
    assert(found.GetNrInmatriculare() == "BC12TRQ");
}

void TestDynamicArray::testIterator() const {
    DynamicArray<Masina> array{};
    assert(array.size() == 0);

    Masina masina{ "BC12TRE", "Dacia", "Spring", "cross-over" };
    array.push_back(masina);
    Masina masina1{ "BC12TRQ", "Dacia", "Spring", "cross-over" };
    array.push_back(masina1);

    DynamicArray<Masina>::IteratorDynamicArray it = array.begin();
    assert(it.valid() == true);

    const Masina& curr = it.element();
    assert(curr.GetNrInmatriculare() == "BC12TRE");

    it.next();

    assert(it.valid() == true);
    const Masina& curr1 = it.element();
    assert(curr1.GetNrInmatriculare() == "BC12TRQ");

    it.next();
    assert(it.valid() == false);

    try {
        it.element();
        assert(false);
    }
    catch (const OutOfRangeException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Iterator out of range!\n");
    }

    try {
        it.next();
        assert(false);
    }
    catch (const OutOfRangeException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Iterator out of range!\n");
    }

    const auto iter = array.begin();
    assert(iter.valid() == true);
    assert(iter.element().GetNrInmatriculare() == "BC12TRE");

    const auto iterEnd = array.end();
    assert(iterEnd.valid() == false);
}

void TestDynamicArray::testLoopIterator() const {
    DynamicArray<Masina> array{};
    assert(array.size() == 0);

    Masina masina{ "BC12TRE", "Dacia", "Spring", "cross-over" };
    array.push_back(masina);
    Masina masina1{ "BC12TRQ", "Dacia", "Spring", "cross-over" };
    array.push_back(masina1);

    int i = 1;
    for (const auto& elem : array) {
        if (i == 1) {
            assert(elem.GetNrInmatriculare() == "BC12TRE");
        }
        else {
            assert(elem.GetNrInmatriculare() == "BC12TRQ");
        }
        i = i + 1;
    }
}

void TestDynamicArray::testErase() const {
    DynamicArray<Masina> array{};

    Masina masina{ "BC12TRE", "Dacia", "Spring", "cross-over" };
    for (unsigned int i = 0; i < 100; ++i) {
        array.push_back(masina);
    }

    try {
        array.erase(100);
        assert(false);
    }
    catch (const OutOfRangeException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Index out of range!\n");
    }

    array.erase(5);
    assert(array.size() == 99);

    for (int i = 98; i >= 0; --i) {
        array.erase(i);
        assert(array.size() == i);
    }

    assert(array.size() == 0);
}

void TestDynamicArray::testConvert() const {
    DynamicArray<Masina> array{};
    assert(array.size() == 0);

    Masina masina{ "BC12TRE", "Dacia", "Spring", "cross-over" };
    array.push_back(masina);
    Masina masina1{ "BC12TRQ", "Dacia", "Spring", "cross-over" };
    array.push_back(masina1);
    Masina masina2{ "BC12TRC", "Dacia", "Spring", "cross-over" };
    array.push_back(masina2);


    const vector<Masina> convert = array.toStdVector();
    assert(convert.at(0).GetNrInmatriculare() == "BC12TRE");
    assert(convert.at(1).GetNrInmatriculare() == "BC12TRQ");
    assert(convert.at(2).GetNrInmatriculare() == "BC12TRC");
}


void TestDynamicArray::runAllTests() const{
    testPushBack();
    testErase();
    testClear();
    testAt();
    testIterator();
    testLoopIterator();
    testConvert();
}