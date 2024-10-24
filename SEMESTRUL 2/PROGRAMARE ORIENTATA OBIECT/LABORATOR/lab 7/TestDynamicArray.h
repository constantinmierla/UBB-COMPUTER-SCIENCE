#pragma once
#include "DynamicArray.h"
#include "Masina.h"
#include <assert.h>
#include <sstream>

using std::stringstream;

class TestDynamicArray
{
private:
    void testPushBack() const;
    void testErase() const;
    void testClear() const;
    void testAt() const;
    void testIterator() const;
    void testLoopIterator() const;
    void testConvert() const;

public:
    void runAllTests() const;
};
