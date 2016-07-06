// ECE 457a Assignment 2
// Question 5
//@file main.cpp
#include "cvrp.hpp"

int main(int argc, char *argv[])
{
  CVRP cvrp("A-VRP/A-n32-k5.vrp");
  cvrp.print_nodes();
  cvrp.solve(1000, 1, 0.85, 100);

  return 0;
}
