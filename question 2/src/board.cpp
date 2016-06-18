// Implementation file for Board class
//@file board.cpp
#include "board.hpp"

Board::Board():
current_player(Square::BLACK)
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

  // Position 0,3 has 10 black stones
  (*board)[0][3]->set_occupant(Square::BLACK);
  (*board)[0][3]->set_num_stones(10);

  // Position 3,0 has 10 white stones
  (*board)[3][0]->set_occupant(Square::WHITE);
  (*board)[3][0]->set_num_stones(10);
}

Board::Board(CongaBoard* board, Square::Player current_player):
board(board),
current_player(current_player) {}

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

Board* Board::travel(Square& square, Board::Direction direction)
{
  // Generate a new CongaBoard that is an exact copy of current
  Board::CongaBoard* new_board = new Board::CongaBoard();
  int x = square.get_x();
  int y = square.get_y();

  for (int x = 0; x < SQUARE_DIMENSION; ++x)
  {
    std::vector<Square*> column;

    for (int y = 0; y < SQUARE_DIMENSION; ++y)
    {
      Square* new_square = new Square(x, y);
      new_square->set_occupant((*board)[x][y]->get_occupant());
      new_square->set_num_stones((*board)[x][y]->get_num_stones());
      column.push_back(new_square);
    }

    new_board->push_back(column);
  }

  Square::Player sq_opponent = toggle_player(current_player);
  int delta_y = 0;
  int delta_x = 0;

  switch (direction)
  {
    case NORTH:
      delta_y = 1;
      break;

    case SOUTH:
      delta_y = -1;
      break;

    case EAST:
      delta_x = 1;
      break;

    case WEST:
      delta_x = -1;
      break;

    case NORTH_EAST:
      break;

    case NORTH_WEST:
      break;

    case SOUTH_EAST:
      break;

    case SOUTH_WEST:
      break;

    default:
      break;
  }

  for (int i = 1; i <= SQUARE_DIMENSION; ++i) {
    int sq_num_stones = (*new_board)[x][y]->get_num_stones();
    int delta_y_i = i * delta_y;
    int delta_x_i = i * delta_x;

    if (y + delta_y_i >= SQUARE_DIMENSION ||
      y + delta_y_i < 0 ||
      x + delta_x_i >= SQUARE_DIMENSION ||
      x + delta_x_i < 0 ||
      (*new_board)[x + delta_x_i][y + delta_y_i]->get_occupant() == sq_opponent)
    {
      if (i == 1)
      {
        // this should not happen
        printf("i == 1 in travel breaking\n");
        break;
      }

      // We have hit an opponent square or end of board so put all the
      // remaining stones on previous square
      (*new_board)[x + delta_x_i - delta_x][y + delta_y_i - delta_y]->set_num_stones((*new_board)[x + delta_x_i - delta_x][y + delta_y_i - delta_y]->get_num_stones() + sq_num_stones);
      sq_num_stones = 0;
      (*new_board)[x][y]->set_num_stones(sq_num_stones);
      break;
    } else
    {
      if (sq_num_stones >= i)
      {
        sq_num_stones -= i;
        (*new_board)[x + delta_x_i][y + delta_y_i]->set_num_stones((*new_board)[x + delta_x_i][y + delta_y_i]->get_num_stones() + i);
      } else {
        (*new_board)[x + delta_x_i][y + delta_y_i]->set_num_stones((*new_board)[x + delta_x_i][y + delta_y_i]->get_num_stones() + sq_num_stones);
        sq_num_stones = 0;
      }

      (*new_board)[x][y]->set_num_stones(sq_num_stones);
    }
  }

  return new Board(new_board, sq_opponent);
}
