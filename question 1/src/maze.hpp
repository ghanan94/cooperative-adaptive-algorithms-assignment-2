// Prototype of Maze
//@file maze.hpp
#ifndef __MAZE_HPP__
#define __MAZE_HPP__

#define SQUARE_DIMENSION 25

#include <vector>
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
  void print_solution();
  void reset();

private:
  Grid* maze;
  Point* start;
  Point* end;

  bool check_isfree(int, int);
  void parse_maze_file(const std::string);

  Point* get_up_point(Point*);
  Point* get_down_point(Point*);
  Point* get_left_point(Point*);
  Point* get_right_point(Point*);
};

#endif // __MAZE_HPP__
