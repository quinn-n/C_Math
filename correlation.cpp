/* correlation.cpp
 * Gets the correlation value (r value) of a scatter plot.
 * Written by happylego91
 * April 30th
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <progutil.h>

#define HELP_MSG "Usage: correlation <[-h]>\nGets the correlation between given points.\n"
#define END_CHAR ']'

//Returns the sum of a vector
double sum(std::vector<double> nums) {
    size_t vectsize = nums.size();
    long double total = 0;
    for (size_t i = 0; i < vectsize; i++) {
        total += nums[i];
    }
    return total;
}

//Squares every value in nums and retursn the result
std::vector<double> square(std::vector<double> nums) {
    std::vector<double> outVect;

    size_t len = nums.size();
    outVect.resize(len);
    for (size_t i = 0; i < len; i++) {
        outVect[i] = pow(nums[i], 2);
    }
    return outVect;
}

//Multiplies each value in two vectors and returns the result
std::vector<double> mult(std::vector<double> v1, std::vector<double> v2) {
    std::vector<double> outVect;

    size_t len = v1.size();
    outVect.resize(len);
    for (size_t i = 0; i < len; i++) {
        outVect[i] = v1[i] * v2[i];
    }
    return outVect;
}

//Gets values from stdin for a given variable
std::vector<double> getVals(char var) {
    std::vector<double> outVect;
    std::string inCache;
    std::cout << var << " = [" << std::endl;
    //Get numbers
    do {
        std::cin >> inCache;
        outVect.push_back(atof(inCache.c_str()));
    } while (inCache[0] != END_CHAR);
    //Cut off the last element of outVect (which will always be 0 due to END_CHAR.)
    outVect.resize(outVect.size() - 1);
    return outVect;
}

int main(int argc, char** argv) {
    //Verify inputs
    if (!checkInputs(argc, argv, 1, (char*) HELP_MSG))
        return 1;
    std::vector<double> x = getVals('x');
    std::vector<double> y = getVals('y');
    //Make sure we got the same number of values for x and y.
    if (x.size() != y.size()) {
        std::cout << "You didn't enter the same number of elements for x and y." << std::endl;
        return 2;
    }

    double sumX = sum(x);
    double sumY = sum(y);
    double sumXX = sum(square(x));
    double sumYY = sum(square(y));
    double sumXY = sum(mult(x, y));
    size_t n = x.size();

    //Print out debug info
    std::cout << "Got sumX: " << sumX << std::endl;
    std::cout << "Got sumY: " << sumY << std::endl;
    std::cout << "Got sumXX: " << sumXX << std::endl;
    std::cout << "Got sumYY: " << sumYY << std::endl;
    std::cout << "Got sumXY: " << sumXY << std::endl;
    std::cout << "Got n: " << n << std::endl;

    std::cout << "Got numerator: " << (n * sumXY - sumX * sumY) << std::endl;
    std::cout << "Got denom1: " << (n * sumXX - pow(sumX, 2)) << std::endl;
    std::cout << "Got denom2: " << (n * sumYY - pow(sumY, 2)) << std::endl;

    double r = (n * sumXY - sumX * sumY) / sqrt((n * sumXX - pow(sumX, 2)) * (n * sumYY - pow(sumY, 2)));
    std::cout << "Got r: " << r << std::endl;
}
