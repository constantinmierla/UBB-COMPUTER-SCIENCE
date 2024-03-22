//
// Created by david on 3/6/24.
//

#include <stdlib.h>
#include "./Domain/product.h"
#include "./Repository/repository.h"
#include "./UI/ui.h"
#include "./Tests/test.h"


int main() {
    testAll();



    Repository repo;
    Validator vali;
    Service service;
    Console console;
    service.repository = &repo;
    service.validator = &vali;
    console.service = &service;

    initRepository(&repo, 11);
    setUp(&service);

    run(console);

    free(repo.products);
}