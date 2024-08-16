int search(int *v1, int *v2, int d1, int d2) {
    int i, j, flag;
    
    // For each overlapping position i
    i = 0;
    while (i < d1-d2) { 
        // i is the starting index for the current window in v1 to compare with v2

        j = 0; // j is the index for elements in v2
        flag = 1; // flag used as a boolean to indicate if the subarray is found

        // Visit array v2 and subarray of v1 starting at i
        while (j<d2 && flag==1) { 
            // Iterate through v2 and the subarray of v1 starting at i
            if (v1[i+j] != v2[j]) { 
                // If any element doesn't match, set the flag to 0 (false) and break the loop
                flag = 0;
            }
            j++; // Move to the next element in v2
        }

        if (flag == 1) { 
            // If flag is still 1 after the inner loop, it means all elements matched
            // Subarray found - return the starting index of subarray in v1
            return i;
        }

        i++; // Move the starting window in v1 to the next element
    }

    return -1; // If no matching subarray is found, return -1
}



//second way


int search(int *v1, int *v2, int d1, int d2) {
    // Iterate over v1 with a for loop
    for (int i = 0; i <= d1 - d2; i++) {
        int flag = 1; // Flag to indicate if the subarray is found

        // Check if the subarray of v1 starting at i matches with v2
        for (int j = 0; j < d2 &&flag==1; j++) {
            if (v1[i + j] != v2[j]) {
                flag = 0; // Set flag to 0 if any element doesn't match
                break; // Break the inner loop as there's no match
            }
        }

        if (flag) {
            return  ; // Return the starting index of the matching subarray in v1
        }
    }

    return -1; // Return -1 if no matching subarray is found
}
