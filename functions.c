// main.c
// Author: Ethan Hillebrand
// Date: Apr 23, 2024
// Description: Program to do basic statistical values, including mean, median, variance, and standard deviation.

// functions.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Mean
float mean(float *arr, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}


int compare_floats(const void *a, const void *b) {
    float fa = *(const float *)a;
    float fb = *(const float *)b;
    return (fa > fb) - (fa < fb);
}

// median
float median(float *arr, int size) {
    float *copy = malloc(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        copy[i] = arr[i];
    }

    qsort(copy, size, sizeof(float), compare_floats);

    float med;
    if (size % 2 == 0) {
        med = (copy[size/2 - 1] + copy[size/2]) / 2.0;
    } else {
        med = copy[size/2];
    }

    free(copy);
    return med;
}

//variance
float variance(float *arr, int size) {
    float avg = mean(arr, size);
    float sum = 0;

    for (int i = 0; i < size; i++) {
        float diff = arr[i] - avg;
        sum += diff * diff;
    }

    return sum / size;  
}

//standard deviation
float standard_deviation(float *arr, int size) {
    return sqrt(variance(arr, size));
}