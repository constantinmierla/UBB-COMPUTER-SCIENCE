#pragma once
#include "Masina.h"
#include "CarRepo.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

class TestRepo
{
    void testStore() const;
    void testErase() const;
    void testFind() const;
    void testGetAll() const;
    void testPrint() const;
    void testModify() const;

public:
    void runAllTests() const;
};
