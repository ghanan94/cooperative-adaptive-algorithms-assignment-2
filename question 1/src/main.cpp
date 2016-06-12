// ECE 457a Assignment 2
// Question 1
//@file question1.cpp
#include "maze.hpp"
#include <string>

int main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("Usage:\n");
    printf("\t%s <search_type> <maze_file_path>\n", argv[0]);
    printf("\tsearch_types: 1=bfs;2=dfs;3=astar");
    return 1;
  }

  int type = std::stoi(argv[1]);
  Maze m(argv[2]);
  m.print_grid();

  switch (type)
  {
    case 1:
      m.run_bfs();
      break;

    case 2:
      m.run_dfs();
      break;

    case 3:
      m.run_astar();
      break;
  }

  m.print_solution();

  return 0;
}
