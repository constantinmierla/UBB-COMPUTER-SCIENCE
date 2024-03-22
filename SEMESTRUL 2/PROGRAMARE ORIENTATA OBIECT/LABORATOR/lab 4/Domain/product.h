//
// Created by david on 3/6/24.
//
#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct {
    int id;
    char type[50];
    char producer[50];
    char model[50];
    int price;
    int quantity;
} Product;

char* getType(Product *product);
char* getProducer(Product *product);
char* getModel(Product *product);
int getId(Product *product);
int getPrice(Product *product);
int getQuantity(Product *product);
int isEqual(Product *one, Product *two);
Product createProduct(int id, const char *type, const char *producer, const char *model, int price, int quantity);

#endif
