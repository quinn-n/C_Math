#include <iostream>
int main(int argc, char* argv[]) {
	float y1Mult;
	float y2Mult;

	float m1;
	float m2;

	float b1;
	float b2;

	if(argc == 5) {
		y1Mult = 1;
		y2Mult = 1;
		
		m1 = atof(argv[1]);
		b1 = atof(argv[2]);

		m2 = atof(argv[3]);
		b2 = atof(argv[4]);
	} else if(argc == 7) {
		y1Mult = atof(argv[1]);
		m1 = atof(argv[2]);
		b1 = atof(argv[3]);

		y2Mult = atof(argv[4]);
		m2 = atof(argv[5]);
		b2 = atof(argv[6]);
	} else {
		std::cout << "Usage: " << argv[0] << " <[y1Mult]> <m1> <b1> <[y2Mult]> <m2> <b2>" << std::endl;
		return 0;
	}

	m1 /= y1Mult;
	b1 /= y1Mult;

	m2 /= y2Mult;
	b2 /= y2Mult;

	float newM = m1 - m2;
	float newB = b1 - b2;

	float x = (newB / -1.) / newM;

	float y = m1 * x + b1;

	std::cout << "Got POI: (" << x << ", " << y << ")" << std::endl;
	return 0;
}
