// Implementation file for class Point
//@file point.cpp
#include "point.hpp"
#include <climits>

Point::Point(int x, int y, bool is_blocked):
x(x),
y(y),
is_blocked(is_blocked),
is_visited(false),
parent(0),
cost(INT_MAX),
visiting(false) {}

Point::~Point()
{}

const int Point::get_x()
{
  return x;
}

const int Point::get_y()
{
  return y;
}

bool Point::get_is_blocked()
{
  return is_blocked;
}

bool Point::get_is_visited()
{
  return is_visited;
}

Point* Point::get_parent()
{
  return parent;
}

void Point::reset()
{
  is_visited = false;
  parent = 0;
  cost = INT_MAX;
  visiting = false;
}

void Point::set_visited()
{
  is_visited = true;
}

int Point::get_cost()
{
  return cost;
}

void Point::set_cost(int new_cost)
{
  cost = new_cost;
}

void Point::set_parent(Point* new_parent)
{
  parent = new_parent;
}

bool Point::get_visiting()
{
  return visiting;
}

void Point::set_visiting()
{
  visiting = true;
}
