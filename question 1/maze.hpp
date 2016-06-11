// Prototype of Maze
//@file maze.hpp
#ifndef __MAZE_HPP__
#define __MAZE_HPP__

#define SQUARE_DIMENSION 25
#include <vector>
#include <queue>

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

  bool check_isfree(int, int);
  void print_solution(Grid&);
};

#endif // __MAZE_HPP__
