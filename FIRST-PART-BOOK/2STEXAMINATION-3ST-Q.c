#include <stdlib.h>
#include <stdio.h>

#define N 5

void aeiou (char *, char [], int [], int, int, int);

int main (int argc, char *argv[]) {
    char *sol;
    char alfa[N] = {'A', 'E', 'I', 'O', 'U'};
    int taken[N] = {0};
    int n_char;

    if (argc < 2) {
        fprintf(stderr, "Run as: pgm numberOfChar.\n");
        exit(EXIT_FAILURE);
    }

    n_char = atoi(argv[1]);
    if (n_char < 0 || n_char > N) {
        fprintf(stderr, "Run with: numberOfChars > N (%d<%d).\n", n_char, N);
        exit(EXIT_FAILURE);
    }

    sol = malloc(n_char * sizeof(char));
    if (sol == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    aeiou(sol, alfa, taken, 0, n_char - N, n_char);
    free(sol);

    return 0;
}
#include <stdio.h>
#define N 5

void aeiou (
    char *sol, char alfa[], int taken[],
    int position, int reps_allowed, int n_char
) {
    int i;

    if (position == n_char) {
        for (i = 0; i < n_char; i++) {
            fprintf(stdout, "%c", sol[i]);
        }
        fprintf(stdout, "\n");
        return;
    }

    for (i = 0; i < N; i++) {
        if (!taken[i]) {
            taken[i] = 1;
            sol[position] = alfa[i];
            aeiou(sol, alfa, taken, position+1, reps_allowed, n_char);
            taken[i] = 0;
        } else {
            if (taken[i] && reps_allowed > 0) {
                sol[position]=alfa[i];
                aeiou(sol, alfa, taken, position+1, reps_allowed-1, n_char);
            }
        }
    }
}





// Include standard library for various functions such as memory allocation and I/O operations.
#include <stdlib.h>
// Include standard I/O library for input and output functions.
#include <stdio.h>

// Define a preprocessor macro for the size of the array.
#define N 5

// Function prototype declaration for 'aeiou'.
void aeiou (char *, char [], int [], int, int, int);

// Main function: entry point of the program.
int main (int argc, char *argv[]) {
    // Pointer to character array for storing solutions.
    char *sol;
    // Array of vowels, representing the set of characters to use.
    char alfa[N] = {'A', 'E', 'I', 'O', 'U'};
    // Array to keep track of which characters have been used.
    int taken[N] = {0};
    // Variable to store the number of characters to use in the solution.
    int n_char;

    // Check if the command line arguments are less than 2.
    if (argc < 2) {
        // Print error message to stderr and exit if not enough arguments are provided.
        fprintf(stderr, "Run as: pgm numberOfChar.\n");
        exit(EXIT_FAILURE);
    }

    // Convert the first argument to an integer to get the number of characters.
    n_char = atoi(argv[1]);
    // Check if the provided number of characters is out of the allowed range.
    if (n_char < 0 || n_char > N) {
        // Print error message to stderr and exit if the number is out of range.
        fprintf(stderr, "Run with: numberOfChars > N (%d<%d).\n", n_char, N);
        exit(EXIT_FAILURE);
    }

    // Allocate memory dynamically for the solution array based on the number of characters.
    sol = malloc(n_char * sizeof(char));
    // Check if memory allocation was successful.
    if (sol == NULL) {
        // Print error message to stderr and exit if memory allocation failed.
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Call the 'aeiou' function with the allocated memory and parameters.
    aeiou(sol, alfa, taken, 0, n_char - N, n_char);
    // Free the dynamically allocated memory for the solution array.
    free(sol);

    // Return 0 to indicate successful execution of the program.
    return 0;
}

// Include standard I/O library for input and output functions (redundant as already included above).
#include <stdio.h>
// Define a preprocessor macro for the size of the array (redundant as already defined above).
#define N 5

// Definition of the 'aeiou' function, which generates combinations of vowels.
void aeiou (
    char *sol, char alfa[], int taken[],
    int position, int reps_allowed, int n_char
) {
    // Index variable for loops.
    int i;

    // Base case for recursion: if all positions are filled, print the solution.
    if (position == n_char) {
        // Loop through the solution array and print each character.
        for (i = 0; i < n_char; i++) {
            fprintf(stdout, "%c", sol[i]);
        }
        // Print a newline after printing the solution.
        fprintf(stdout, "\n");
        // Return from the function to backtrack.
        return;
    }

     // Loop through all possible characters in the 'alfa' array.
    for (i = 0; i < N; i++) {
        // Check if the current character is not already taken.
        if (!taken[i]) {
            // Mark the character as taken.
            taken[i] = 1;
            // Place the character in the current position of the solution array.
            sol[position] = alfa[i];
            // Recursively call 'aeiou' for the next position.
            aeiou(sol, alfa, taken, position+1, reps_allowed, n_char);
            // Unmark the character as taken to allow for other combinations.
            taken[i] = 0;
        } else {
            // Check if the character has already been taken and if repetitions are allowed.
            if (taken[i] && reps_allowed > 0) {
                // Place the character in the current position of the solution array.
                sol[position] = alfa[i];
                // Recursively call 'aeiou' for the next position, decrementing the repetitions allowed.
                aeiou(sol, alfa, taken, position+1, reps_allowed-1, n_char);
            }
        }
    }
    
