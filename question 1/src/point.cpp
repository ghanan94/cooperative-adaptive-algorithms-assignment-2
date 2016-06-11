// Implementation file for class Point
//@file point.cpp
#include "point.hpp"

Point::Point(int x, int y, bool is_blocked):
x(x),
y(y),
is_blocked(is_blocked),
is_visited(false),
parent(0) {}

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
}

void Point::set_visited()
{
  is_visited = true;
}
