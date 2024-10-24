#pragma once
#include <string>
#include <assert.h>
#include <sstream>
#include "ValidatorMasina.h"

using std::string;
using std::stringstream;

class TestValidatorMasina
{
private:
    void testValidate() const;
public:
    void runAllTests() const;
};
