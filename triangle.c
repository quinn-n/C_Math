/*
Written to get a specific element of Pascal's triangle.
written by happylego91
TODO: make this multithreadded (start threads in each function)
Feb. 26 2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <progutil.h>
#define HELP_MSG "Usage: triangle <n> <r>\n"

long long int getTri(long long int n, long long int r) {
  //Make sure we don't go off the left isde of the triangle
  if(r < 0) return 0;
  //Make sure we don't go off the right side of the triangle
  if(r > n) return 0;
  if(n == 0) return 1;
  return (getTri(n-1, r-1) + getTri(n-1, r));
}

int main(int argc, char* argv[]) {
  if(!checkInputs(argc, argv, 3, HELP_MSG)) return 0;
  long long int n = atoll(argv[1]);
  long long int r = atoll(argv[2]);
  printf("%lli\n", getTri(n, r));
}
