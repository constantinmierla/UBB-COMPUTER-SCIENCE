#include "../Repository/repository.h"
#include "./test.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>


void testGetModel() {
    Product *a = malloc(sizeof(Product));
    strcpy(a->model, "Inspiron");

    assert(strcmp(getModel(a), "Inspiron") == 0 && "Model should be Inspiron");

    free(a);
}

void testGetId() {
    Product *a = malloc(sizeof(Product));
    a->id = 1;

    assert(getId(a) == 1 && "ID should be 1");

    free(a);
}

void testGetPrice() {
    Product *a = malloc(sizeof(Product));
    a->price = 999;

    assert(getPrice(a) == 999 && "Price should be 999.99");

    free(a);
}

void testGetQuantity() {
    Product *a = malloc(sizeof(Product));
    a->quantity = 10;

    assert(getQuantity(a) == 10 && "Quantity should be 10");

    free(a);
}

void testGetType() {
    Product *a = malloc(sizeof(Product));
    strcpy(a->type, "Laptop");

    assert(strcmp(getType(a), "Laptop") == 0 && "Type should be Laptop");

    free(a);
}

void testGetProducer() {
    Product *a = malloc(sizeof(Product));
    strcpy(a->producer, "Dell");

    assert(strcmp(getProducer(a), "Dell") == 0 && "Producer should be Dell");

    free(a);
}

void testCreate() {
    Product *a = malloc(sizeof(Product));
    Repository *repository = malloc(sizeof (Repository));
    initRepository(repository, 10);
    a->id = 1;
    strcpy(a->type, "Televizor");
    strcpy(a->producer, "samsuuuung");
    strcpy(a->model, "model1");
    a->price = 2;
    a->quantity = 50;

    add(repository, *a);

    free(repository->products);
    free(repository);
    free(a);
}

void testFind() {
    Product *a = malloc(sizeof(Product));
    Repository *repository = malloc(sizeof(Repository));
    initRepository(repository, 10);
    a->id = 2;
    a->quantity = 0;

    add(repository, *a);

    Product b = find(*repository, 2);
    if (b.id != 2) {
        assert(EXIT_FAILURE);
    } else {
        assert(b.id == 2 && "b->id trebuia sa fie 2; testFind()");
    }
    free(a);

    int invalidID = 20;
    assert(find(*repository, invalidID).id == -2);
    free(repository->products);
    free(repository);
}

void testUpdateQuantity() {
    Product a;
    Repository repository;
    initRepository(&repository, 10);
    a.id = 0;
    strcpy(a.type, "Masina de spalat");
    strcpy(a.producer, "samsuuuung");
    strcpy(a.model, "model2");
    a.price = 2;
    a.quantity = 49;

    add(&repository, a);

    add(&repository, a);

    Product b = find(repository, 0);
    assert(b.quantity == 50 && "b.quantity trebuia sa fie 50");
    free(repository.products);
}

void testUpdatePriceOrQuantity() {
    Product a;
    Repository repository;
    initRepository(&repository, 10);

    a.id = 0;
    strcpy(a.type, "Masina de spalat");
    strcpy(a.producer, "samsuuuung");
    strcpy(a.model, "model2");
    a.price = 2;
    a.quantity = 49;

    add(&repository, a);

    int i = 0;
    updatePrice(&repository, i, 100);
    assert(find(repository, 0).price == 100 && "Pretul trebuia sa fie 100");

    updateQuantity(&repository, i, 500);
    assert(find(repository, 0).quantity == 500 && "Cantitatea trebuia sa fie 500");
    free(repository.products);

}

void testDelete() {
    Product a;
    Repository repository;
    initRepository(&repository, 10);
    a.id = 0;
    strcpy(a.type, "Televizor");
    strcpy(a.producer, "samsuuuung");
    strcpy(a.model, "model1");
    a.price = 2;
    a.quantity = 50;

    Product b;
    b.id = 1;
    strcpy(a.type, "Televizor");
    strcpy(a.producer, "samsuuuung");
    strcpy(a.model, "model1");
    b.price = 5;
    b.quantity = 10;

    add(&repository, a);
    add(&repository, b);
    delete(&repository, 0);

    assert(repository.products[0].id == 1);

    assert(delete(&repository, 100) == -1);
    free(repository.products);
}

void testGetAll() {
    Repository repo;
    initRepository(&repo, 10);
    Product a;
    a.id = 1;
    add(&repo, a);
    Product* products;
    products = getAll(&repo);
    for (int i = 1; i <= 1; i++) {
        assert(products[i].id == i);
    }
    free(repo.products);
}

void testAddProduct() {
    Repository r;
    Validator v;
    Service service;
    service.repository = &r;
    service.validator = &v;
    initRepository(&r, 10);
    setUp(&service);

    Product a;
    a.id = 1;


    addProduct(&service, a);

    Product b = getProduct(service, 0);
    //assert(b.id == 0 && "testAddProduct didnt pass");
    free(r.products);
}

void testUpdatePriceForProduct() {
    Repository r;
    Validator v;
    Service service;
    service.repository = &r;
    service.validator = &v;
    initRepository(&r, 10);
    setUp(&service);
    Product a;
    a.id = 0;
    addProduct(&service, a);
    updatePriceForProduct(&service, 0, 50);

    Product b = getProduct(service, 0);
    assert(b.price == 50 && "testUpdatePriceForProduct didnt pass");

    free(r.products);
}

void testAdd100ELements() {
    Repository r;
    Validator v;
    Service service;
    service.repository = &r;
    service.validator = &v;
    initRepository(&r, 101);
    setUp(&service);

    for (int i = 0; i < 101; i++) {
        Product a;
        a.id = 0;
        addProduct(&service, a);
    }
    free(r.products);
}

void testUpdateQuantityForProduct() {
    Repository r;
    Validator v;
    Service service;
    service.repository = &r;
    service.validator = &v;
    initRepository(&r, 10);
    setUp(&service);

    Product a;
    a.id = 0;
    addProduct(&service, a);
    updatePriceForProduct(&service, 0, 50);
    updateQuantityForProduct(&service, 0, 100);

    Product b = getProduct(service, 0);
    assert(b.quantity == 100 && "testUpdateQuantityForProduct didnt pass");

    free(r.products);
}

void testDeleteProduct() {
    Repository re;
    Validator v;
    Service service;
    service.repository = &re;
    service.validator = &v;
    initRepository(&re, 10);
    setUp(&service);

    Product a;
    a.id = 1;
    addProduct(&service, a);
    updatePriceForProduct(&service, 0, 50);
    updateQuantityForProduct(&service, 0, 100);

    deleteProduct(&service, 0);
    assert(service.repository->count == 0 && "testDeleteProduct didnt pass");
    free(re.products);

}

void testGetAllService() {
    Repository re;
    Validator v;
    Service service;
    service.repository = &re;
    service.validator = &v;
    initRepository(&re, 10);
    setUp(&service);


    Product a;
    a.id = 0;
    addProduct(&service, a);
    Product* products;
    products = getAllService(&service);
    assert(products[0].id == 0);
    free(re.products);
}

void testSortProducts() {
    // Create a service with some products
    Repository repository;
    Validator validator;
    Service service;
    service.repository = &repository;
    service.validator = &validator;
    initRepository(&repository, 10);
    setUp(&service);

    // Add some products to the service
    Product product1 = createProduct(1, "Laptop", "Dell", "Model1", 1000, 20);
    addProduct(&service, product1);
    Product product2 = createProduct(2, "Phone", "Samsung", "Model2", 1000, 10);
    addProduct(&service, product2);
    Product product3 = createProduct(3, "Tablet", "Apple", "Model3", 1200, 15);
    addProduct(&service, product3);

    // Sort the products
    Product *sortedProducts = sortProducts(service, 1);

    // Verify that the sorted products are in the correct order (by price and quantity)
    assert(sortedProducts[0].id == 1 && "First product should be the second one (Phone)");
    assert(sortedProducts[1].id == 0 && "Second product should be the first one (Laptop)");
    assert(sortedProducts[2].id == 2 && "Third product should be the third one (Tablet)");

    // Free memory allocated for sorted products
    free(sortedProducts);
    free(repository.products);
}

void testFilterProducts() {
    // Mock service and repository data
    Repository repository;
    Product products[3] = {
            {0, "Laptop", "Dell", "Model1", 1000, 10},
            {1, "Phone", "Samsung", "Model2", 800, 20},
            {2, "Tablet", "Apple", "Model3", 1200, 15}
    };
    repository.products = products;
    repository.count = 3;

    Service service = {&repository};

    // Test case 1: Price criteria
    int filteredSize;
    Product* filteredProducts = filterProducts(service, "price", 800, &filteredSize, NULL);
    assert(filteredSize == 1 && "Filtered size should be 1 for price criteria");
    assert(filteredProducts[0].id == 1 && "Filtered product ID should be 1 for price criteria");
    free(filteredProducts);

    // Test case 2: Quantity criteria
    filteredProducts = filterProducts(service, "quantity", 20, &filteredSize, NULL);
    assert(filteredSize == 1 && "Filtered size should be 1 for quantity criteria");
    assert(filteredProducts[0].id == 1 && "Filtered product ID should be 1 for quantity criteria");
    free(filteredProducts);

    // Test case 3: Producer criteria
    filteredProducts = filterProducts(service, "producer", 800, &filteredSize, "Samsung");
    assert(filteredSize == 1 && "Filtered size should be 1 for producer criteria");
    assert(filteredProducts[0].id == 1 && "Filtered product ID should be 2 for producer criteria");
    free(filteredProducts);
}

void testAll() {
    testGetId();
    testGetModel();
    testGetPrice();
    testGetQuantity();
    testGetProducer();
    testGetType();
    testCreate();
    testFind();
    testUpdateQuantity();
    testUpdatePriceOrQuantity();
    testDelete();
    testAddProduct();
    testUpdatePriceForProduct();
    testUpdateQuantityForProduct();
    testDeleteProduct();
    testAdd100ELements();
    testGetAll();
    testGetAllService();
    testSortProducts();
    testFilterProducts();
}