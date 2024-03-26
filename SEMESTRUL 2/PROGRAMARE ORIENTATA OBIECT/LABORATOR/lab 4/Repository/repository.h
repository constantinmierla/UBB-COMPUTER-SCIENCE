#ifndef LAB2_REPOSITORY_H
#include "../Domain/product.h"
#define LAB2_REPOSITORY_H
#define MAX_LEN 1000

typedef struct {
    Product *products;
    int count;
} Repository;

typedef struct {
    Product *actions;
    int count;
    int capacity;
} UndoList;

Product* getAll(Repository *repo);
void add(Repository *repo, Product product);
Product find(Repository repo, int id);
void updatePrice(Repository *repo, int id, int price);
void updateQuantity(Repository *repo, int id, int quantity);
int delete(Repository *repo, int id);
void initRepository(Repository *repo, int size);

#endif //LAB2_REPOSITORY_H
