/* Made by happylego91
 *
 * A program to get the lowest whole base of an integer.
 */

#include <iostream>
#include <math.h>
#include <stdlib.h>
#define START_BASE 2
#define START_POW 1

int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cout << "Usage: " << argv[0] << " <num>" << std::endl;
		std::cout << "Gets the lowest base of num." << std::endl;
		return 1;
	} else if(argv[1] == "-h" || argv[1] == "--help") {
		std::cout << "Usage: " << argv[0] << " <num>" << std::endl;
		std::cout << "Gets the lowest base of num." << std::endl;
		return 1;
	}
	int targetNum = atoi(argv[1]);
	int startBase = START_BASE;
	int currentPow;

	for(int i=START_BASE;i < targetNum;i++) {
		currentPow = START_POW;
		int powResult = pow(i, currentPow);
		while(powResult <= targetNum) {
			currentPow++;
			powResult = pow(i, currentPow);
			if(powResult == targetNum) {
				std::cout << "Got base: " << i << " and pow: " << currentPow << " which equals " << pow(i, currentPow) << std::endl;
				return 0;
			}
		}
	}
	return 0;
}
