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
void initOperationStack(OperationStack* stack) {
    stack->operations = malloc(sizeof(Operation) * 10);
    stack->size = 0;
    stack->capacity = 10;
}

void pushOperation(OperationStack* stack, Operation operation) {
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        stack->operations = realloc(stack->operations, sizeof(Operation) * stack->capacity);
    }
    stack->operations[stack->size++] = operation;
}

Operation popOperation(OperationStack* stack) {
    return stack->operations[--stack->size];
}

void setUp(Service *service) {
    service->id = 0;
    initOperationStack(&service->undoStack); // Add this line
}

Product* getAllService(Service *service) {
    return getAll(service->repository);
}

int addProduct(Service *service, Product product) {
    product.id = service->id;
    if (validateProduct(product) == 1) {
        add(service->repository, product);
        service->id++;

        Operation operation;
        strcpy(operation.type, "add");
        operation.before = getProduct(*service, product.id);
        operation.after = product;
        pushOperation(&service->undoStack, operation);

        return 0;
    } else {
        return -1;
    }
}

int updatePriceForProduct(Service *service, int id, int price) {
    Operation operation;
    strcpy(operation.type, "update");
    operation.before = getProduct(*service, id);
    operation.after = getProduct(*service, id);
    operation.after.price = price;
    pushOperation(&service->undoStack, operation);

    updatePrice(service->repository, id, price);
    return 0;
}

int updateQuantityForProduct(Service *service, int id, int quantity) {
    Operation operation;
    strcpy(operation.type, "update");
    operation.before = getProduct(*service, id);
    operation.after = getProduct(*service, id);
    operation.after.quantity = quantity;
    pushOperation(&service->undoStack, operation);
    updateQuantity(service->repository, id, quantity);
    return 0;
}

int deleteProduct(Service *service, int id) {
    Product product = find(*service->repository, id);
    if (product.id == -1) {
        return -1;
    }

    Operation operation;
    strcpy(operation.type, "delete");
    operation.before = product;
    operation.after = product;
    pushOperation(&service->undoStack, operation);

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

int undo(Service *service) {
    if (service->undoStack.size == 0) {
        return -1;
    }

    Operation operation;
    do {
        operation = popOperation(&service->undoStack); // Pop the operation
    } while (service->undoStack.size > 0 && strcmp(operation.type, "undo") == 0);

    if (strcmp(operation.type, "undo") == 0) {
        // If we've popped all operations and the last one is still an undo, there's nothing to undo
        return -1;
    }

    int result = -1;
    if (strcmp(operation.type, "add") == 0) {
        result = deleteProduct(service, operation.after.id);
        if (result == -1) {
            pushOperation(&service->undoStack, operation); // Push the operation back if it failed
        }
    } else if (strcmp(operation.type, "delete") == 0) {
        result = addProduct(service, operation.before);
    } else if (strcmp(operation.type, "update") == 0) {
        updatePriceForProduct(service, operation.before.id, operation.before.price);
        result = updateQuantityForProduct(service, operation.before.id, operation.before.quantity);
    }

    return result;
}
