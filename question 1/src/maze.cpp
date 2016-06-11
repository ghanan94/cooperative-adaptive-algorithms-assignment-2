// Implementation file for maze.hpp
//@file maze.cpp

#include "maze.hpp"
#include "point.hpp"
#include <fstream> // std::ifstream, std::getline
#include <iostream>
#include <string> // std::string
#include <sstream> // std::stringstream
#include <queue> // std::queue

Maze::Maze(const std::string file_name):
maze(0),
start(0),
end(0)
{
  parse_maze_file(file_name);
}

Maze::~Maze()
{
  delete maze;
  maze = 0;
  // start and end will be deleted by the maze deconstructor
  // as they are elements within the maze vector
  start = 0;
  end = 0;
}

bool Maze::check_isfree(int x, int y)
{
  if (x >= 0 && x < SQUARE_DIMENSION && y >= 0 && y < SQUARE_DIMENSION)
  {
    return !(*maze)[x][y]->get_is_blocked();
  } else
  {
    return false;
  }

}

void Maze::print_solution(Grid& solution)
{
  return;
}

//Priority is broken in the following order:
//1. North 2. East 3. South 4. West
void Maze::run_bfs()
{
  std::queue<Point*> bfs_fringe;
  bfs_fringe.push(start);

  /*while (!bfs_fringe.empty())
  {
    Point* cnode = bfs_fringe.front();
  }*/

  return;
}

void Maze::run_dfs()
{
  return;
}

void Maze::run_astar()
{
  return;
}

Point* Maze::get_up_point(Point* old_point)
{
  if (check_isfree(old_point->get_x(), old_point->get_y() + 1))
  {
    return (*maze)[old_point->get_x()][old_point->get_y() + 1];
  } else
  {
    return 0;
  }
}

Point* Maze::get_down_point(Point* old_point)
{
  if (check_isfree(old_point->get_x(), old_point->get_y() - 1))
  {
    return (*maze)[old_point->get_x()][old_point->get_y() - 1];
  } else
  {
    return 0;
  }
}

Point* Maze::get_left_point(Point* old_point)
{
  if (check_isfree(old_point->get_x() - 1, old_point->get_y()))
  {
    return (*maze)[old_point->get_x() - 1][old_point->get_y()];
  } else
  {
    return 0;
  }
}

Point* Maze::get_right_point(Point* old_point)
{
  if (check_isfree(old_point->get_x() + 1,old_point->get_y()))
  {
    return (*maze)[old_point->get_x() + 1][old_point->get_y()];
  } else
  {
    return 0;
  }
}

void Maze::print_grid() {
  const char* hyphens = std::string(SQUARE_DIMENSION * 2 + 1, '-').c_str();
  printf(" %s\n", hyphens);

  for (int x = SQUARE_DIMENSION - 1; x >= 0; --x)
  {
    printf("| ");

    for (int y = 0; y < SQUARE_DIMENSION; ++y)
    {
      Point* point = (*maze)[x][y];

      if (start == point)
      {
        printf("S ");
      } else if (end == point)
      {
        printf("E ");
      } else
      {
        printf("%c ", point->get_is_blocked() ? '#' : ' ');
      }
    }

    printf("| \n");
  }

  printf(" %s\n", hyphens);
}

void Maze::parse_maze_file(const std::string file_name)
{
  std::ifstream maze_file;
  std::string line;
  std::string data;

  int s_x, s_y, e_x, e_y;
  maze_file.open(file_name);

  // If a maze already exists, delete/free it
  if (maze)
  {
    delete maze;
    start = 0;
    end = 0;
  }

  maze = new Grid();

  for (int x = 0; x < SQUARE_DIMENSION; ++x)
  {
    std::vector<Point *> row;
    maze->push_back(row);
  }

  if (maze_file.is_open())
  {
    // Get the start location; x y
    std::getline(maze_file, line);
    std::stringstream linestream_start(line);
    std::getline(linestream_start, data, ' ');
    linestream_start >> s_x;
    linestream_start >> s_y;

    // Get end location; x y
    std::getline(maze_file, line);
    std::stringstream linestream_end(line);
    std::getline(linestream_end, data, ' ');
    linestream_end >> e_x;
    linestream_end >> e_y;

    // Parse maze; 0 = not blocked; 1 = blocked
    for (int x = SQUARE_DIMENSION - 1; x >= 0; --x)
    {
      std::getline(maze_file, line);
      std::stringstream linestream(line);
      std::getline(linestream, data, ' ');

      for (int y = 0; y < SQUARE_DIMENSION; ++y)
      {
        bool is_blocked;
        linestream >> is_blocked;

        Point* new_point = new Point(x, y, is_blocked);
        (*maze)[x].push_back(new_point);

        if (x == s_x && y == s_y)
        {
          start = new_point;
        } else if (x == e_x && y == e_y)
        {
          end = new_point;
        }
      }
    }

    maze_file.close();
  } else
  {
    printf("File error\n");
  }
}
