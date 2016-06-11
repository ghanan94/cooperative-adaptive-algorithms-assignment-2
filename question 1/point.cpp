// Implementation file for class Point
//@file point.cpp
#include "point.hpp"

Point::Point(int x, int y, Point& parent):
x(x),
y(y),
parent(parent) {}
