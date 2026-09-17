#include <stdio.h>
#include <string.h>

#define OUTPUT_FILENAME "employee_hours.txt"
#define MAX_FILENAME_LEN 256

int main(void) {
  char inputFileName[MAX_FILENAME_LEN];
  FILE *inputFile;
  FILE *outputFile;
  FILE *existCheck;

  int lineNumber;
  int lineCount;
  long charCount;
  int atLineStart;
  int ch;
  int writeError;

  printf("Enter the name of the input file: ");
  fgets(inputFileName, sizeof(inputFileName), stdin);
  inputFileName[strcspn(inputFileName, "\n")] = '\0';

  inputFile = fopen(inputFileName, "r");

  printf("\n----------------------------------------\n");
  printf("Precision Payroll Services\n");
  printf("File Processing Summary\n");
  printf("----------------------------------------\n\n");

  if (inputFile == NULL) {
    printf("Error\n\n");
    printf("Unable to open file \"%s\".\n\n", inputFileName);
    printf("Please verify that the file exists and try again.\n");
    return 1;
  }

  /* The output file name is fixed; refuse to overwrite one that already exists.
   */
  existCheck = fopen(OUTPUT_FILENAME, "r");
  if (existCheck != NULL) {
    fclose(existCheck);
    fclose(inputFile);
    printf("Error\n\n");
    printf("The output file \"%s\" already exists.\n\n", OUTPUT_FILENAME);
    printf("Please remove or rename it and try again.\n");
    return 1;
  }

  outputFile = fopen(OUTPUT_FILENAME, "w");
  if (outputFile == NULL) {
    fclose(inputFile);
    printf("Error\n\n");
    printf("Unable to create file \"%s\".\n\n", OUTPUT_FILENAME);
    printf("Please check file permissions and try again.\n");
    return 1;
  }

  lineNumber = 1;
  lineCount = 0;
  charCount = 0;
  atLineStart = 1;
  writeError = 0;

  while ((ch = fgetc(inputFile)) != EOF) {
    if (atLineStart) {
      if (ch == '\n') {
        /* Blank line: skip entirely (not copied, not numbered, not counted). */
        continue;
      }
      if (fprintf(outputFile, "%d. ", lineNumber) < 0) {
        writeError = 1;
        break;
      }
      lineNumber++;
      atLineStart = 0;
    }

    if (fputc(ch, outputFile) == EOF) {
      writeError = 1;
      break;
    }

    if (ch == '\n') {
      lineCount++;
      atLineStart = 1;
    } else {
      charCount++;
    }
  }

  /* Credit a final line that has content but no trailing newline. */
  if (!writeError && !atLineStart) {
    lineCount++;
  }

  fclose(inputFile);

  /* fputc/fprintf only report a failed write once the C library actually
     flushes its internal buffer to disk, which may not happen until the
     file is closed. A disk-full condition can therefore go undetected by
     every earlier check and only surface here. */
  if (fclose(outputFile) != 0) {
    writeError = 1;
  }

  printf("%-18s: %s\n", "Input File", inputFileName);
  printf("%-18s: %s\n", "Output File", OUTPUT_FILENAME);
  printf("\n");
  printf("%-18s: %d\n", "Lines Copied", lineCount);
  printf("%-18s: %ld\n", "Characters Copied", charCount);
  printf("\n");

  if (writeError) {
    printf("The file copy did not complete successfully.\n");
  } else {
    printf("File copied successfully.\n");
  }

  return 0;
}
