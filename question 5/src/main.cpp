// ECE 457a Assignment 2
// Question 5
//@file main.cpp
#include "cvrp.hpp"

int main(int argc, char *argv[])
{
  CVRP cvrp("A-VRP/A-n32-k5.vrp");
  cvrp.print_nodes();
  cvrp.solve();

  return 0;
}
