#include <stdio.h>

/* Persists for the whole program, per the customer's own note that the
   overall inventory must remain available throughout the entire run. */
int currentInventory;

/* Returns 1 on success, 0 if input ran out (EOF) before a valid value
   was entered. */
int getCurrentInventory(void) {
    int scanResult;
    int c;
    int trailingGarbage;

    while (1) {
        printf("Current Inventory: ");
        scanResult = scanf("%d", &currentInventory);

        if (scanResult == EOF) {
            printf("\nNo more input was received. Exiting program.\n");
            return 0;
        }

        if (scanResult != 1) {
            while ((c = getchar()) != '\n' && c != EOF) {
                /* discard */
            }
            printf("Error: Please enter a valid whole number.\n");
            continue;
        }

        trailingGarbage = 0;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c != ' ' && c != '\t') {
                trailingGarbage = 1;
            }
        }
        if (trailingGarbage) {
            printf("Error: Please enter a valid whole number.\n");
            continue;
        }

        if (currentInventory < 0) {
            printf("Error: Inventory quantity cannot be negative.\n");
            continue;
        }

        break; /* valid */
    }

    return 1;
}

/* Returns 1 on success (purchased quantity written to *purchased), 0 if
   input ran out (EOF) before a valid value was entered. */
int getPurchaseQuantity(int inventory, int *purchased) {
    int scanResult;
    int c;
    int trailingGarbage;

    while (1) {
        printf("Products Purchased: ");
        scanResult = scanf("%d", purchased);

        if (scanResult == EOF) {
            printf("\nNo more input was received. Exiting program.\n");
            return 0;
        }

        if (scanResult != 1) {
            while ((c = getchar()) != '\n' && c != EOF) {
                /* discard */
            }
            printf("Error: Please enter a valid whole number.\n");
            continue;
        }

        trailingGarbage = 0;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c != ' ' && c != '\t') {
                trailingGarbage = 1;
            }
        }
        if (trailingGarbage) {
            printf("Error: Please enter a valid whole number.\n");
            continue;
        }

        if (*purchased <= 0) {
            printf("Error: Purchase quantity must be greater than zero.\n");
            continue;
        }

        if (*purchased > inventory) {
            printf("Error: Not enough inventory to complete this purchase.\n");
            continue;
        }

        break; /* valid */
    }

    return 1;
}

/* Returns 1 on success (answer written to *answer), 0 if input ran out
   (EOF) before a valid value was entered. */
int getConfirmation(char *answer) {
    int scanResult;
    int c;
    int trailingGarbage;

    while (1) {
        printf("Confirm this sale? (Y/N) ");
        scanResult = scanf(" %c", answer);

        if (scanResult == EOF) {
            printf("\nNo more input was received. Exiting program.\n");
            return 0;
        }

        trailingGarbage = 0;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c != ' ' && c != '\t') {
                trailingGarbage = 1;
            }
        }

        if (!trailingGarbage && scanResult == 1 &&
            (*answer == 'Y' || *answer == 'y' ||
             *answer == 'N' || *answer == 'n')) {
            break;
        }

        printf("Error: Please enter Y or N.\n");
    }

    return 1;
}

void processSale(int purchased) {
    currentInventory = currentInventory - purchased;
}

void displaySummary(int inventoryBefore, int sold) {
    printf("\n----------------------------------------\n");
    printf("Green Valley Supply Company\n");
    printf("Inventory Transaction Summary\n");
    printf("----------------------------------------\n\n");

    printf("%-22s: %d\n\n", "Inventory Before Sale", inventoryBefore);
    printf("%-22s: %d\n\n", "Products Sold", sold);
    printf("%-22s: %d\n", "Inventory Remaining", currentInventory);
}

void displayCancellation(int inventoryBefore) {
    printf("\n----------------------------------------\n");
    printf("Green Valley Supply Company\n");
    printf("Inventory Transaction Summary\n");
    printf("----------------------------------------\n\n");

    printf("Sale cancelled. Inventory unchanged.\n\n");
    printf("%-22s: %d\n", "Inventory Remaining", inventoryBefore);
}

int main(void) {
    int inventoryBefore;
    int purchased;
    char confirmAnswer;

    if (!getCurrentInventory()) {
        return 1;
    }
    inventoryBefore = currentInventory;

    if (!getPurchaseQuantity(currentInventory, &purchased)) {
        return 1;
    }

    if (!getConfirmation(&confirmAnswer)) {
        return 1;
    }

    if (confirmAnswer == 'Y' || confirmAnswer == 'y') {
        processSale(purchased);
        displaySummary(inventoryBefore, purchased);
    } else {
        displayCancellation(inventoryBefore);
    }

    return 0;
}
