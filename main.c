//#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void swap (int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main (void) {
    union ticks{
        unsigned long long t64;
        struct s32 { long th, tl; } t32;
    } start, end;
    double cpu_Hz = 2000000000ULL; // for 2 GHz CPU
    FILE* input = fopen("/home/ilya/CLionProjects/my_bubble_sort/in.txt", "r");
    if (input == NULL) {
        return 1;
    }
    int n;
    if (fscanf(input, "%d", &n) != 1) {
        fclose(input);
        return 1;
    }
    int* a = malloc(sizeof(int) * n);
    if (a == NULL) {
        fclose(input);
        return 1;
    }
    for (int i = 0, m; i < n; ++ i) {
        if (fscanf(input, "%d", &m) != 1) {
            free(a);
            fclose(input);
            return 1;
        }
        a[i] = m;
    }
    fclose(input);
    //struct timespec start, end;
    // clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    asm("rdtsc\n" : "=a" (start.t32.th), "=d" (start.t32.tl));
    for (int i = 0; i < n; ++ i) {
        for (int j = n - 1; j > i; -- j) {
            if (a[j] <= a[j - 1]) {
                swap(&a[j], &a[j - 1]);
            }
        }
    }
    asm("rdtsc\n" : "=a" (end.t32.th), "=d" (end.t32.tl));
    //clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    //printf("Time taken: %lf sec.\n", end.tv_sec-start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));
    FILE* output = fopen("/home/ilya/CLionProjects/my_bubble_sort/out.txt", "w");
    if (output == NULL) {
        free(a);
        return 1;
    }
    printf("Time taken: %lf sec.\n", (end.t64-start.t64) / cpu_Hz);
    for (int i = 0; i < n; ++ i) {
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
    free(a);
    return 0;
}
