#pragma once
#include "TestMasina.h"
#include "TestRepo.h"
#include "TestValidatorMasina.h"
#include "TestStore.h"
#include "TestDynamicArray.h"

class Test
{
private:
    const TestMasina& tMasina;
    const TestRepo& tRepo;
    const TestValidatorMasina& tValidator;
    const TestStore& tStore;
    const TestDynamicArray& tDynamicArray;
public:

    Test(const TestMasina& tMasina, const TestRepo& tRepo, const TestValidatorMasina& tValidator, const TestStore& tStore, const TestDynamicArray& tDynamicArray) noexcept : tMasina{ tMasina }, tRepo{ tRepo }, tValidator{ tValidator }, tStore{ tStore }, tDynamicArray{ tDynamicArray } { };
    void runAllTests() const;
};
