#include <iostream>
#include <stdlib.h>
#include <math.h>

bool isInt(double num) {
	return(fmod(num, 1.) == 0);
}

int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cout << "Usage: " << argv[0] << " <number>" << std::endl;
		return 1;
	} else if(argv[1] == "-h" || argv[1] == "--help") {
		std::cout << "Usage: " << argv[0] << " <number>" << std::endl;
		return 1;
	}
	int num = atoi(argv[1]);
	for(int i = num;i > 0;i--) {
		if(isInt(num / pow(i, 2))) {
			std::cout << pow(i, 2) << ", which reduces to " << i << std::endl;
			return 0;
		}
	}
}
