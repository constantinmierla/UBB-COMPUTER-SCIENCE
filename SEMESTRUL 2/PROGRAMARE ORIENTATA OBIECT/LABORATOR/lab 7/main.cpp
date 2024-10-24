
#include "Test.h"
#include "TestMasina.h"
#include "TestRepo.h"
#include "TestValidatorMasina.h"
#include "TestStore.h"
#include "TestDynamicArray.h"

#include "CarRepo.h"
#include "ValidatorMasina.h"
#include "CarStore.h"
#include "Console.h"


int main() {
    TestMasina const tMasina{};
    TestRepo const tRepo{};
    TestValidatorMasina const tValidator{};
    TestStore const tStore{};
    TestDynamicArray const tDynamicArray{};


    Test const test{ tMasina, tRepo, tValidator, tStore, tDynamicArray};

    cout << "Rulare teste..." << '\n';
    test.runAllTests();
    cout << "Rulare reusita!" << '\n';
    if (true) {
        CarRepo repo{};
        ValidatorMasina const validator{};
        CarStore service{ repo, validator };
        const ConsoleUI console{ service };

        console.run();
    }



    return 0;
}