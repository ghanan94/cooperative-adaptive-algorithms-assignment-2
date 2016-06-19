// ECE 457a Assignment 2
// Question 3
//@file main.cpp
#include "qap.hpp"

int main(int argc, char *argv[])
{
  QAP qap("flow_distance_tables/Flow.csv", "flow_distance_tables//Distance.csv");
  qap.print_flow_table();
  qap.print_distance_table();
  qap.find_solution();
  return 0;
}
