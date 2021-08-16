/* matmul.cpp
 * Multiplies matricies.
 * Written by happylego91 <happylego91@gmail.com>
 * March 31st 2019
*/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <ctype.h>
#include <arrayutils.hpp>
#include <error.h>
#include <progutil.h>

#define MATRIX_TERMINATOR "]"
#define NUM_SEPARATOR ','

typedef std::vector<std::vector<double>> matrix;
//[row][column]

matrix mat1;
matrix mat2;

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
    mat1 = getVect();
    mat2 = getVect();
}

//Resizes a matrix
void resizeMatrix(matrix &mat, size_t rows, size_t cols) {
    mat.resize(rows);
    for(size_t i = 0; i < rows; i++) {
        mat[i].resize(cols);
    }
}

//Gets position of a matrix multiplication. Note: row and col start from 0, not 1.
double getPos(matrix mat1, matrix mat2, size_t row, size_t col) {
    double result = 0;
    size_t matsize = mat2.size();
    for(size_t i = 0; i < matsize; i++) {
        result += mat1[row][i] * mat2[i][col];
    }
    return result;
}

//Multiplies two matrices.
matrix matmul (matrix m1, matrix m2) {
    matrix outMat;
    //The dimensions of the result of a multiplication are rows in m1 x cols in m2.
    size_t numRows = m1.size();
    size_t numCols = m2[0].size();
    resizeMatrix(outMat, numRows, numCols);
    for(size_t row = 0; row < numRows; row++) {
        for(size_t col = 0; col < numCols; col++) {
            outMat[row][col] = getPos(m1, m2, row, col);
        }
    }
    return outMat;
}

int main() {
    getInputs();
    matrix outMat = matmul(mat1, mat2);
    printMatrix(outMat);
}