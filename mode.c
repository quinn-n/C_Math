#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <progutil.h>

#define HELP_MSG "Usage: mode <nums>"
#define ISINT_TOLERANCE .0000000001

/*
//Returns true if num is an integer
bool isInt(double num) {
    return (fmod(num, 1) < ISINT_TOLERANCE);
}
*/

//Swaps two elements in an array
void swap(int* arr, int pos1, int pos2) {
    int cache = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = cache;
}

//Sorts an array using the bubble sort method
void sort(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int n = i; n < size - 1; n++) {
            if (arr[n] > arr[n + 1])
                swap(arr, n, n + 1);
        }
    }
}

//Fills an array with random numbers
void fillArr(int* arr, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
        printf("Generated element: %i\n", arr[i]);
    }
}

void printArr(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%i\n", arr[n]);
    }
}

int main(int argc, char** argv) {
    int numNums = argc - 1;
    int* testarr = malloc(sizeof(int) * 20);
    fillArr(testarr, 20);
    printf("Random arr:\n");
    printArr(testarr, 20);
    sort(testarr, 20);
    printf("Sorted arr:\n");
    printArr(testarr, 20);
}