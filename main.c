
// main.c
// Author: Ethan Hillebrand
// Date: Apr 23, 2024
// Description: Program to do basic statistical values, including mean, median, variance, and standard deviation.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"



int main(int argc, char const *argv[])
{
    //if no arguments
    if (argc < 2) {
        printf("Usage: %s infile [outfile]\n", argv[0]);
        return 1;
    }

    // open file for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error. Can't open file.");
        return 1;
    }

    // Allocate initial memory
    float *arr = NULL;
    int capacity = 10;
    int size = 0;
    arr = (float *)malloc(capacity * sizeof(float));
    if (!arr) {
        fclose(file);
        perror("Memory allocation failed");
        return 1;
    }

    float num;
    while (fscanf(file, "%f", &num) == 1) {
        if (size == capacity) {
            capacity *= 2;
            arr = realloc(arr, capacity * sizeof(float));
            if (!arr) {
                fclose(file);
                perror("Reallocation failed");
                return EXIT_FAILURE;
            }
        }
        arr[size++] = num;
    }

    fclose(file);

    // Compute statistics
    float m = mean(arr, size);
    float md = median(arr, size);
    float v = variance(arr, size);
    float s = standard_deviation(arr, size);

    // Output file
    FILE *out = stdout;
    if (argc == 3) {
        out = fopen(argv[2], "w");
        if (!out) {
            perror("Error opening output file");
            free(arr);
            return 1;
        }
    }

    //print out results
    fprintf(out, "Mean: %.2f\n", m);
    fprintf(out, "Median: %.2f\n", md);
    fprintf(out, "Variance: %.2f\n", v);
    fprintf(out, "Standard Deviation: %.2f\n", s);

    if (out != stdout) {
        fclose(out);
    }

    free(arr);
    return 0;
}