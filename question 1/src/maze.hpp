// Prototype of Maze
//@file maze.hpp
#ifndef __MAZE_HPP__
#define __MAZE_HPP__

#define SQUARE_DIMENSION 25

#include <vector>
#include <queue>
#include <string>

class Point;
class Maze
{
public:
  typedef std::vector<std::vector<Point*>> Grid;

  Maze(const std::string);
  ~Maze();

  void run_bfs();
  void run_dfs();
  void run_astar();
  void print_grid();
  
private:
  Grid* maze;
  Point* start;
  Point* end;

  bool check_isfree(int, int);
  void print_solution(Grid&);
  void parse_maze_file(const std::string);
};

#endif // __MAZE_HPP__
