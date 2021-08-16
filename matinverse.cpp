/*
 * matinverse.cpp
 * Finds the inverse of a matrix.
 * Written by happylego91 <happylego91@gmail.com>
*/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <ctype.h>
#include <arrayutils.hpp>
#include <error.h>
#include <progutil.h>

#define MATRIX_TERMINATOR "]"
#define NUM_SEPARATOR ','

typedef std::vector<std::vector<double>> matrix;
//[row][column]

matrix mat;

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
matrix getVect() {
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
    printMatrix(outNums);
    return outNums;
}

//Gets two matrices from stdin.
void getInputs() {
    mat = getVect();
}

//Resizes a matrix
void resizeMatrix(matrix &mat, size_t rows, size_t cols) {
    mat.resize(rows);
    for(size_t i = 0; i < rows; i++) {
        mat[i].resize(cols);
    }
}

//Swaps two elements in a matrix.
void swapMatrix(matrix &mat, size_t row1, size_t col1, size_t row2, size_t col2) {
    double cache;
    cache = mat[row1][col1];
    mat[row1][col1] = mat[row2][col2];
    mat[row2][col2] = cache;
}

//Returns the determinant from a matrix.
//Returns NULL if the determinant is zero.
double getDet(matrix mat) {
    double a = mat[0][0];
    double b = mat[0][1];
    double c = mat[1][0];
    double d = mat[1][1];
    double det = a * d - b * c;
    if(det == 0)
        return (double) NULL;
    return det;
}

//Multiplies matrix by a base.
void multiplyBase(matrix &mat, double base) {
    size_t numRows = mat.size();
    size_t numCols = mat[0].size();
    //Iterate over each element in the matrix and multiply it by the base value.
    for(size_t row = 0; row < numRows; row++) {
        for(size_t col = 0; col < numCols; col++) {
            mat[row][col] *= base;
        }
    }
}

//Returns the inverse of a matrix.
//NOTE: This function assumes that the first part of the determinant is taken from a diagonal from 0,0 to x,x, and the second part is taken from 0,x to x,0
matrix inverseMatrix(matrix mat) {
    double det = getDet(mat);
    //Throw an exception if determinant is zero.
    if(det == (double) NULL)
        throw std::domain_error("Determinant is zero. There is no inverse.");
    std::cout << "Got determinant: " << det << std::endl;
    //Swap a and d
    swapMatrix(mat, 0, 0, 1, 1);
    //Invert b and c
    mat[0][1] *= -1;
    mat[1][0] *= -1;
    multiplyBase(mat, 1 / det);
    return mat;
}

int main() {
    getInputs();
    matrix invMat = inverseMatrix(mat);
    printMatrix(invMat);
}
