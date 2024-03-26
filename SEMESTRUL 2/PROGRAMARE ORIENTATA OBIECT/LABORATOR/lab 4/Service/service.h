#ifndef LAB2_SERVICE_H
#define LAB2_SERVICE_H
#include "Repository/repository.h"
#include "Domain/validator.h"

typedef struct {
    char type[10]; // "add", "update", "delete"
    Product before;
    Product after;
} Operation;

typedef struct {
    Operation* operations;
    int size;
    int capacity;
} OperationStack;

typedef struct {
    Repository *repository;
    Validator *validator;
    int id;
    OperationStack undoStack;
} Service;

void initOperationStack(OperationStack* stack);
void pushOperation(OperationStack* stack, Operation operation);
Operation popOperation(OperationStack* stack);
Product* getAllService(Service *service);
void setUp(Service *service);
int addProduct(Service *service, Product product);
int updatePriceForProduct(Service *service, int id, int price);
int updateQuantityForProduct(Service *service, int id, int quantity);
int deleteProduct(Service *service, int id);
Product *sortProducts(Service service, int reverse);
Product getProduct(Service service, int id);
Product *filterProducts(Service service, const char *criteria, int value, int *filteredSize, char* producer);
int undo(Service *service);
#endif //LAB2_SERVICE_H