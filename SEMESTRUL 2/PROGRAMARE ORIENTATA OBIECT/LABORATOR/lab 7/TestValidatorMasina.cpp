#include "TestValidatorMasina.h"

void TestValidatorMasina::testValidate() const {
    ValidatorMasina const validator{};

    Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
    validator.validate(masina);

    Masina masinaInvalidNumar{ "cB24ABC", "Dacia", "Logan", "berlina" };

    try {
        validator.validate(masinaInvalidNumar);
        assert(false);
    }
    catch (const ValidateException& ex) {
        stringstream os;
        os << ex;
        assert(os.str() == "Numar de inmatriculare invalid!\n");
        assert(true);
    }

    Masina masinaInvalidNumarCifre{ "BC2TABC", "Dacia", "Logan", "berlina" };

    try {
        validator.validate(masinaInvalidNumarCifre);
        assert(false);
    }
    catch (const ValidateException& ex) {
        stringstream os;
        os << ex;
        assert(os.str() == "Numar de inmatriculare invalid!\n");
        assert(true);
    }

    Masina const masinaInvalida{ "BC25ABCA", "", "", "" };

    try {
        validator.validate(masinaInvalida);
        assert(false);
    }
    catch (const ValidateException& ex) {
        stringstream os;
        os << ex;
        assert(os.str() == "Numar de inmatriculare invalid!\nProducator invalid!\nModel invalid!\nTip invalid!\n");
        assert(true);
    }
}

void TestValidatorMasina::runAllTests() const {
    testValidate();
}