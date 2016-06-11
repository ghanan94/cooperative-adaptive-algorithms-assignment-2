// Implementation file for class Point
//@file point.cpp
#include "point.hpp"

Point::Point(int x, int y, Point& parent):
x(x),
y(y),
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
