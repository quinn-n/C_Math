#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

int main(int argc, char** argv) {
  if (argc < 3 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
    std::cout << "Usage: div-remainder <numerator> <denominator>" << std::endl;
    std::cout << "Divides numerator and denominator and leaves the denominator" << std::endl;
    return 1;
  }
  int num = atoi(argv[1]);
  int denom = atoi(argv[2]);
  int result = num / denom;
  int remain = fmod(num, denom);
  std::cout << result << ", " << remain << 'R' << std::endl;
}
