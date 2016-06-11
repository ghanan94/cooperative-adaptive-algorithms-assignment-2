// ECE 457a Assignment 2
// Question 1
//@file question1.cpp
#include "maze.hpp"
#include <string>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Usage:\n");
    printf("\t%s <maze_file_path>\n", argv[0]);
    return 1;
  }

  Maze m(argv[1]);
  m.print_grid();
  m.run_dfs();
  m.print_solution();
  return 0;
}
