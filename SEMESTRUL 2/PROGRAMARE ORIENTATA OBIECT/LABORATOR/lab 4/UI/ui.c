#include <stdio.h>
#include <stdlib.h>
#include "./ui.h"

#define BUFFER_SIZE 100

void showMenu() {
    printf("1. Adauga Produs\n");
    printf("2. Actualizeaza Produs\n");
    printf("3. Sterge Produs\n");
    printf("4. Lista Produse\n");
    printf("5. Filtrare produse dupa criteriu (producator, pret, cantitate)\n");
    printf("6. Exit\n");
}

void uiAdaugaProdus(Service *service) {
    Product product;

    product.id = 0;

    printf("Enter the type of the product: ");
    if (scanf("%49s", product.type) != 1) {
        fprintf(stderr, "Error: Failed to read type\n");
        return;
    }

    printf("Enter the producer of the product: ");
    if (scanf("%49s", product.producer) != 1) {
        fprintf(stderr, "Error: Failed to read producer\n");
        return;
    }

    printf("Enter the model of the product: ");
    if (scanf("%49s", product.model) != 1) {
        fprintf(stderr, "Error: Failed to read model\n");
        return;
    }

    printf("Enter the price of the product: ");
    if (scanf("%d", &product.price) != 1) {
        fprintf(stderr, "Error: Invalid price\n");
        return;
    }

    printf("Enter the quantity of the product: ");
    if (scanf("%d", &product.quantity) != 1) {
        fprintf(stderr, "Error: Invalid quantity\n");
        return;
    }

    // Call the addProduct function to add the product to the service
    addProduct(service, product);
}

void uiActualizareProdus(Service *service) {
    char* option;
    option = malloc(100 * sizeof (char));

    printf("Alegeti id ul produsului pe care vreti sa il actualizati: ");
    scanf("%s", option);
    int num = atoi(option);
    int id = num;
    Product finded =  find(*service->repository, num);
    if (finded.id == -1) {
        printf("Produsul nu a fost gasit\n");
    } else {
        printf("Alegeti dupa ce actualizati produsul\n1. Doar dupa pret\n2. Doar dupa cantitate\n3. Dupa pret si cantitate\nOptiune: ");
        scanf("%s", option);
        printf("\n");

        num = atoi(option);

        if (num == 1) {
            int newPrice = 0;
            printf("Introduceti pretul cu care modificati: ");
            scanf("%d", &newPrice);
            updatePriceForProduct(service, id, newPrice);
        } else if (num == 2) {
            int newQuantity = 0;
            printf("Introduceti cantitatea cu care modificati: ");
            scanf("%d", &newQuantity);
            updateQuantityForProduct(service, id, newQuantity);
        } else if (num == 3) {
            int newPrice = 0;
            printf("Introduceti pretul cu care modificati: ");
            scanf("%d", &newPrice);
            printf("\n");
            int newQuantity = 0;
            printf("Introduceti cantitatea cu care modificati: ");
            scanf("%d", &newQuantity);

            updatePriceForProduct(service, id, newPrice);
            updateQuantityForProduct(service, id, newQuantity);
        } else {
            printf("Optiune invalida");
        }
    }

}

void uiStergereProdus(Service *service) {
    int id;

    char* option = malloc(100 * sizeof (char *));

    printf("Introduceti id-ul produsului pe car vreti sa l stergeti: ");
    scanf("%s", option);

    id = atoi(option);
    Product finded = find(*service->repository, id);

    if (finded.id == -1) {
        printf("Produsul nu a fost gasit");
    } else {
        deleteProduct(service, id);
    }

    free(option);

}

void uiVizualizareProduse(Service *service) {
    int option;

    printf("Alegeti tipul de sortare (1 : crescator/2 : descrescator): ");
    scanf("%d", &option);

    Product *sortedProducts = sortProducts(*service, option);
    if (sortedProducts == NULL) {
        printf("There are no products in the service.\n");
        return;
    }

    printf("List of products:\n");

    for (int i = 0; i < service->repository->count; i++) {
        printf("ID: %d, Type: %s, Producer: %s, Model: %s, Price: %d, Quantity: %d\n",
        sortedProducts[i].id, sortedProducts[i].type, sortedProducts[i].producer, sortedProducts[i].model,
        sortedProducts[i].price, sortedProducts[i].quantity);
    }

    free(sortedProducts);

}

void uiListaProduseFiltrate(Service *service){
    Product *filteredProducts;

    printf("Alegeti criteriul dupa care se filtreaza:\n1. Pret\n2. Cantitate\n3. Producator\nOptiune: ");
    int num;
    scanf("%d", &num);

    int filteredSize = 0;
    if (num == 1) {
        printf("Introduceti pretul dupa care filtrati: ");
        int price = 0;
        scanf("%d", &price);
        filteredProducts = filterProducts(*service, "price", price, &filteredSize, "");
    } else if (num == 2) {
        printf("Introduceti cantitatea dupa care filtrati: ");
        int quantity = 0;
        scanf("%d", &quantity);
        filteredProducts = filterProducts(*service, "quantity", quantity, &filteredSize, "");
    } else {
        printf("Introduceti producatorul dupa care filtrati: ");
        char *producer = NULL;
        producer = malloc(BUFFER_SIZE * sizeof (char));
        scanf("%s", producer);
        filteredProducts = filterProducts(*service, "producer", 0, &filteredSize, producer);
        free(producer);
    }

    for (int i = 0; i < filteredSize; i++) {
        printf("ID: %d, Type: %s, Producer: %s, Model: %s, Price: %d, Quantity: %d\n",
               filteredProducts[i].id, filteredProducts[i].type, filteredProducts[i].producer, filteredProducts[i].model,
               filteredProducts[i].price, filteredProducts[i].quantity);
    }
}

void run(Console ui) {

    char choice[50];
    int num;
    do {
        showMenu();
        printf("Alege o optiune: ");
        scanf("%s", &choice);
        char *endptr = NULL;
        num = strtol(&choice, &endptr, 10);

        switch (num) {
            case 1:
                uiAdaugaProdus(ui.service);
                break;
            case 2:
                uiActualizareProdus(ui.service);
                break;
            case 3:
                uiStergereProdus(ui.service);
                break;
            case 4:
                uiVizualizareProduse(ui.service);
                break;
            case 5:
                uiListaProduseFiltrate(ui.service);
                break;
            case 6:
                break;
            case 7:
                printf("Optiune invalida\n");
                break;
        }
    } while (num != 6);
}

