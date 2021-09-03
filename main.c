#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h> // for times
#include <unistd.h> // for sysconf

void swap (int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main (void) {
    struct tms start, end;
    long clocks_per_sec = sysconf(_SC_CLK_TCK);
    long clocks;
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
    times(&start);
    for (int i = 0; i < n; ++ i) {
        for (int j = n - 1; j > i; -- j) {
            if (a[j] <= a[j - 1]) {
                swap(&a[j], &a[j - 1]);
            }
        }
    }
    times(&end);
    clocks = end.tms_utime - start.tms_utime;
    printf("Time taken: %lf sec.\n", (double) clocks / clocks_per_sec);
    FILE* output = fopen("/home/ilya/CLionProjects/my_bubble_sort/out.txt", "w");
    if (output == NULL) {
        free(a);
        return 1;
    }
    for (int i = 0; i < n; ++ i) {
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
    free(a);
    return 0;
}
