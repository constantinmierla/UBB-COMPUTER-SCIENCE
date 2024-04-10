#pragma once

#include "Masina.h"
#include "CarRepo.h"
#include "ValidatorMasina.h"
#include "CarStore.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::stringstream;

class TestStore
{
private:
    void testAddMasina() const;
    void testGetAll() const;
    void testErase() const;
    void testFind() const;
    void testModify() const;
    void testSort() const;
    void testFilter() const;
public:
    void runAllTests() const;
};
