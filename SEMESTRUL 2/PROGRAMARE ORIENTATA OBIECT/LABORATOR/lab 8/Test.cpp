#include "Test.h"

void Test::runAllTests() const {
    tDynamicArray.runAllTests();
    tMasina.runAllTests();
    tRepo.runAllTests();
    tValidator.runAllTests();
    tStore.runAllTests();
}