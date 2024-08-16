#include <stdlib.h>
#include <float.h>
#include <stdio.h>

#define N 10
//FILE CLIENT.C

void permute(int taken[], float sol[], float best_sol[], float *best_dif, float mov[], float *min, float *max, int level, int tot_level);

int main(int argc, char *argv[]) {
    // Bank account cash flows
    float mov[N] = {1, -2, 3, 14, -5, 16, 7, 8, -9, 120};
    float sol[N] = {0};  // Current solution

    float best_sol[N] = {0};  // Best solution
    float best_diff = FLT_MAX;  // Smaller difference between max and min
    float min = FLT_MAX;  // Initialize min to the largest possible float value
    float max = -FLT_MAX; // Initialize max to the smallest possible float value

    int taken[N] = {0};  // Initialize all elements to 0, meaning not taken

    // Corrected function call with the right parameters
    permute(taken, sol, best_sol, &best_diff, mov, &min, &max, 0, N);

    fprintf(stdout, "Best order: ");
    for (int i = 0; i < N; i++) {
        fprintf(stdout, "%g ", best_sol[i]);
    }
    fprintf(stdout, "\n");

    fprintf(stdout, "Max balance: %.1f\n", max);
    fprintf(stdout, "Min balance: %.1f\n", min);
    fprintf(stdout, "Min difference: %.1f\n", best_diff);

    return 0;
}

//file impl3.c
#include <stdlib.h>
#include <float.h>
void permute(int taken[], float sol[], float best_sol[], float *best_diff, float mov[], float *min, float *max, int level, int tot_level) {
    if (level == tot_level) {
        evaluate(sol, best_sol, best_diff, min, max, tot_level);
        return;
    }
    
    for (int i = 0; i < tot_level; i++) {
        if (taken[i]==1){
            continue;
        } 
        taken[i] = 1;
        sol[level] = mov[i];
        permute(taken, sol, best_sol, best_diff, mov, min, max, level + 1, tot_level);
        taken[i] = 0;
    }
    return;
}


static void evaluate(float sol[], float best_sol[], float *best_diff, float *min, float *max, int tot_level) {
    float tot = 0, cmin = FLT_MAX, cmax = FLT_MIN;

    for (int i = 0; i < tot_level; i++) {
        tot += sol[i];
        cmin = (tot < cmin) ? tot : cmin;
        cmax = (tot > cmax) ? tot : cmax;
    }

    if ((cmax - cmin) < *best_diff) {
        *best_diff = cmax - cmin;
        for (int i = 0; i < tot_level; i++) {
            best_sol[i] = sol[i];
        }
        *min = cmin;
        *max = cmax;
    }
    return;
}





