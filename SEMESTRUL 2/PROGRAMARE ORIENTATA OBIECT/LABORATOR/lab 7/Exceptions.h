#pragma once
#include <string>
#include <sstream>

using std::string;
using std::ostream;

class OutOfRangeException {
    string message;
public:
    OutOfRangeException(string message) : message{ message } {};

    /**
    * Functie generica pentru afisarea unei CarRepoException
    *
    * @params: out - o referinta la un string de tip ostream
    *		   ex - o referinta constanta la o CarRepoException
    *
    * @return: o referinta la un string de tip ostream
    */
    friend ostream& operator<<(ostream& out, const OutOfRangeException& ex);
};
