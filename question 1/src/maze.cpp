// Implementation file for maze.hpp
//@file maze.cpp

#include "maze.hpp"
#include "point.hpp"
#include <fstream> // std::ifstream, std::getline
#include <iostream>
#include <string> // std::string
#include <sstream> // std::stringstream
#include <queue> // std::queue
#include <deque> // std::deque
#include <unordered_set> // std::unordered_set

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
    return !(*maze)[y][x]->get_is_blocked();
  } else
  {
    return false;
  }
}

void Maze::print_solution()
{
  std::unordered_set<Point *> solution_path;
  Point *temp = end->get_parent();

  while (temp) {
    solution_path.insert(temp);
    temp = temp->get_parent();
  }

  const char* hyphens = std::string(SQUARE_DIMENSION * 2 + 1, '-').c_str();
  printf(" %s\n", hyphens);

  for (int y = SQUARE_DIMENSION - 1; y >= 0; --y)
  {
    printf("| ");

    for (int x = 0; x < SQUARE_DIMENSION; ++x)
    {
      Point* point = (*maze)[y][x];

      if (start == point)
      {
        printf("S ");
      } else if (end == point)
      {
        printf("E ");
      } else if (solution_path.end() != solution_path.find(point))
      {
        if (point == get_up_point(point->get_parent()))
        {
          printf("^ ");
        } else if (point == get_down_point(point->get_parent()))
        {
          printf("v ");
        } else if (point == get_right_point(point->get_parent()))
        {
          printf("> ");
        } else if (point == get_left_point(point->get_parent()))
        {
          printf("< ");
        } else
        {
          printf("* ");
        }
      } else
      {
        printf("%c ", point->get_is_blocked() ? '#' : ' ');
      }
    }

    printf("| \n");
  }

  printf(" %s\n", hyphens);

}

//Priority is broken in the following order:
//1. North 2. East 3. South 4. West
void Maze::run_bfs()
{
  std::queue<Point*> bfs_fringe;
  bfs_fringe.push(start);

  for (int y = 0; y < SQUARE_DIMENSION; ++y)
  {
    for (int x = 0; x < SQUARE_DIMENSION; ++x)
    {
      (*maze)[y][x]->reset();
    }
  }

  while (!bfs_fringe.empty())
  {
    Point* cnode = bfs_fringe.front();
    if (cnode == end)
    {
      return;
    }

    Point* up_pt = get_up_point(cnode);
    Point* right_pt = get_right_point(cnode);
    Point* down_pt = get_down_point(cnode);
    Point* left_pt = get_left_point(cnode);


    if (up_pt)
    {
      if (up_pt->get_is_visited() &&
        (cnode->get_cost() + 1) < up_pt->get_cost())
      {
        up_pt->set_parent(cnode);
        up_pt->set_cost(cnode->get_cost() + 1);
      } else if (!up_pt->get_is_visited())
      {
        bfs_fringe.push(up_pt);
        up_pt->set_cost(cnode->get_cost() + 1);
        up_pt->set_parent(cnode);
      }
    }

    if (right_pt)
    {
      if (right_pt->get_is_visited() &&
        (cnode->get_cost() + 1) < right_pt->get_cost())
      {
        right_pt->set_parent(cnode);
        right_pt->set_cost(cnode->get_cost() + 1);
      } else if (!right_pt->get_is_visited())
      {
        bfs_fringe.push(right_pt);
        right_pt->set_cost(cnode->get_cost() + 1);
        right_pt->set_parent(cnode);
      }
    }

    if (down_pt)
    {
      if (down_pt->get_is_visited() &&
        (cnode->get_cost() + 1) < down_pt->get_cost())
      {
        down_pt->set_parent(cnode);
        down_pt->set_cost(cnode->get_cost() + 1);
      } else if (!down_pt->get_is_visited())
      {
        bfs_fringe.push(down_pt);
        down_pt->set_cost(cnode->get_cost() + 1);
        down_pt->set_parent(cnode);
      }
    }

    if (left_pt)
    {
      if (left_pt->get_is_visited() &&
        (cnode->get_cost() + 1) < left_pt->get_cost())
      {
        left_pt->set_parent(cnode);
        left_pt->set_cost(cnode->get_cost() + 1);
      } else if (!left_pt->get_is_visited())
      {
        bfs_fringe.push(left_pt);
        left_pt->set_cost(cnode->get_cost() + 1);
        left_pt->set_parent(cnode);
      }
    }
    cnode->set_visited();
    bfs_fringe.pop();
  }
  return;
}


/*
 * NAME:          run_dfs
 *
 * DESCRIPTION:   Runs a depth-first search to get from start to end points.
 *                the appropriate parents will be updated in each point.
 *
 * PARAMETERS:
 *  N/A
 *
 * RETURNS:
 *  N/A
 */
void Maze::run_dfs()
{
  std::deque<Point *> dfs_fringe;

  // Reset all points
  for (int y = 0; y < SQUARE_DIMENSION; ++y)
  {
    for (int x = 0; x < SQUARE_DIMENSION; ++x)
    {
      (*maze)[y][x]->reset();
    }
  }

  start->set_cost(0);
  dfs_fringe.push_front(start);

  while (dfs_fringe.size())
  {
    Point *p = dfs_fringe.front();
    dfs_fringe.pop_front();

    if (p->get_is_visited()) {
      printf("Visting node already visited\n");
      continue;
    }

    p->set_visited();

    printf("Visiting (%d, %d)\n", p->get_x(), p->get_y());
    if (p == end) {
      // got solution
      break;
    }

    Point *u_p = get_up_point(p);
    Point *r_p = get_right_point(p);
    Point *d_p = get_down_point(p);
    Point *l_p = get_left_point(p);
    int new_cost = p->get_cost() + 1;

    if (l_p)
    {
      if(l_p->get_is_visited())
      {
        if (l_p->get_cost() > new_cost) {
          l_p->set_cost(new_cost);
          l_p->set_parent(p);
        }
      } else
      {
        l_p->set_cost(new_cost);
        l_p->set_parent(p);
        dfs_fringe.push_front(l_p);
      }
    }

    if (d_p)
    {
      if(d_p->get_is_visited())
      {
        if (d_p->get_cost() > new_cost) {
          d_p->set_cost(new_cost);
          d_p->set_parent(p);
        }
      } else
      {
        d_p->set_cost(new_cost);
        d_p->set_parent(p);
        dfs_fringe.push_front(d_p);
      }
    }

    if (r_p)
    {
      if(r_p->get_is_visited())
      {
        if (r_p->get_cost() > new_cost) {
          r_p->set_cost(new_cost);
          r_p->set_parent(p);
        }
      } else
      {
        r_p->set_cost(new_cost);
        r_p->set_parent(p);
        dfs_fringe.push_front(r_p);
      }
    }

    if (u_p)
    {
      if(u_p->get_is_visited())
      {
        if (u_p->get_cost() > new_cost) {
          u_p->set_cost(new_cost);
          u_p->set_parent(p);
        }
      } else
      {
        u_p->set_cost(new_cost);
        u_p->set_parent(p);
        dfs_fringe.push_front(u_p);
      }
    }
  }
}

void Maze::run_astar()
{
  return;
}

Point* Maze::get_up_point(Point* old_point)
{
  if (check_isfree(old_point->get_x(), old_point->get_y() + 1))
  {
    return (*maze)[old_point->get_y() + 1][old_point->get_x()];
  } else
  {
    return 0;
  }
}

Point* Maze::get_down_point(Point* old_point)
{
  if (check_isfree(old_point->get_x(), old_point->get_y() - 1))
  {
    return (*maze)[old_point->get_y() - 1][old_point->get_x()];
  } else
  {
    return 0;
  }
}

Point* Maze::get_left_point(Point* old_point)
{
  if (check_isfree(old_point->get_x() - 1, old_point->get_y()))
  {
    return (*maze)[old_point->get_y()][old_point->get_x() - 1];
  } else
  {
    return 0;
  }
}

Point* Maze::get_right_point(Point* old_point)
{
  if (check_isfree(old_point->get_x() + 1,old_point->get_y()))
  {
    return (*maze)[old_point->get_y()][old_point->get_x() + 1];
  } else
  {
    return 0;
  }
}

void Maze::print_grid() {
  const char* hyphens = std::string(SQUARE_DIMENSION * 2 + 1, '-').c_str();
  printf(" %s\n", hyphens);

  for (int y = SQUARE_DIMENSION - 1; y >= 0; --y)
  {
    printf("| ");

    for (int x = 0; x < SQUARE_DIMENSION; ++x)
    {
      Point* point = (*maze)[y][x];

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

  for (int y = 0; y < SQUARE_DIMENSION; ++y)
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
    for (int y = SQUARE_DIMENSION - 1; y >= 0; --y)
    {
      std::getline(maze_file, line);
      std::stringstream linestream(line);
      std::getline(linestream, data, ' ');

      for (int x = 0; x < SQUARE_DIMENSION; ++x)
      {
        bool is_blocked;
        linestream >> is_blocked;

        Point* new_point = new Point(x, y, is_blocked);
        (*maze)[y].push_back(new_point);

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
