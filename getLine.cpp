
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

#include <pthread.h>

#define END_CHAR ']'

//Returns the sum of the numbers in a vector
double sum(std::vector<double> nums) {
    size_t size = nums.size();
    double total = 0;
    for (size_t i = 0; i < size; i++) {
        total += nums[i];
    }
    return total;
}

//Returns the mean value of all the numbers in a vector
double mean(std::vector<double> nums) {
    return sum(nums) / nums.size();
}

//Squares each number in nums and adds it to a returned vector
std::vector<double> square(std::vector<double> nums) {
    std::vector<double> outNums;
    size_t size = nums.size();
    outNums.resize(size);
    for (size_t i = 0; i < size; i++) {
        outNums[i] = pow(nums[i], 2);
    }
    return outNums;
}

//Multiplies each element in two vectors and returns the result.
std::vector<double> mult(std::vector<double> v1, std::vector<double> v2) {
    std::vector<double> outVect;
    size_t size = v1.size();
    outVect.resize(size);
    for (size_t i = 0; i < size; i++) {
        outVect[i] = v1[i] * v2[i];
    }
    return outVect;
}

//Gets a variable from standard input.
std::vector<double> getVar(char var) {
    std::vector<double> outVect;
    std::cout << var << " = [" << std::endl;
    std::string inCache;
    do {
        std::cin >> inCache;
        outVect.push_back(atof(inCache.c_str()));
    } while (inCache[0] != END_CHAR);

    //Cut off the terminating END_CHAR
    outVect.resize(outVect.size() - 1);
    return outVect;
}

int main() {
    //Get x and ys
    std::vector<double> x = getVar('x');
    std::vector<double> y = getVar('y');
    //Make sure that x and y are the same size.
    if (x.size() != y.size()) {
        std::cout << "x and y are different sizes." << std::endl;
        return 1;
    }
    //Calculate a value
    double sumX = sum(x);
    double sumY = sum(y);
    double sumXY = sum(mult(x, y));
    double sumXX = sum(square(x));
    double sumYY = sum(square(y));
    double n = x.size();
    double a = (n * sumXY - sumX * sumY) / (n * sumXX - pow(sumX, 2));
    //Calculate b value
    double meanY = mean(y);
    double meanX = mean(x);
    double b = meanY - a * meanX;
    std::cout << "y = " << a << "x + " << b << std::endl;
}