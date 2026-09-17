#include <stdio.h>

int main(void) {
  int age;
  int ageValid;
  int scanResult;
  int c;

  char dayLetter;
  int dayValid;

  /* ---- Get a valid age, retrying on any invalid entry ---- */
  do {
    ageValid = 1;

    printf("Enter customer's age: ");
    scanResult = scanf("%d", &age);

    if (scanResult == EOF) {
      printf("\nNo more input was received. Exiting program.\n");
      return 1;
    }

    if (scanResult != 1) {
      /* Non-numeric entry: discard the bad line so it is never re-read. */
      while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
      }
      ageValid = 0;
    } else {
      /* A number matched, but reject trailing garbage like "25xyz" —
         only whitespace is allowed between the number and the newline. */
      int trailingGarbage = 0;
      while ((c = getchar()) != '\n' && c != EOF) {
        if (c != ' ' && c != '\t') {
          trailingGarbage = 1;
        }
      }
      if (trailingGarbage) {
        ageValid = 0;
      } else if (age < 1 || age > 100) {
        ageValid = 0;
      }
    }

    if (!ageValid) {
      printf("Error: The customer's age is invalid. Please enter a whole "
             "number from 1 to 100.\n");
    }
  } while (!ageValid);

  /* ---- Get a valid day type: W = Weekday, E = Weekend ---- */
  do {
    dayValid = 1;

    printf("Enter day type (W = Weekday, E = Weekend): ");
    scanResult = scanf(" %c", &dayLetter);

    if (scanResult == EOF) {
      printf("\nNo more input was received. Exiting program.\n");
      return 1;
    }

    if (scanResult != 1) {
      dayValid = 0;
    } else {
      /* A character matched, but reject trailing garbage like "WX" or
         "Weekday" — only whitespace is allowed after the one character. */
      int trailingGarbage = 0;
      while ((c = getchar()) != '\n' && c != EOF) {
        if (c != ' ' && c != '\t') {
          trailingGarbage = 1;
        }
      }

      if (trailingGarbage) {
        dayValid = 0;
      } else if (dayLetter == 'W' || dayLetter == 'w' || dayLetter == 'E' ||
                 dayLetter == 'e') {
        dayValid = 1;
      } else {
        dayValid = 0;
      }
    }

    if (!dayValid) {
      printf("Error: The day type is invalid. Please enter W for Weekday or E "
             "for Weekend.\n");
    }
  } while (!dayValid);

  /* ---- Both age and day type are now valid: display the report ---- */
  printf("\n----------------------------------------\n");
  printf("Grand Cinema Theater\n");
  printf("Ticket Classification\n");
  printf("----------------------------------------\n\n");

  printf("Customer Age : %d\n", age);

  if (dayLetter == 'W' || dayLetter == 'w') {
    printf("Day Type     : Weekday\n");
  } else {
    printf("Day Type     : Weekend\n");
  }

  printf("\n");

  if (age <= 12) {
    printf("Ticket Type  : Child Ticket\n");
  } else if (age <= 59) {
    printf("Ticket Type  : Adult Ticket\n");
  } else {
    printf("Ticket Type  : Senior Ticket\n");
  }

  return 0;
}
