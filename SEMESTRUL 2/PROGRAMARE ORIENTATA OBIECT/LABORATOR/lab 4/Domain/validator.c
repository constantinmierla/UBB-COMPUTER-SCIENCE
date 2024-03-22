#include "./validator.h"

int validateProduct(Product product) {
    if (product.id < 10)
        return 1;
    else {
        return 0;
    }
}