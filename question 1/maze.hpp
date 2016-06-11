// Prototype of Maze
//@file maze.hpp
#ifndef __MAZE_HPP
#define __MAZE_HPP

#define SQUARE_DIMENSION 25
#include <vector>

class Point;
class Maze
{
public:
  typedef std::vector<std::vector<Point>> Grid;

  Maze();
  ~Maze();

  void run_bfs();
  void run_dfs();
  void run_astar();
private:
  Grid* maze;
  Point& start;
  Point& end;

  bool check_isfree(int x, int y);
  void print_solution(Grid& solution);
};

#endif // __MAZE_HPP
