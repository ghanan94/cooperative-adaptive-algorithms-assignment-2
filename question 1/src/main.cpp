// ECE 457a Assignment 2
// Question 1
//@file question1.cpp
#include "maze.hpp"
#include <string>

int main()
{
  Maze m("mazes/maze1.txt");
  m.print_grid();
  return 0;
}
