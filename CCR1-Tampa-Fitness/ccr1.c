
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_LINE_LEN 100

void getValidName(char *name);
int getValidAge(void);
float getValidFee(void);
void printReceipt(const char *name, int age, float fee);

int main(void) {
  char name[MAX_NAME_LEN];
  int age;
  float fee;

  getValidName(name);
  age = getValidAge();
  fee = getValidFee();

  printReceipt(name, age, fee);

  return 0;
}

/* Prompts for a customer name, re-prompting until the name contains only
   letters and spaces and has at least one non-space character. */
void getValidName(char *name) {
  char buffer[MAX_LINE_LEN];
  int valid;
  int i, len;
  int start, end;

  do {
    valid = 1;

    printf("Enter customer's first name: ");
    fgets(buffer, sizeof(buffer), stdin);

    /* Remove the trailing newline left by fgets, if present. */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
      len--;
    }

    /* Find the first and last non-space characters. */
    start = 0;
    while (start < len && buffer[start] == ' ') {
      start++;
    }

    end = len - 1;
    while (end >= start && buffer[end] == ' ') {
      end--;
    }

    if (start > end) {
      /* Name was empty or contained only spaces. */
      valid = 0;
    } else {
      for (i = 0; i < len; i++) {
        if (!isalpha((unsigned char)buffer[i]) && buffer[i] != ' ') {
          valid = 0;
          break;
        }
      }
    }

    if (!valid) {
      printf("Invalid name. Names may contain only letters and spaces, "
             "and cannot be empty.\n");
    }
  } while (!valid);

  len = end - start + 1;
  strncpy(name, &buffer[start], len);
  name[len] = '\0';
}

/* Prompts for an age, re-prompting until a whole number from 0 to 120
   is entered. */
int getValidAge(void) {
  char buffer[MAX_LINE_LEN];
  int age;
  int fieldsRead;

  while (1) {
    printf("Enter customer's age: ");
    fgets(buffer, sizeof(buffer), stdin);

    fieldsRead = sscanf(buffer, "%d", &age);

    if (fieldsRead == 1 && age >= 0 && age <= 120) {
      break;
    }

    printf("Invalid age. Please enter a whole number between 0 and 120.\n");
  }

  return age;
}

/* Prompts for a monthly membership fee, re-prompting until a value of
   $0.00 or more is entered. */
float getValidFee(void) {
  char buffer[MAX_LINE_LEN];
  float fee;
  int fieldsRead;

  while (1) {
    printf("Enter monthly membership fee: ");
    fgets(buffer, sizeof(buffer), stdin);

    fieldsRead = sscanf(buffer, "%f", &fee);

    if (fieldsRead == 1 && fee >= 0.0f) {
      break;
    }

    printf("Invalid fee. Please enter an amount of $0.00 or more.\n");
  }

  return fee;
}

/* Displays the formatted membership receipt. */
void printReceipt(const char *name, int age, float fee) {
  printf("\n------------------------------\n");
  printf(" Tampa Fitness Center\n");
  printf(" Membership Receipt\n");
  printf("------------------------------\n\n");

  printf("Customer: %s\n\n", name);
  printf("Age: %d\n\n", age);
  printf("Monthly Fee: $%.2f\n\n", fee);

  if (age >= 65) {
    printf("Status: Senior Program\n\n");
  } else {
    printf("Status: Standard Membership\n\n");
  }

  printf("Thank you for joining!\n");
}
