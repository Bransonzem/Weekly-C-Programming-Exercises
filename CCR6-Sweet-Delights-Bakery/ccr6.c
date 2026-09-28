#include <stdio.h>

#define TAX_RATE 0.06
#define MAX_ORDER 5000.00

double roundToNickel(double value) {
    return ((int)(value * 20.0 + 0.5)) / 20.0;
}

double calculateDiscount(double orderAmount, double discountPercent) {
    double discount;

    discount = orderAmount * (discountPercent / 100.0);

    return roundToNickel(discount);
}

double calculateSalesTax(double orderAmount) {
    double tax;

    tax = orderAmount * TAX_RATE;

    return roundToNickel(tax);
}

double calculateFinalTotal(double orderAmount, double discount, double salesTax) {
    return orderAmount + salesTax - discount;
}

int main(void) {
    double orderAmount;
    double discountPercent;
    double discount;
    double salesTax;
    double finalTotal;
    int scanResult;
    int c;
    int trailingGarbage;
    char discountLabel[32];

    /* ---- Get a valid order amount ---- */
    while (1) {
        printf("Order Amount: $");
        scanResult = scanf("%lf", &orderAmount);

        if (scanResult == EOF) {
            printf("\nNo more input was received. Exiting program.\n");
            return 1;
        }

        if (scanResult != 1) {
            /* Non-numeric entry: discard the bad line so it is never re-read. */
            while ((c = getchar()) != '\n' && c != EOF) {
                /* discard */
            }
            printf("Error: Please enter a valid dollar amount.\n");
            continue;
        }

        /* A number matched, but reject trailing garbage like "25.00abc" —
           only whitespace is allowed between the number and the newline. */
        trailingGarbage = 0;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c != ' ' && c != '\t') {
                trailingGarbage = 1;
            }
        }
        if (trailingGarbage) {
            printf("Error: Please enter a valid dollar amount.\n");
            continue;
        }

        if (orderAmount < 0) {
            printf("Error: Order amount cannot be negative.\n");
            continue;
        }

        if (orderAmount > MAX_ORDER) {
            printf("Error: Order amount cannot exceed $5000.00.\n");
            continue;
        }

        break; /* valid */
    }

    orderAmount = roundToNickel(orderAmount);

    /* ---- Get the discount percentage from the customer's coupon, if any ---- */
    while (1) {
        printf("Discount Percentage from Coupon (0 if none): ");
        scanResult = scanf("%lf", &discountPercent);

        if (scanResult == EOF) {
            printf("\nNo more input was received. Exiting program.\n");
            return 1;
        }

        if (scanResult != 1) {
            while ((c = getchar()) != '\n' && c != EOF) {
                /* discard */
            }
            printf("Error: Please enter a valid percentage.\n");
            continue;
        }

        trailingGarbage = 0;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c != ' ' && c != '\t') {
                trailingGarbage = 1;
            }
        }
        if (trailingGarbage) {
            printf("Error: Please enter a valid percentage.\n");
            continue;
        }

        if (discountPercent < 0 || discountPercent > 100) {
            printf("Error: Discount percentage must be between 0 and 100.\n");
            continue;
        }

        break; /* valid */
    }

    discount = calculateDiscount(orderAmount, discountPercent);
    salesTax = calculateSalesTax(orderAmount);
    finalTotal = calculateFinalTotal(orderAmount, discount, salesTax);

    printf("\n----------------------------------------\n");
    printf("Sweet Delights Bakery\n");
    printf("Customer Receipt\n");
    printf("----------------------------------------\n\n");

    printf("%-15s: $%.2f\n\n", "Original Order", orderAmount);

    if (discountPercent > 0) {
        sprintf(discountLabel, "Discount (%.0f%%)", discountPercent);
    } else {
        sprintf(discountLabel, "Discount");
    }
    printf("%-15s: $%.2f\n\n", discountLabel, discount);

    printf("%-15s: $%.2f\n\n", "Sales Tax", salesTax);
    printf("-------------------------------\n\n");
    printf("%-15s: $%.2f\n", "Final Total", finalTotal);

    return 0;
}
