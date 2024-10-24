#include "Exceptions.h"

ostream& operator<<(ostream& out, const OutOfRangeException& ex) {
    out << ex.message;
    return out;
}