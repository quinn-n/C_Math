#include <cmath>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "strUtils.cpp"
#include <pthread.h>
#include <thread>

static const int n_cores = std::thread::hardware_concurrency();

long int maxLCM = 0;
long int globalNum1;
long int globalNum2;

void* getLCMDevice(void* threadId) {
	long tid = (long) threadId;
	long int lowest = 1;
	for(int i = (maxLCM+1) - tid; i > 0; i -= n_cores) {
		if(remainder(globalNum1, i) == 0 && remainder(globalNum2, i) == 0) {
		//if(fmod(globalNum1, i) == 0 && fmod(globalNum2, i) == 0) {
			if(i > lowest) {
				lowest = i;
				return (void*) i;
			} else {
				return (void*) i;
			}
		}
	}
	return (void*) 1;
}

long int getLCM(int num1, int num2) {
	maxLCM = num1 * num2;
	long int lcm = 1;
	globalNum1 = num1;
	globalNum2 = num2;
	pthread_t threads[n_cores];
	for(int i=0;i<n_cores;i++) {
		pthread_create(&threads[i], NULL, getLCMDevice, (void*) i);
	}
	long int lowest;
	void* status;
	for(int i=0;i<n_cores;i++) {
		pthread_join(threads[i], &status);
		lowest = (long) status;
		if (lowest > lcm) {
			lcm = lowest;
		}
	}
	return lcm;
}

bool isInt(float x) { //returns true if x is a whole number.
    return(remainder(x,1) == 0);
/*    if(remainder(x,1) == 0) {
        return true;
    } else {
        return false;
    } */
}

int main(int argc, char* argv[]) {
    float a;
    float b;
    float c;
    std::string variableName = "x";
    if(argc == 3) {
        a = atof(argv[1]); // a & c given
        b = 0;
        c = atof(argv[2]);
    } else if(argc == 4) { //a, b & c given
        a = atof(argv[1]);
        b = atof(argv[2]);
        c = atof(argv[3]);
    } else if(argc == 5) { //variable name
        a = atof(argv[1]);
        b = atof(argv[2]);
        c = atof(argv[3]);
        variableName = argv[4];
    } else {
        std::cout << "Usage: " << argv[0] << " <a> [b] <c> [variable name]" << std::endl;
        std::cout << "ax^2 + bx + c" << std::endl;
        std::cout << "Factors a trinomial." << std::endl;
        std::cout << "Example: " << argv[0] << " 1 3 2 f" << std::endl;
        std::cout << "Or: " << argv[0] << " 1 3 2" << std::endl;
        return 0;
    }

    float oldA = a;
    float oldB = b;
    float oldC = c;
    bool decimal = false;
    int multiplier = 1;

    if(isInt(a) && isInt(b) && isInt(c)) { //check for decimal numbers
        std::cout << "No decimals found." << std::endl;
    } else {
        decimal = true;
        std::cout << "Decimals found." << std::endl;
        multiplier = 10;
    }

    while(decimal) { //remove the decimal spaces from our numbers so we can factor them.
        a = oldA * multiplier;
        b = oldB * multiplier;
        c = oldC * multiplier;
        if(isInt(a) && isInt(b) && isInt(c)) {
            decimal = false;
        } else {
            multiplier *= 10;
        }
    }

    float multiplied = a * c;

    bool negative = false;
    if(multiplied < 0) { //we can't find the square root of a negative number
        multiplied /= -1;
        negative = true;
    }

    float root = sqrt(multiplied);
    int maxNum = floor(root);

    if(negative) multiplied /= -1;

    std::cout << "Found a: " << a << " found b: " << b << " found c: " << c << std::endl;
    std::cout << "Looping through 1 - " << maxNum << std::endl;

    int totalNumNums = 0;

    int loopNum = maxNum + 1;
    int cacheNum;
    //find the two numbers that multiply to a*c and add to b
    for(int i = 0; i < loopNum; i++) {
        cacheNum = multiplied / i;
        if(b == i + cacheNum) {
            totalNumNums++;
        } else if(b == cacheNum - loopNum || b == loopNum - cacheNum) {
            totalNumNums++;
        } else if(b == (i + cacheNum) / -1) {
            totalNumNums++;
        }
    }

    int firstSetNums[totalNumNums];
    int secondSetNums[totalNumNums];
    int numNums = 0;

    for(int i = 0; i < loopNum; i++) {
        cacheNum = multiplied / i;
        if(b == i + cacheNum) {
            std::cout << "first number: " << cacheNum << ", second number: " << i << std::endl;
            firstSetNums[numNums] = cacheNum;
            secondSetNums[numNums] = i;
            numNums++;
        } else if(b == cacheNum - loopNum || b == loopNum - cacheNum) {
            std::cout << "first number: " << cacheNum << ", second number: " << i / -1 << std::endl;
            firstSetNums[numNums] = cacheNum;
            secondSetNums[numNums] = i / -1;
            numNums++;
        } else if(b == (i + cacheNum) / -1) {
            std::cout << "first number: " << cacheNum / -1 << ", second number: " << i / -1 << std::endl;
            firstSetNums[numNums] = cacheNum / -1;
            secondSetNums[numNums] = i / -1;
            numNums++;
        }
    }

    bool backwards;
    std::string finalFactors[numNums];
    int numFactors = 0;
    std::cout << "Got " << numNums << " different factors." << std::endl;
    for(int i=0;i<numNums;i++) {
        int firstSetNum = firstSetNums[i];
        int secondSetNum = secondSetNums[i];
        long double firstBracketMult = getLCM(a,firstSetNum);
        long double secondBracketMult = getLCM(c,secondSetNum);
        backwards = false;
        if(firstBracketMult == 0 || secondBracketMult == 0) {
            firstBracketMult = getLCM(a,secondSetNum);
            secondBracketMult = getLCM(c,firstSetNum);
            backwards = true;
        }
        if(firstBracketMult == 0 || secondBracketMult == 0) {
            std::cout << "Uh-oh! It looks like something went wrong. You should double check that your equation is factorable, and if it is, send me the arguments you've used with this program so I can try to fix it." << std::endl;
            return 1;
        }
        //here we get the final strings of our trinomials.
        std::string firstBracket = "";
        std::string secondBracket = "";
        firstBracket = "(" + atos(a/firstBracketMult) + variableName + "+" + atos(firstSetNum / firstBracketMult) + ")";
        secondBracket = "(" + atos(secondSetNum / secondBracketMult) + variableName + "+" + atos(c/secondBracketMult) + ")";
        bool firstAndSecondEqual = true;
        if(firstBracket != secondBracket) {
            firstAndSecondEqual = false;
            //check if the first bracket is equal to the second with the numbers flipped.
            if(secondBracket == "(" + atos(a / firstBracketMult / -1) + variableName + "+" + atos(firstSetNum / firstBracketMult / -1) + ")") {
                firstBracket = "(" + atos(a / firstBracketMult / -1) + variableName + "+" + atos(firstSetNum / firstBracketMult / -1) + ")";
                firstBracketMult /= -1;
                firstAndSecondEqual = true;
            }
        }

        if(!firstAndSecondEqual) { //if our brackets aren't the same, we cannot factor them further.
            if(!backwards) {
                finalFactors[numFactors] = atos(firstBracketMult/multiplier) + variableName + firstBracket + "+" + atos(secondBracketMult) + secondBracket;
                numFactors++;
            } else if(backwards) {
                finalFactors[numFactors] = atos(firstBracketMult / multiplier) + variableName + "(" + atos(a / firstBracketMult) + variableName + "+" + atos(secondSetNum / firstBracketMult) + ")+" + atos(secondBracketMult) + "(" + atos(firstSetNum / secondBracketMult) + variableName + "+" + atos(c / secondBracketMult);
                numFactors++;
            }
        } else { //if our brackets are the same, we can factor further.
            if(getLCM(firstBracketMult, secondBracketMult) != 1) {
                int commonMultiple = getLCM(firstBracketMult, secondBracketMult);
                finalFactors[numFactors] = atos(commonMultiple / multiplier) + "(" + atos(firstBracketMult / commonMultiple) + variableName + "+" + atos(secondBracketMult / commonMultiple) + ")" + firstBracket;
                numFactors++;
            } else {
                if(multiplier == 1) {
                    finalFactors[numFactors] = "(" + atos(firstBracketMult) + variableName + "+" + atos(secondBracketMult) + ")" + firstBracket;
                } else {
                    finalFactors[numFactors] = "1/" + atos(multiplier) + "(" + atos(firstBracketMult) + variableName + "+" + atos(secondBracketMult) + ")" + firstBracket; //we can use any bracket here, since they're the same.
                }
                numFactors++;
            }
        }
    }
    std::cout << "Factor(s):" << std::endl;
    for(int i=0;i<numFactors;i++) {
        std::cout << finalFactors[i] << std::endl;
    }
}
