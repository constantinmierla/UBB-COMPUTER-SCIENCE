#pragma once
#include "Masina.h"
#include <assert.h>
#include <sstream>

using std::stringstream;

class TestMasina
{
private:
    void testGetAndSet() const;
    void testCopy() const;
    void testCompare() const;
    void testPrint() const;

public:
    void runAllTests() const;
};
