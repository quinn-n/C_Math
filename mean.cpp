/*
mean.cpp
Calculates the mean of the numbers given by argv.
Written by happylego91
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <progutil.h>

#define HELP_MSG "Usage: average <[nums]>\nCalculates mean between all given numbers.\n"

std::vector<double> getNums(char** arr, size_t size) {
    //Converts all the char* numbers in array to doubles.
    std::vector<double> outVect;
    outVect.resize(size - 1);
    for (size_t i = 1; i < size; i++) {
        outVect[i - 1] = atof(arr[i]);
    }
    return outVect;
}

//Gets the sum of all elements in a vector
double sum(std::vector<double> vect) {
    size_t vectSize = vect.size();
    size_t sum = vect[0];
    for (size_t i = 1; i < vectSize; i++) {
        sum += vect[i];
    }
    return sum;
}

//Returns the mean of the elements in a vector.
double mean(std::vector<double> vect) {
    return sum(vect) / vect.size();
}

int main(int argc, char** argv) {
    //Verify inputs
    if (!checkInputs(argc, argv, 2, (char*) HELP_MSG))
        return 1;
    std::vector<double> inputNums = getNums(argv, argc);
    double numsum = sum(inputNums);
    double mean = numsum / inputNums.size();
    std::cout << "Got sum: " << numsum << std::endl;
    std::cout << "Got mean: " << mean << std::endl;
}
