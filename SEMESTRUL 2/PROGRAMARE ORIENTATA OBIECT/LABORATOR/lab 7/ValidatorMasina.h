#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Masina.h"

using std::string;
using std::vector;
using std::ostream;

class ValidateException
{
    vector<string> errors;

public:
    ValidateException(const vector<string>& errors) : errors{ errors } {};

    friend ostream& operator<<(ostream& out, const ValidateException& val);
};

class ValidatorMasina
{
private:
    static bool esteNrInmatriculare(const string& nrInmatriculare) ;
public:
    void validate(const Masina& masina) const;
};
