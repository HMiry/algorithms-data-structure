#include <stdio.h>
#include <stdlib.h>

static void menu_create_r(char ***, int, char **, int);

void menu_create(char ***data, int n) {
    char **v;
    
    v = malloc(n * sizeof(char *));
    if (v==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    
    menu_create_r(data, n, v, 0);
    
    free(v);
    
    return;
}

static void menu_create_r(char ***data, int n, char **v, int l) {
    static int nSol = 1;
    int i;
    
    if (l==n) {
        fprintf(stdout, "Menu %2d: ", nSol);
        for (i=0; i<n; i++) {
            fprintf(stdout, "%s ", v[i]);
        }
        fprintf(stdout, "\n");
        nSol++;
        return;
    }

    i=0;
    while (data[l][i]!=NULL) {
        v[l] = data[l][i];
        menu_create_r(data, n, v, l+1);
        i++;
    }
    return;
}





//commented code 


#include <stdio.h>
#include <stdlib.h>

// Forward declaration of the recursive function to be used later in the code.
static void menu_create_r(char ***, int, char **, int);

// The 'menu_create' function is the entry point for creating menus.
// It takes a list of dish names ('data') and the number of courses ('n').
void menu_create(char **data, int n) {
    // Declare a pointer to a pointer to char, which will hold our menu.
    char **v;
    
    // Dynamically allocate memory for 'v' to hold 'n' pointers to char.
    v = malloc(n * sizeof(char *));
    // If memory allocation fails, print an error message and exit.
    if (v==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    
    // Call the recursive function 'menu_create_r' starting with level 0.
    menu_create_r(data, n, v, 0);
    
    // After all menus are created, free the allocated memory for 'v'.
    free(v);
    
    // Return from the function.
    return;
}

// The 'menu_create_r' function is a recursive function that creates all possible
// combinations of dishes into menus.
// It takes the list of dish names ('data'), number of courses ('n'),
// the current menu being built ('v'), and the current level ('l').
static void menu_create_r(char ***data, int n, char **v, int l) {
    // A static variable 'nSol' keeps track of the number of solutions (menus) created.
    static int nSol = 1;
    // An iterator variable.
    int i;
    
    // Base case for recursion: If the current level 'l' is equal to 'n',
    // it means a complete menu has been created.
    if (l==n) {
        // Print the current menu number.
        fprintf(stdout, "Menu %2d: ", nSol);
        // Iterate over the menu array 'v' and print each dish in the menu.
        for (i=0; i<n; i++) {
            fprintf(stdout, "%s ", v[i]);
        }
        // Move to the next line after printing the menu.
        fprintf(stdout, "\n");
        // Increment the solution count.
        nSol++;
        // Return to the previous level of recursion (or exit if this is the first call).
        return;
    }

    // Recursion part: For the current course 'l', iterate over all possible dishes.
    i=0;
    while (data[l][i]!=NULL) {
        // Set the current dish into the current menu at level 'l'.
        v[l] = data[l][i];
        // Recursively call 'menu_create_r' to build the next level of the menu.
        menu_create_r(data, n, v, l+1);
        // Move to the next dish for the current course after returning from recursion.
        i++;
    }
    // Return to the previous level of recursion once all dishes for the current course have been tried.
    return;
}
