// ECE 457a Assignment 2
// Question 5
//@file main.cpp
#include "cvrp.hpp"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("USAGE:\n\t%s <path to vrp file>\n", argv[0]);
    return 0;
  }

  CVRP cvrp(argv[1]);
  cvrp.solve(1000, 1, 0.85, 100);

  return 0;
}
