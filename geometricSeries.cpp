/*
Written by happylego91

A tool to get a and r in a geometric series, and then find specific terms in the series.
1.0 Dec. 3rd 2018
*/
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string.h>

long double getTerm(double n, double a, double r) {
  return (a * pow(r, n - 1));
}
long double getSum(double n, double a, double r) {
  return (a * (pow(r, n) - 1) / (r - 1));
}

int main(int argc, char* argv[]) {
  //Print out help if we haven't got enough arguments or if we've got a -h or --help.
  if (argc < 3) {
    std::cout << "Usage: geometricSeries <t1> <t2>" << std::endl;
    std::cout << "geometricSeries -m <a> <r>" << std::endl;
    std::cout << "geometricSeries -n <t1> <t2> <tn> "<< std::endl;
    return 1;
  } else if (argv[1] == "-h" || argv[1] == "--help") {
    std::cout << "Usage: geometricSeries <t1> <t2>" << std::endl;
    std::cout << "geometricSeries -m <a> <r>" << std::endl;
    std::cout << "geometricSeries -n <t1> <t2> <tn> "<< std::endl;
    return 0;
  }
  double a;
  double r;
  char type;

  if (argc > 3) {
    //Get the type of operation.
    type = argv[1][1];
    //'manual' mode, give the script a and r directly.
    if(type == "m"[0]) {
      a = atof(argv[2]);
      r = atof(argv[3]);
    //Get n from it's term, print out n and the sum at n.
    } else if (type == "n"[0]) {
      a = atof(argv[2]);
      double t2 = atof(argv[3]);
      double tn = atof(argv[4]);
      r = t2 / a;
      long int n = log(tn / a) / log(r) + 1;
      long double sum = getSum(n, a, r);
      std::cout << "a: " << a << "\nr: " << r << "\nn: " << n <<  "\nSn: " << sum << std::endl;
      return 0;
    }
  } else if (argc == 3) {
    //Get t1 and t2 in double form
    double t1 = atof(argv[1]);
    double t2 = atof(argv[2]);
    //get a and r
    a = t1;
    r = t2 / t1;
  }

  std::cout << "a: " << a << "\nr: " << r << std::endl;

  std::string solveCache;
  long int n;
  long double tn;
  long double sn;
  while(true) {
    //Query the user for the term position they want
    solveCache = "";
    std::cout << "Which term would you like to get?" << std::endl;
    std::cout << ">> " << std::flush;
    std::cin >> solveCache;
    n = atoi(solveCache.c_str());
    //print out the term at that pos and the sum at that pos.
    tn = getTerm(n, a, r);
    sn = getSum(n, a, r);
    std::cout << "t" << n << ": " << tn << "\nS" << n << ": " << sn << std::endl;
  }
  return 0;
}
