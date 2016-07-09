// Implementation file of class Square
//@file square.cpp
#include "square.hpp"
Square::Square(int x, int y):
x(x),
y(y),
occupant(NONE),
num_stones(0) {}

Square::~Square()
{}

const int Square::get_x()
{
  return x;
}

const int Square::get_y()
{
  return y;
}

Square::Player Square::get_occupant()
{
  return occupant;
}

void Square::set_occupant(Player new_occupant)
{
  occupant = new_occupant;
}

int Square::get_num_stones()
{
  return num_stones;
}

void Square::set_num_stones(int new_num)
{
  num_stones = new_num;
}
