#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_HOURS 5
#define MAX_LINE_LEN 100

void readLineOrExit(char *buffer, int size);
int getValidCupCount(int hourNumber);
void printTiedHours(const int *cups, int value, int count);

int main(void) {
  int cups[NUM_HOURS];
  int i;
  int total;
  float average;
  int roundedAverage;
  int maxValue, minValue;
  int maxCount, minCount;

  for (i = 0; i < NUM_HOURS; i++) {
    cups[i] = getValidCupCount(i + 1);
  }

  total = 0;
  for (i = 0; i < NUM_HOURS; i++) {
    total += cups[i];
  }

  average = (float)total / NUM_HOURS;
  roundedAverage = (int)(average + 0.5f);

  maxValue = cups[0];
  minValue = cups[0];
  for (i = 1; i < NUM_HOURS; i++) {
    if (cups[i] > maxValue) {
      maxValue = cups[i];
    }
    if (cups[i] < minValue) {
      minValue = cups[i];
    }
  }

  maxCount = 0;
  minCount = 0;
  for (i = 0; i < NUM_HOURS; i++) {
    if (cups[i] == maxValue) {
      maxCount++;
    }
    if (cups[i] == minValue) {
      minCount++;
    }
  }

  printf("\n----------------------------------------\n");
  printf("Sunrise Coffee Company\n");
  printf("Daily Sales Summary\n");
  printf("----------------------------------------\n\n");

  printf("Sales by Hour\n\n");
  for (i = 0; i < NUM_HOURS; i++) {
    printf("Hour %d : %d\n", i + 1, cups[i]);
  }

  printf("\nTotal Cups Sold : %d\n", total);
  printf("Average per Hour: %d\n\n", roundedAverage);

  printf("Busiest Hour : ");
  printTiedHours(cups, maxValue, maxCount);

  printf("Slowest Hour : ");
  printTiedHours(cups, minValue, minCount);

  return 0;
}

/* Reads one line of input into buffer. If input ends unexpectedly (EOF),
   prints an error and exits the program instead of looping forever.
   If the line was longer than the buffer, discards the leftover
   characters so they are not mistaken for the next input. */
void readLineOrExit(char *buffer, int size) {
  int c;

  if (fgets(buffer, size, stdin) == NULL) {
    printf("\nNo more input was received. Exiting program.\n");
    exit(1);
  }

  if (strchr(buffer, '\n') == NULL) {
    while ((c = getchar()) != '\n' && c != EOF) {
      /* discard the rest of the oversized line */
    }
  }
}

/* Prompts for the cup count of one hour, re-prompting until a whole
   number of 0 or more is entered with no extra characters
   (e.g. "12abc" or "-5" is rejected). There is no upper limit. */
int getValidCupCount(int hourNumber) {
  char buffer[MAX_LINE_LEN];
  char *endptr;
  long value = 0;
  int valid;

  do {
    valid = 1;

    printf("Enter cups sold during Hour %d: ", hourNumber);
    readLineOrExit(buffer, sizeof(buffer));

    value = strtol(buffer, &endptr, 10);

    if (endptr == buffer) {
      /* No digits were found at all. */
      valid = 0;
    } else {
      /* Only trailing whitespace is allowed after the number. */
      while (isspace((unsigned char)*endptr)) {
        endptr++;
      }
      if (*endptr != '\0') {
        valid = 0;
      }
    }

    if (valid && value < 0) {
      valid = 0;
    }

    if (!valid) {
      printf("Invalid entry. Please enter a whole number of 0 or more.\n");
    }
  } while (!valid);

  return (int)value;
}

/* Prints every hour whose cup count matches value, separated by commas
   and in ascending hour order, followed by the shared cup count. Used
   for both the busiest and slowest hour lines so ties are fully
   reported rather than showing only the first match. */
void printTiedHours(const int *cups, int value, int count) {
  int i;
  int printed;

  printed = 0;
  for (i = 0; i < NUM_HOURS; i++) {
    if (cups[i] == value) {
      if (printed > 0) {
        printf(", ");
      }
      printf("Hour %d", i + 1);
      printed++;
      if (printed == count) {
        break;
      }
    }
  }
  printf(" (%d cups)\n", value);
}
