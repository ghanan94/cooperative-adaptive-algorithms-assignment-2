// Implementation file for class Point
//@file point.cpp
#include "point.hpp"

Point::Point(int x, int y, bool is_empty, Point& parent):
x(x),
y(y),
is_empty(is_empty),
parent(parent) {}

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

Point& Point::get_parent()
{
  return parent;
}
