#include "product.h"
#include <string.h>

int getId(Product *product) {
    return product->id;
}

char* getType(Product *product) {
    return product->type;
}

char* getProducer(Product *product) {
    return product->producer;
}

char* getModel(Product *product) {
    return product->model;
}

int getPrice(Product *product) {
    return product->price;
}

int getQuantity(Product *product) {
    return  product->quantity;
}

Product createProduct(int id, const char *type, const char *producer, const char *model, int price, int quantity) {
    Product product;
    product.id = id;
    strcpy(product.type, type);
    strcpy(product.producer, producer);
    strcpy(product.model, model);
    product.price = price;
    product.quantity = quantity;
    return product;
}
