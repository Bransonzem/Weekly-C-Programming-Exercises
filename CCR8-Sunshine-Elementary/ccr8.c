#include <stdio.h>

#define MAX_GRADE 120.0

/* Reads a number from the line the user types. Returns 1 for a valid
   number, 0 if input ran out (EOF), -1 for anything that isn't a clean
   number (e.g. "abc" or "84xyz"). */
int readNumber(const char *prompt, double *value) {
    int scanResult;
    int c;
    int trailingGarbage;

    printf("%s", prompt);
    scanResult = scanf("%lf", value);

    if (scanResult == EOF) {
        printf("\nNo more input was received. Exiting program.\n");
        return 0;
    }

    if (scanResult != 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
            /* discard */
        }
        return -1;
    }

    trailingGarbage = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c != ' ' && c != '\t') {
            trailingGarbage = 1;
        }
    }
    if (trailingGarbage) {
        return -1;
    }

    return 1;
}

/* Returns 1 on success, 0 on EOF. */
int getOriginalGrade(double *grade) {
    int status;

    while (1) {
        status = readNumber("Original Grade: ", grade);
        if (status == 0) {
            return 0;
        }
        if (status == -1) {
            printf("Error: Please enter a valid number.\n");
            continue;
        }
        /* Written as a negated range check so "nan" is rejected too. */
        if (!(*grade >= 0 && *grade <= MAX_GRADE)) {
            printf("Error: Grade must be between 0 and 120.\n");
            continue;
        }
        return 1;
    }
}

/* Returns 1 on success, 0 on EOF. */
int getExtraCredit(double *extraCredit) {
    int status;

    while (1) {
        status = readNumber("Extra Credit: ", extraCredit);
        if (status == 0) {
            return 0;
        }
        if (status == -1) {
            printf("Error: Please enter a valid number.\n");
            continue;
        }
        if (!(*extraCredit >= 0)) {
            printf("Error: Extra credit cannot be negative.\n");
            continue;
        }
        if (*extraCredit > MAX_GRADE) {
            printf("Error: Extra credit cannot be more than 120 points.\n");
            continue;
        }
        return 1;
    }
}

/* Returns 1 on success, 0 on EOF. */
int getConfirmation(char *answer) {
    int scanResult;
    int c;
    int trailingGarbage;

    while (1) {
        printf("Apply extra credit to this grade? (Y/N) ");
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

        if (!trailingGarbage &&
            (*answer == 'Y' || *answer == 'y' ||
             *answer == 'N' || *answer == 'n')) {
            return 1;
        }

        printf("Error: Please enter Y or N.\n");
    }
}

/* originalGrade is a pointer to const, so this function cannot change the
   original grade; the result goes out through correctedGrade instead. */
void calculateCorrectedGrade(const double *originalGrade, double extraCredit,
                             double *correctedGrade) {
    *correctedGrade = *originalGrade + extraCredit;

    if (*correctedGrade > MAX_GRADE) {
        *correctedGrade = MAX_GRADE;
    }
}

void printHeader(void) {
    printf("\n----------------------------------------\n");
    printf("Sunshine Elementary School\n");
    printf("Grade Adjustment Report\n");
    printf("----------------------------------------\n\n");
}

void displayReport(const double *originalGrade, double extraCredit,
                   const double *correctedGrade) {
    printHeader();

    printf("%-15s: %g\n\n", "Original Grade", *originalGrade);
    printf("%-15s: %g\n\n", "Extra Credit", extraCredit);
    printf("%-15s: %g\n", "Corrected Grade", *correctedGrade);

    if (*originalGrade + extraCredit > MAX_GRADE) {
        printf("\nNote: Corrected grade was capped at the maximum of 120.\n");
    }
}

void displayCancellation(const double *originalGrade) {
    printHeader();

    printf("Extra credit not applied.\n\n");
    printf("%-15s: %g\n", "Original Grade", *originalGrade);
}

int main(void) {
    double originalGrade;
    double extraCredit;
    double correctedGrade;
    char answer;

    if (!getOriginalGrade(&originalGrade)) {
        return 1;
    }

    if (!getExtraCredit(&extraCredit)) {
        return 1;
    }

    calculateCorrectedGrade(&originalGrade, extraCredit, &correctedGrade);

    if (!getConfirmation(&answer)) {
        return 1;
    }

    if (answer == 'Y' || answer == 'y') {
        displayReport(&originalGrade, extraCredit, &correctedGrade);
    } else {
        displayCancellation(&originalGrade);
    }

    return 0;
}
