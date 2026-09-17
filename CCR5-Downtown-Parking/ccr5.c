#include <stdio.h>

#define RATE_PER_HOUR 2.00
#define DAILY_MAX 50.00

int main(void) {
    int vehicleNumber;
    int vehiclesProcessed;
    double totalRevenue;
    double hoursParked;
    double charge;
    double averageFee;
    char moreVehicles;
    int scanResult;
    int c;
    int trailingGarbage;

    printf("----------------------------------------\n");
    printf("Downtown Parking Services\n");
    printf("Parking Summary\n");
    printf("----------------------------------------\n\n");

    vehicleNumber = 1;
    vehiclesProcessed = 0;
    totalRevenue = 0.0;

    while (1) {
        /* ---- Get a valid hours-parked value for this vehicle ---- */
        while (1) {
            printf("Vehicle %d Hours Parked: ", vehicleNumber);
            scanResult = scanf("%lf", &hoursParked);

            if (scanResult == EOF) {
                printf("\nNo more input was received. Exiting program.\n");
                return 1;
            }

            if (scanResult != 1) {
                /* Non-numeric entry: discard the bad line so it is never re-read. */
                while ((c = getchar()) != '\n' && c != EOF) {
                    /* discard */
                }
                printf("Error: Please enter a valid number of hours.\n");
                continue;
            }

            /* A number matched, but reject trailing garbage like "2.5xyz" —
               only whitespace is allowed between the number and the newline. */
            trailingGarbage = 0;
            while ((c = getchar()) != '\n' && c != EOF) {
                if (c != ' ' && c != '\t') {
                    trailingGarbage = 1;
                }
            }
            if (trailingGarbage) {
                printf("Error: Please enter a valid number of hours.\n");
                continue;
            }

            if (hoursParked < 0) {
                printf("Error: Parking time cannot be negative.\n");
                continue;
            }

            break; /* valid */
        }

        charge = hoursParked * RATE_PER_HOUR;
        if (charge > DAILY_MAX) {
            charge = DAILY_MAX;
        }

        printf("Vehicle %d Charge : $%.2f\n", vehicleNumber, charge);

        vehiclesProcessed++;
        totalRevenue += charge;
        vehicleNumber++;

        /* ---- Ask whether there are more vehicles ---- */
        while (1) {
            printf("More vehicles? ");
            scanResult = scanf(" %c", &moreVehicles);

            if (scanResult == EOF) {
                printf("\nNo more input was received. Exiting program.\n");
                return 1;
            }

            trailingGarbage = 0;
            while ((c = getchar()) != '\n' && c != EOF) {
                if (c != ' ' && c != '\t') {
                    trailingGarbage = 1;
                }
            }

            if (!trailingGarbage && scanResult == 1 &&
                (moreVehicles == 'Y' || moreVehicles == 'y' ||
                 moreVehicles == 'N' || moreVehicles == 'n')) {
                break;
            }

            printf("Error: Please enter Y or N.\n");
        }

        if (moreVehicles == 'N' || moreVehicles == 'n') {
            break;
        }
    }

    if (vehiclesProcessed > 0) {
        averageFee = totalRevenue / vehiclesProcessed;
    } else {
        averageFee = 0.0;
    }

    printf("\n----------------------------------------\n\n");
    printf("%-19s: %d\n\n", "Vehicles Processed", vehiclesProcessed);
    printf("%-19s: $%.2f\n\n", "Total Revenue", totalRevenue);
    printf("%-19s: $%.2f\n", "Average Parking Fee", averageFee);

    return 0;
}
