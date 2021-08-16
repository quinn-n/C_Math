#include <matrix.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <arrayutils.hpp>
#include <error.h>
#include <progutil.h>

#define MATRIX_TERMINATOR "]"
#define NUM_SEPARATOR ','
#define HELP_MSG "Usage: matpow [-h]\nRaises a matrix to an exponent.\nNote: exponent must be a positive, whole integer."

//Gets all the elements in a string from start to end.
std::string getStringRange(std::string str, size_t s, size_t e) {
    std::string outStr;
    for(size_t i = s; i < e; i++) {
        outStr += str[i];
    }
    return outStr;
}

//Strips a string of all whitespace characters.
std::string strip(std::string str) {
    size_t strlen = str.length();
    std::string outstr;
    //Loop over every element in str, backwards, to get the last position of a non-whitespace char.
    size_t lastChar;
    for(lastChar = strlen; isspace(str[lastChar]); lastChar--);
    return getStringRange(str, 0, lastChar + 1);
}

//Splits a string between given characters.
std::vector<std::string> splitString(std::string str, char split) {
    //Initialize vars
    std::vector<std::string> outVect;
    size_t strlen = str.length();
    size_t vectPos = 0;
    //Resize outVect to the number of characters in str. We'll shrink it later.
    outVect.resize(strlen);
    //Loop over every char in str, 
    for(size_t i = 0; i < strlen; i++) {
        if(str[i] != split) {
            outVect[vectPos] += str[i];
        } else {
            vectPos++;
        }
    }
    //Shrink outVect to the number of used elements.
    outVect.resize(vectPos + 1);
    return outVect;
}

//Prints a matrix to stdout.
void printMatrix(matrix mat) {
    size_t numRows = mat.size();
    size_t numCols = mat[0].size();
    std::cout << "[\n";
    for(size_t row = 0; row < numRows; row++) {
        for(size_t col = 0; col < numCols; col++) {
            std::cout << mat[row][col] << NUM_SEPARATOR;
        }
        std::cout << std::endl;
    }
    std::cout << "]" << std::endl;
}

//Gets a matrix from stdin. Terminates at a ].
matrix getMatrix() {
    std::string input = "";
    size_t row = 0;
    std::vector<std::string> numStr;
    matrix outNums;
    std::cout << "[" << std::endl;
    while (input != MATRIX_TERMINATOR) {
        //std::cin.getline((char*) input.c_str(), 9001);
        std::cin >> input;
        if (input == MATRIX_TERMINATOR)
            break;
        numStr = splitString(input, NUM_SEPARATOR);
        //Strip every string in nums.
        size_t numSize = numStr.size();
        for(size_t i = 0; i < numSize; i++) {
            numStr[i] = strip(numStr[i]);
        }
        //Add all the numbers in numStr to outNums and allocate an extra slot to outNums.
        outNums.resize(row + 1);
        for(size_t col = 0; col < numSize; col++) {
            outNums[row].push_back(atof(numStr[col].c_str()));
        }
        row++;
    }
    return outNums;
}

unsigned long getPow() {
    std::string inCache;
    std::cout << "Power\n>> " << std::flush;
    std::cin >> inCache;
    return (unsigned long) atoll(inCache.c_str());
}

//Resizes a matrix
void resizeMatrix(matrix &mat, size_t rows, size_t cols) {
    mat.resize(rows);
    for(size_t i = 0; i < rows; i++) {
        mat[i].resize(cols);
    }
}

int main() {
    matrix mat = getMatrix();
    unsigned long power = getPow();
    mat = mat ^ power;
    printMatrix(mat);
}