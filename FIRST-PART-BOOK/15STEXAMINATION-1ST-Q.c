#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Convert a string to a floating-point number
float my_atof_ver1(char *s) {
    int i, n;
    float f1, f2, f;

    n = strlen(s); // Get the length of the string

    // Convert integer part
    for (f1 = 0.0, i = 0; s[i] != '.' && i < n; i++) { // Loop until '.' or end of string
            f1 = f1 * 10 + ((int)s[i]-'0'); // Convert character to digit and add to f1
    }

    // Convert decimal part
    for (f2 = 0.0, i = n-1; i>=0 && s[i] != '.'; i--) { // Start from the end and loop until '.'
            f2 = f2 + ((int)s[i]-'0'); // Convert character to digit and add to f2
            f2 = f2 / 10; // Adjust the decimal place of f2
        
    }

    f = f1 + f2; // Add integer and decimal parts

    // If there's an '-' in the string, adjust the float value accordingly
    if (s[0]=='-') {
        f = -f;
    }

    return f; // Return the result
}
