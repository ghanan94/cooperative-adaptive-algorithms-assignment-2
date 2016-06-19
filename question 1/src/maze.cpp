// Implementation file for maze.hpp
//@file maze.cpp

#include "maze.hpp"
#include "point.hpp"
#include <fstream> // std::ifstream, std::getline
#include <iostream> // printf
#include <string> // std::string
#include <sstream> // std::stringstream
#include <queue> // std::queue
#include <deque> // std::deque
#include <unordered_set> // std::unordered_set
#include <algorithm>
#include <list>

bool maze_astar_function(Point* p1, Point* p2)
{
  return (p1->get_cost() + p1->get_est_cost() < p2->get_cost() + p2->get_est_cost());
}

Maze::Maze(const std::string file_name):
maze(0),
start(0),
end(0)
{
  parse_maze_file(file_name);
  start->set_cost(0);
  find_manchester_cost();
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

void Maze::reset()
{
  for (int y = 0; y < SQUARE_DIMENSION; ++y)
  {
    for (int x = 0; x < SQUARE_DIMENSION; ++x)
    {
      (*maze)[y][x]->reset();
    }
  }
  start->set_cost(0);
}

void Maze::find_manchester_cost()
{
  int x_diff, y_diff;
  for (int y = 0; y < SQUARE_DIMENSION; ++y)
  {
    y_diff = abs(y - end->get_y());
    for (int x = 0; x < SQUARE_DIMENSION; ++x)
    {
      x_diff = abs(x - end->get_x());
      (*maze)[y][x]->set_est_cost(y_diff + x_diff);
    }
  }
}
/*
 * NAME:          run_bfs
 *
 * DESCRIPTION:   Runs a breadth-first search to get from start to end points.
 *                the appropriate parents will be updated in each point.
 *
 * PARAMETERS:
 *  N/A
 *
 * RETURNS:
 *  N/A
 *
 * NOTES:         Priority is in the following order: Up->Right->Down->Left
 */
void Maze::run_bfs()
{
  //Reset any previous pathfinding operations
  reset();

  std::queue<Point*> bfs_fringe;
  bfs_fringe.push(start);

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
      if ((up_pt->get_is_visited() || up_pt->get_visiting()) &&
        (cnode->get_cost() + 1) < up_pt->get_cost())
      {
        up_pt->set_parent(cnode);
        up_pt->set_cost(cnode->get_cost() + 1);
      } else if (!up_pt->get_is_visited() && !up_pt->get_visiting())
      {
        bfs_fringe.push(up_pt);
        up_pt->set_cost(cnode->get_cost() + 1);
        up_pt->set_parent(cnode);
        up_pt->set_visiting();
      }
    }

    if (right_pt)
    {
      if ((right_pt->get_is_visited() || right_pt->get_visiting()) &&
        (cnode->get_cost() + 1) < right_pt->get_cost())
      {
        right_pt->set_parent(cnode);
        right_pt->set_cost(cnode->get_cost() + 1);
      } else if (!right_pt->get_is_visited() && !right_pt->get_visiting())
      {
        bfs_fringe.push(right_pt);
        right_pt->set_cost(cnode->get_cost() + 1);
        right_pt->set_parent(cnode);
        right_pt->set_visiting();
      }
    }

    if (down_pt)
    {
      if ((down_pt->get_is_visited() || down_pt->get_visiting()) &&
        (cnode->get_cost() + 1) < down_pt->get_cost())
      {
        down_pt->set_parent(cnode);
        down_pt->set_cost(cnode->get_cost() + 1);
      } else if (!down_pt->get_is_visited() && !down_pt->get_visiting())
      {
        bfs_fringe.push(down_pt);
        down_pt->set_cost(cnode->get_cost() + 1);
        down_pt->set_parent(cnode);
        down_pt->set_visiting();
      }
    }

    if (left_pt)
    {
      if ((left_pt->get_is_visited() || left_pt->get_visiting()) &&
        (cnode->get_cost() + 1) < left_pt->get_cost())
      {
        left_pt->set_parent(cnode);
        left_pt->set_cost(cnode->get_cost() + 1);
      } else if (!left_pt->get_is_visited() && !left_pt->get_visiting())
      {
        bfs_fringe.push(left_pt);
        left_pt->set_cost(cnode->get_cost() + 1);
        left_pt->set_parent(cnode);
        left_pt->set_visiting();
      }
    }
    cnode->set_visited();
    bfs_fringe.pop();
  }
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
  reset();
  std::deque<Point *> dfs_fringe;

  start->set_cost(0);
  start->set_visiting();

  dfs_fringe.push_front(start);

  while (dfs_fringe.size())
  {
    Point *p = dfs_fringe.front();
    dfs_fringe.pop_front();

    p->set_visited();

    //printf("Visiting (%d, %d)\n", p->get_x(), p->get_y());
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
      if(l_p->get_is_visited() || l_p->get_visiting())
      {
        if (l_p->get_cost() > new_cost) {
          l_p->set_cost(new_cost);
          l_p->set_parent(p);
        }
      } else
      {
        l_p->set_cost(new_cost);
        l_p->set_parent(p);
        l_p->set_visiting();
        dfs_fringe.push_front(l_p);
      }
    }

    if (d_p)
    {
      if(d_p->get_is_visited() || d_p->get_visiting())
      {
        if (d_p->get_cost() > new_cost) {
          d_p->set_cost(new_cost);
          d_p->set_parent(p);
        }
      } else
      {
        d_p->set_cost(new_cost);
        d_p->set_parent(p);
        d_p->set_visiting();
        dfs_fringe.push_front(d_p);
      }
    }

    if (r_p)
    {
      if(r_p->get_is_visited() || r_p->get_visiting())
      {
        if (r_p->get_cost() > new_cost) {
          r_p->set_cost(new_cost);
          r_p->set_parent(p);
        }
      } else
      {
        r_p->set_cost(new_cost);
        r_p->set_parent(p);
        r_p->set_visiting();
        dfs_fringe.push_front(r_p);
      }
    }

    if (u_p)
    {
      if(u_p->get_is_visited() || u_p->get_visiting())
      {
        if (u_p->get_cost() > new_cost) {
          u_p->set_cost(new_cost);
          u_p->set_parent(p);
        }
      } else
      {
        u_p->set_cost(new_cost);
        u_p->set_parent(p);
        u_p->set_visiting();
        dfs_fringe.push_front(u_p);
      }
    }
  }
}

/*
 * NAME:          run_dfs
 *
 * DESCRIPTION:   Runs an A* search to get from start to end points.
 *                the appropriate parents will be updated in each point.
 *
 * PARAMETERS:
 *  N/A
 *
 * RETURNS:
 *  N/A
 */
void Maze::run_astar()
{
  //Reset any previous pathfinding operations
  reset();

  std::list<Point*> astar_fringe;
  astar_fringe.push_back(start);

  while (!astar_fringe.empty())
  {
    astar_fringe.sort(maze_astar_function);

    Point* cnode = astar_fringe.front();
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
      if ((up_pt->get_is_visited() || up_pt->get_visiting()) &&
        (cnode->get_cost() + 1) < up_pt->get_cost())
      {
        up_pt->set_parent(cnode);
        up_pt->set_cost(cnode->get_cost() + 1);
      } else if (!up_pt->get_is_visited() && !up_pt->get_visiting())
      {
        astar_fringe.push_back(up_pt);
        up_pt->set_cost(cnode->get_cost() + 1);
        up_pt->set_parent(cnode);
        up_pt->set_visiting();
      }
    }

    if (right_pt)
    {
      if ((right_pt->get_is_visited() || right_pt->get_visiting()) &&
        (cnode->get_cost() + 1) < right_pt->get_cost())
      {
        right_pt->set_parent(cnode);
        right_pt->set_cost(cnode->get_cost() + 1);
      } else if (!right_pt->get_is_visited() && !right_pt->get_visiting())
      {
        astar_fringe.push_back(right_pt);
        right_pt->set_cost(cnode->get_cost() + 1);
        right_pt->set_parent(cnode);
        right_pt->set_visiting();
      }
    }

    if (down_pt)
    {
      if ((down_pt->get_is_visited() || down_pt->get_visiting()) &&
        (cnode->get_cost() + 1) < down_pt->get_cost())
      {
        down_pt->set_parent(cnode);
        down_pt->set_cost(cnode->get_cost() + 1);
      } else if (!down_pt->get_is_visited() && !down_pt->get_visiting())
      {
        astar_fringe.push_back(down_pt);
        down_pt->set_cost(cnode->get_cost() + 1);
        down_pt->set_parent(cnode);
        down_pt->set_visiting();
      }
    }

    if (left_pt)
    {
      if ((left_pt->get_is_visited() || left_pt->get_visiting()) &&
        (cnode->get_cost() + 1) < left_pt->get_cost())
      {
        left_pt->set_parent(cnode);
        left_pt->set_cost(cnode->get_cost() + 1);
      } else if (!left_pt->get_is_visited() && !left_pt->get_visiting())
      {
        astar_fringe.push_back(left_pt);
        left_pt->set_cost(cnode->get_cost() + 1);
        left_pt->set_parent(cnode);
        left_pt->set_visiting();
      }
    }

    cnode->set_visited();
    astar_fringe.pop_front();
  }
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
  if (check_isfree(old_point->get_x() + 1, old_point->get_y()))
  {
    return (*maze)[old_point->get_y()][old_point->get_x() + 1];
  } else
  {
    return 0;
  }
}
/*******************************************************************************
                          Input/Output Functions
*******************************************************************************/

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
    s_x = std::stoi(data);
    std::getline(linestream_start, data, ' ');
    s_y = std::stoi(data);

    // Get end location; x y
    std::getline(maze_file, line);
    std::stringstream linestream_end(line);
    std::getline(linestream_end, data, ' ');
    e_x = std::stoi(data);
    std::getline(linestream_end, data, ' ');
    e_y = std::stoi(data);

    // Parse maze; 0 = not blocked; 1 = blocked
    for (int y = SQUARE_DIMENSION - 1; y >= 0; --y)
    {
      std::getline(maze_file, line);
      std::stringstream linestream(line);

      for (int x = 0; x < SQUARE_DIMENSION; ++x)
      {
        std::getline(linestream, data, ' ');
        bool is_blocked;
        is_blocked = data[0] != '0';

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
