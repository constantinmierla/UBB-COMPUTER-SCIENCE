//
// Created by david on 3/6/24.
//

#ifndef LAB2_TEST_H
#define LAB2_TEST_H
#include "../Repository/repository.h"
#include "../Service/service.h"

//domain tests
void testGetType();
void testGetProducer();
void testGetModel();
void testGetId();
void testGetPrice();
void testGetQuantity();

//repository tests
void testCreate();
void testFind();
void testUpdateQuantity();
void testUpdatePriceOrQuantity();
void testDelete();

//service tests
void testAddProduct();
void testUpdatePriceForProduct();
void testUpdateQuantityForProduct();
void testDeleteProduct();
void testShowAll();
void testShowAllSortedBy();

void testAdd10000ELements();

void testAll();

#endif //LAB2_TEST_H
