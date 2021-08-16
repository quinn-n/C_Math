#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "strUtils.cpp"
#define BLOCKS 1
#define BLOCK_THREADS 256

std::string arrayToString(long int* array, size_t size) {
  std::string outString;
  for(size_t i=0;i < size;i++) {
		outString += atos(array[i]) + ", ";
  }
  return getStringRange(outString, 0, outString.length()-2);
}

//Get the largest element using reduction.
__global__
void getMaxElement(long int* array, size_t size, long int* result) {
	extern __shared__ long int resultCache[];
	//copy array into resultCache.
	for(int i=threadIdx.x;i < size;i += blockDim.x) {
		resultCache[i] = array[i];
	}
	__syncthreads();
	int totalElements = size;
	int halfPoint;
	//Keep track of how many times the loop has run so we can use the halfPoints array.
	__syncthreads();
	while (totalElements > 1) {
		//only half the threads will be active.
		halfPoint = totalElements / 2;
		for(int currentElement = threadIdx.x;currentElement < halfPoint;currentElement += blockDim.x) {
			if(currentElement < halfPoint) {
				//if this thread's cache is less than it's partener's cache, set it's cache equal to it's partener's cache.
				if (resultCache[currentElement] < resultCache[currentElement + halfPoint]) {
					resultCache[currentElement] = resultCache[currentElement + halfPoint];
				}
			}
		}
		__syncthreads();
		totalElements = halfPoint;
	}
	if (threadIdx.x == 0) result[0] = resultCache[0];
	return;
}

__global__
void deviceGetLCM(double* nums, long int* results) {
  int maxLCM = nums[0] * nums[1];
  int tid = threadIdx.x + blockIdx.x * blockDim.x;
  int step = blockDim.x + blockIdx.x * blockDim.x;
  for(double i=maxLCM - tid;i > 0;i -= step) {
    if (fmod(nums[0], i) == 0 && fmod(nums[1], i) == 0) {
      //make sure the current number is greater than the current result.
      if (i > results[tid]) results[tid] = i;
      //else we've already gone past it and can end the thread.
      else return;
    }
  }
  __syncthreads();
}

long double getLCM(long int num1, long int num2) {
  double* nums;
  long int* lcmResult;
  cudaMallocManaged(&nums, sizeof(double) * 2);
  cudaMallocManaged(&lcmResult, sizeof(long int) * BLOCKS * BLOCK_THREADS);
  nums[0] = num1;
  nums[1] = num2;
  //Reduce the possible LCMs to the number of threads.
  deviceGetLCM<<<BLOCKS, BLOCK_THREADS>>>(nums, lcmResult);
	//prepare for the next kernel while we wait for this one to finish
	long int* result;
	//std::cout << "lcmResult: " << arrayToString(result, BLOCKS * BLOCK_THREADS) << std::endl;
	cudaMallocManaged(&result, sizeof(long int));
  cudaDeviceSynchronize();
  //Get the maximum element from the results of BLOCKSGetLcm.
	getMaxElement<<<BLOCKS, BLOCK_THREADS, sizeof(long int) * BLOCKS * BLOCK_THREADS>>>(lcmResult, BLOCKS * BLOCK_THREADS, result);
  //Free memory on the device
  cudaFree(&nums);
	cudaDeviceSynchronize();
	std::cout << "result: " << arrayToString(result, 1) << std::endl;
	cudaFree(&lcmResult);
  return result[0];
}

bool isInt(float x) { //returns true if x is a whole number.
    return(remainder(x,1) == 0);
}

__global__ void findCombos(int* firstSetNums, int* secondSetNums, int* numNums, int max, int multiplied, float a, float b, float c) {
    int threadNum = threadIdx.x;
    int step = blockDim.x;
    int loopNum = max + 1;
    int cacheNum;
    for(int i = threadNum; i < loopNum; i += step) {
        cacheNum = multiplied / i;
        if(b == i + cacheNum) {
            firstSetNums[numNums[0]] = cacheNum;
            secondSetNums[numNums[0]] = i;
            numNums[0]++;
        } else if(b == cacheNum - loopNum || b == loopNum - cacheNum) {
            firstSetNums[numNums[0]] = cacheNum;
            secondSetNums[numNums[0]] = i / -1;
            numNums[0]++;
        } else if(b == (i + cacheNum) / -1) {
            firstSetNums[numNums[0]] = cacheNum / -1;
            secondSetNums[numNums[0]] = i / -1;
            numNums[0]++;
        }
    }
}

__global__ void getNumCombos(int* numCombos, int max, int multiplied, float a, float b, float c) {
    int threadNum = threadIdx.x;
    int step = blockDim.x;
    int loopNum = max + 1;
    int cacheNum;
    for(int i = threadNum; i < loopNum; i += step) {
        cacheNum = multiplied / i;
        if(b == i + cacheNum) {
            numCombos[0]++;
        } else if(b == cacheNum - loopNum || b == loopNum - cacheNum) {
            numCombos[0]++;
        } else if(b == (i + cacheNum) / -1) {
            numCombos[0]++;
        }
    }
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

    int* numCombos;
    cudaMallocManaged(&numCombos, sizeof(int));

    getNumCombos<<<BLOCKS, BLOCK_THREADS>>>(numCombos, maxNum, multiplied, a, b, c);
    cudaDeviceSynchronize();

    std::cout << "Got " << numCombos[0] << " combos." << std::endl;

    int* firstSetNums;
    int* secondSetNums;
    int* numNums;

    cudaMallocManaged(&firstSetNums, numCombos[0] * sizeof(int));
    cudaMallocManaged(&secondSetNums, numCombos[0] * sizeof(int));
    cudaMallocManaged(&numNums, numCombos[0] * sizeof(int));

    findCombos<<<BLOCKS, BLOCK_THREADS>>>(firstSetNums, secondSetNums, numNums, maxNum, multiplied, a, b, c);
    cudaDeviceSynchronize();

    bool backwards;
    std::string finalFactors[numNums[0]];
    int numFactors = 0;
    std::cout << "Got " << numNums[0] << " different factors." << std::endl;
    for(int i=0;i<numNums[0];i++) {
        std::cout << i << ". Got first num: " << firstSetNums[i] << ", and second num: " << secondSetNums[i] << std::endl;
    }
    for(int i=0;i<numNums[0];i++) {
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
            std::cout << "Uh-oh! It looks like something went wrong. You might want to double check that your equation is factorable, and if it is, send me the arguments you've used with this program so I can try to fix it." << std::endl;
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
                long double commonMultiple = getLCM(firstBracketMult, secondBracketMult);
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
