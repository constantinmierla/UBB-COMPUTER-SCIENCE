#include <stdlib.h>
#include <string.h>
#include "./service.h"

int compareProducts(Product productA, Product productB) {
    // Compare by price
    if (productA.price != productB.price) {
        return productA.price - productB.price;
    }

    // If prices are equal, compare by quantity
    return productA.quantity - productB.quantity;
}


void setUp(Service *service) {
    service->id = 0;
}

Product* getAllService(Service *service) {
    return getAll(service->repository);
}

int addProduct(Service *service, Product product) {
    product.id = service->id;
    if (validateProduct(product) == 1) {
        add(service->repository, product);
        service->id++;
        return 0;
    } else {
        return -1;
    }
}

int updatePriceForProduct(Service *service, int id, int price) {
    updatePrice(service->repository, id, price);
    return 0;
}

int updateQuantityForProduct(Service *service, int id, int quantity) {
    updateQuantity(service->repository, id, quantity);
    return 0;
}

int deleteProduct(Service *service, int id) {
    delete(service->repository, id);
    return 0;
}

Product getProduct(Service service, int id) {
    Product a = find(*service.repository, id);
    return a;
}

void customSortProducts(Product* products, int size, int (*compare)(Product productA, Product productB), int reverse) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            int comparisonResult = compare(products[j], products[j + 1]);
            if ((reverse == 1 && comparisonResult > 0) || (reverse == 2 && comparisonResult < 0)) {
                // Swap products
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

Product *sortProducts(Service service, int reverse) {
    Product* products = getAllService(&service);
    int size = service.repository->count;
    // Allocate memory for the copy of sorted products
    Product *sortedProducts = malloc(size * sizeof(Product));
    // Copy the pointers from the original array to the copy
    memcpy(sortedProducts, products, size * sizeof(Product));

    // Sort the copied array
    customSortProducts(sortedProducts, size, compareProducts, reverse);

    return sortedProducts;
}

Product* filterProducts(Service service, const char* criteria, int value, int* filteredSize, char* producer) {
    // Allocate memory for the filtered products
    Product* products = getAllService(&service);
    int size = service.repository->count;
    Product* filteredProducts = malloc(size * sizeof(Product));

    *filteredSize = 0;

    for (int i = 0; i < size; ++i) {
        if (strcmp(criteria, "price") == 0 && products[i].price == value) {
            filteredProducts[(*filteredSize)++] = products[i];
        } else if (strcmp(criteria, "quantity") == 0 && products[i].quantity == value) {
            filteredProducts[(*filteredSize)++] = products[i];
        } else if (strcmp(criteria, "producer") == 0 && strcmp(products[i].producer, producer) == 0) {
            filteredProducts[(*filteredSize)++] = products[i];
        }
    }

    filteredProducts = realloc(filteredProducts, (*filteredSize) * sizeof(Product));

    return filteredProducts;
}