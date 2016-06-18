// Testing file for Question2
//@file main.cpp
#include "board.hpp"

int main()
{
  Board conga_board;
  conga_board.print_board();
  conga_board.do_best_move();
  conga_board.print_board();
  conga_board.do_random_move();
  conga_board.print_board();
  return 0;
}
