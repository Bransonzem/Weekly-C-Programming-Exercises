# CCR5 — Downtown Parking Services

Enters hours parked per vehicle, calculates and displays that vehicle's charge immediately, repeats for as many vehicles as the employee enters, then prints a summary of the day's activity once they signal there are no more.

Includes `screenshot_tests/` with evidence for each required test case (negative hours, malformed input, daily max, zero hours, etc.).

**Run:** `gcc -Wall -Wextra -std=c11 -o ccr5 ccr5.c && ./ccr5`
