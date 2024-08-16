#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define L1 3
#define L2 5
#include "password.h"


void password(char *, int, int *, int *, int *);

int main(int argc, char *argv[]) {
    int n, i, level, letter[26], digit[10];
    char pass[L2];

    // Max number of letter and digit

    n = atoi(argv[1]);
    if (n > L1) {
        fprintf(stderr, "n > L1.\n");
        return (0);
    }

    // Initialize occurrence array
    for (i=0; i<26; i++) {
        letter[i]=0;
    }
    for (i=0; i<10; i++) {
        digit[i]=0;
    }

    // Recursion level
    level = 0;

    // Calling the recursive function
    password(pass, level, letter, digit, n);
    return 1;
}

void password(char *pass, int level, int *letter, int *digit, int n) {
    static int stop = 0, STOP = 1000;
    int i;

    if (level == L2) {
        for (i = 0; i < L2; i++) {
            fprintf(stdout, "%c", pass[i]);
        }
        fprintf(stdout, "\n");

        stop++;
        if (stop >= STOP) {
            fprintf(stderr, "End program after %d password.\n", stop);
            exit(EXIT_FAILURE);
        }

        return;
    }

    if (level < L1) {
        // Select a letter
        for (i = 0; i < 26; i++) {
            if (letter[i] < n) {
                letter[i]++;
                pass[level] = (char) ((int) 'a' + i);
                password(pass, level + 1, letter, digit, n);
                letter[i]--;
            }
        }
    } else {
        // Select a digit
        for (i = 0; i < 10; i++) {
            if (digit[i] < n) {
                digit[i]++;
                pass[level] = (char) ((int) '0' + i);
                password(pass, level + 1, letter, digit, n);
                digit[i]--;
            }
        }
    }
    return;
}



//commented version 



int main(int argc, char *argv[]) {
    // Declare variables: n for the command-line argument,
    // i for loop counters, level for recursion depth,
    // letter and digit for tracking character occurrences,
    // and pass as the password array.
    int n, i, level, letter[26], digit[10];
    char pass[L2];

    // Check if a command-line argument is provided
    if (argc < 2) {
        // If not, print usage information and exit with code 1 (error)
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    // Convert the first command-line argument to an integer
    n = atoi(argv[1]);
    // If the converted argument exceeds L1, print an error and exit
    if (n > L1) {
        fprintf(stderr, "n > L1.\n");
        return 1;
    }

    // Initialize the occurrence arrays for letters and digits to zero
    memset(letter, 0, sizeof(letter));
    memset(digit, 0, sizeof(digit));

    // Set the initial recursion level to 0
    level = 0;

    // Start the password generation by calling the password function
    password(pass, level, letter, digit, n);
    // Return 0 to indicate successful execution
    return 0;
}
void password(char *pass, int level, int *letter, int *digit, int n) {
    // Static variables to keep track of how many passwords have been generated
    // and when to stop the program after generating STOP passwords
    static int stop = 0, STOP = 1000;
    int i;

    // If we have reached the end of the password (recursion depth equals L2),
    // it's time to print the password
    if (level == L2) {
        // Terminate the current password with a null character to ensure proper printing
        pass[level] = '\0';
        // Print the current password
        printf("%s\n", pass);

        // Increment the number of generated passwords
        stop++;
        // If we have reached the maximum number of passwords (STOP), terminate the program
        if (stop >= STOP) {
            fprintf(stderr, "End program after %d passwords.\n", stop);
            exit(EXIT_FAILURE);
        }

        // Return to stop the current recursive call
        return;
    }

    // If the current level is less than L1, we are still adding letters to the password
    if (level < L1) {
        // Iterate over all possible letters
        for (i = 0; i < 26; i++) {
            // If the current letter has been used less than n times
            if (letter[i] < n) {
                // Increment the count for this letter
                letter[i]++;
                // Set the current level of the password to this letter
                pass[level] = 'a' + i;
                // Recursively call password to fill in the next level
                password(pass, level + 1, letter, digit, n);
                // Decrement the count for this letter before trying the next one
                letter[i]--;
            }
        }
    } else {
    // If the current level is not less than L1, we should start adding digits
    for (i = 0; i < 10; i++) {
        // Check if the current digit has been used less than n times
        if (digit[i] < n) {
            // Increment the count for this digit
            digit[i]++;
            // Set the current level of the password to this digit
            pass[level] = '0' + i;
            // Recursively call password to fill in the next level
            password(pass, level + 1, letter, digit, n);
            // Decrement the count for this digit before trying the next one
            digit[i]--;
        }
    }
}
// There's no need for a return statement here since the function type is void

In this `password` function:

- The recursion builds a string `pass` that represents a password, character by character.
- The `letter` and `digit` arrays track how many times each letter and digit have been used, ensuring that each is used no more than `n` times.
- The `level` variable tracks the depth of recursion, corresponding to the current position in the password being constructed.
- The function prints a password once it reaches the desired length (`L2`), then continues to build and print other combinations until the `stop` limit is reached.
