# CCR4 — Precision Payroll Services

Reads an input text file of employee work-hour records line by line, copies it into a new numbered output file, and prints a summary of the operation — or a clear error if the input file can't be opened. First CCR to use file I/O.

Includes `employee_hours.txt` / `payroll.txt` as sample input, and `screenshot_tests/` with evidence for each required test case (missing file, filename collision, blank lines, read-only output, etc.).

**Run:** `gcc -Wall -Wextra -std=c11 -o ccr4 ccr4.c && ./ccr4`
