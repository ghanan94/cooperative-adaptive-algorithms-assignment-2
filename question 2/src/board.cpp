// Implementation file for Board class
//@file board.cpp
#include "board.hpp"

Board::Board()
{
  board = new CongaBoard();
  for (int x = 0; x < SQUARE_DIMENSION; ++x)
  {
    std::vector<Square*> column;
    for (int y = 0; y < SQUARE_DIMENSION; ++y)
    {
      //Assignment says bottom-left is (1,1), acknowledge that our Conga Board
      //is zero-indexed instead (i.e. bottom-left is (0,0))
      Square* new_square = new Square(x, y);
      column.push_back(new_square);
    }
    board->push_back(column);
  }
}

Board::~Board()
{
  delete board; //calls delete on all pointers it holds
}

void Board::simulate_game()
{
}

Square::Player Board::toggle_player(Square::Player curr_player)
{
  return (curr_player == Square::BLACK ? Square::WHITE : Square::BLACK);
}

std::vector<Board::Direction>
Board::find_available_directions(Square& square)
{
  std::vector<Board::Direction> available_directions;
  Square::Player sq_occupant = square.get_occupant();
  if (sq_occupant == Square::NONE)
  {
    return available_directions;
  }

  Square::Player sq_opponent = toggle_player(sq_occupant);

// check to see if movement on 8 directions is within boundaries first
// then check the board to make sure at last one adjacent space is available
  if (square.get_y() + 1 < SQUARE_DIMENSION &&
    (*board)[square.get_x()][square.get_y() + 1]->get_occupant() != sq_opponent)
  {
    available_directions.push_back(Board::NORTH);
  }

  if (square.get_y() - 1 < SQUARE_DIMENSION &&
    (*board)[square.get_x()][square.get_y() - 1]->get_occupant() != sq_opponent)
  {
    available_directions.push_back(Board::SOUTH);
  }

  if (square.get_x() + 1 < SQUARE_DIMENSION &&
    (*board)[square.get_x() + 1][square.get_y()]->get_occupant() != sq_opponent)
  {
    available_directions.push_back(Board::EAST);
  }

  if (square.get_x() - 1 < SQUARE_DIMENSION &&
    (*board)[square.get_x() - 1][square.get_y()]->get_occupant() != sq_opponent)
  {
    available_directions.push_back(Board::WEST);
  }

  if (square.get_x() + 1 < SQUARE_DIMENSION && // check x + 1
    square.get_y() + 1 < SQUARE_DIMENSION && // check y + 1
      (*board)[square.get_x() + 1][square.get_y() + 1]->get_occupant()
        != sq_opponent) //check that diagonal is not blocked
  {
    available_directions.push_back(Board::NORTH_EAST);
  }

  if (square.get_x() + 1 < SQUARE_DIMENSION &&
    square.get_y() - 1 < SQUARE_DIMENSION &&
      (*board)[square.get_x() + 1][square.get_y() - 1]->get_occupant()
        != sq_opponent)
  {
    available_directions.push_back(Board::SOUTH_EAST);
  }

  if (square.get_x() - 1 < SQUARE_DIMENSION &&
    square.get_y() + 1 < SQUARE_DIMENSION &&
      (*board)[square.get_x() - 1][square.get_y() + 1]->get_occupant()
        != sq_opponent)
  {
    available_directions.push_back(Board::NORTH_WEST);
  }

  if (square.get_x() - 1 < SQUARE_DIMENSION &&
    square.get_y() - 1 < SQUARE_DIMENSION &&
      (*board)[square.get_x() - 1][square.get_y() - 1]->get_occupant()
        != sq_opponent)
  {
    available_directions.push_back(Board::SOUTH_WEST);
  }

  return available_directions;
}
