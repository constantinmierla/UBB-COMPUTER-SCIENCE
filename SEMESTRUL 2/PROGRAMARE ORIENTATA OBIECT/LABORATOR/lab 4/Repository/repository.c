#include "./repository.h"
#include <stdlib.h>


Product* getAll(Repository *repo) {
    return repo->products;
}

void initRepository(Repository *repo, int size) {
    repo->count = 0;
    repo->products = malloc(size * sizeof(Product));

    for (int i = 0; i < size; i++) {
        repo->products[i].id = -1;
    }
}

void add(Repository *repo, Product product){
    if (repo->products[product.id].id == product.id && repo->products[product.id].quantity != 0 && repo->products[product.id].price != 0) {
        repo->products[product.id].quantity++;
    } else {
        repo->products[product.id] = product;
        repo->count++;
    }
}

Product find(Repository repo, int id) {
    if (repo.products[id].id != -1 && id < repo.count) {
        return repo.products[id];
    } else {
        Product a;
        a.id = -2;
        return a;
    }
}

void updatePrice(Repository *repo, int id, int price) {
    if (repo->products[id].id == id){
        repo->products[id].price = price;
    }
}

void updateQuantity(Repository *repo, int id, int quantity) {
    if (repo->products[id].id == id) {
        repo->products[id].quantity = quantity;
    }
}


int delete(Repository *repository, int id) {
    int found = -1;
    for (int i = 0; i < repository->count; i++) {
        if (repository->products[i].id == id) {
            // Shift remaining elements to the left to remove the product
            for (int j = i; j < repository->count - 1; j++) {
                repository->products[j] = repository->products[j + 1];
            }
            found = 1;
            repository->count--;
            break;
        }
    }
    return found;
}
