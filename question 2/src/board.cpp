// Implementation file for Board class
//@file board.cpp
#include "board.hpp"
#include <string>
#include <iostream>
#include <climits>
#include <ctime>
#include <random>

#define MIN_MAX_TREE_DEPTH 3

Board::Board():
current_player(Square::BLACK),
game_over(false)
{
  std::srand(time(0));

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
current_player(current_player),
game_over(false) {}

Board::~Board()
{
  for (int x = 0; x < SQUARE_DIMENSION; ++x)
  {
    for (int y = 0; y < SQUARE_DIMENSION; ++y)
    {
      delete (*board)[x][y];
    }
  }

  delete board; //calls delete on all pointers it holds
}

void Board::simulate_game()
{
  unsigned int moves = 0;

  print_board();

  while (!game_over)
  {
    switch (current_player)
    {
      case Square::BLACK:
        do_best_move();
        break;

      case Square::WHITE:
        do_random_move();
        break;

      default:
        printf("default in simulate_game?\n");
        break;
    }

    print_board();

    if (game_over)
    {
      printf("Game over after %u moves\n", moves);
      break;
    }

    ++moves;
  }
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

  if (square.get_y() - 1 >= 0 &&
    (*board)[square.get_x()][square.get_y() - 1]->get_occupant() != sq_opponent)
  {
    available_directions.push_back(Board::SOUTH);
  }

  if (square.get_x() + 1 < SQUARE_DIMENSION &&
    (*board)[square.get_x() + 1][square.get_y()]->get_occupant() != sq_opponent)
  {
    available_directions.push_back(Board::EAST);
  }

  if (square.get_x() - 1 >= 0 &&
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
    square.get_y() - 1 >= 0 &&
      (*board)[square.get_x() + 1][square.get_y() - 1]->get_occupant()
        != sq_opponent)
  {
    available_directions.push_back(Board::SOUTH_EAST);
  }

  if (square.get_x() - 1 >= 0 &&
    square.get_y() + 1 < SQUARE_DIMENSION &&
      (*board)[square.get_x() - 1][square.get_y() + 1]->get_occupant()
        != sq_opponent)
  {
    available_directions.push_back(Board::NORTH_WEST);
  }

  if (square.get_x() - 1 >= 0 &&
    square.get_y() - 1 >= 0 &&
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
      delta_y = 1;
      delta_x = 1;
      break;

    case NORTH_WEST:
      delta_y = 1;
      delta_x = -1;
      break;

    case SOUTH_EAST:
      delta_y = -1;
      delta_x = 1;
      break;

    case SOUTH_WEST:
      delta_y = -1;
      delta_x = -1;
      break;

    default:
      break;
  }

  for (int i = 1; i <= SQUARE_DIMENSION; ++i)
  {
    int sq_num_stones = (*new_board)[x][y]->get_num_stones();
    int y_i = y + i * delta_y;
    int x_i = x + i * delta_x;

    if (y_i >= SQUARE_DIMENSION ||
      y_i < 0 ||
      x_i >= SQUARE_DIMENSION ||
      x_i < 0 ||
      (*new_board)[x_i][y_i]->get_occupant() == sq_opponent)
    {
      if (i == 1)
      {
        // this should not happen
        printf("i == 1 in travel breaking\n");
        break;
      }

      // We have hit an opponent square or end of board so put all the
      // remaining stones on previous square
      (*new_board)[x_i - delta_x][y_i - delta_y]->set_num_stones((*new_board)[x_i - delta_x][y_i - delta_y]->get_num_stones() + sq_num_stones);
      sq_num_stones = 0;
    } else
    {
      if (sq_num_stones >= i)
      {
        sq_num_stones -= i;
        (*new_board)[x_i][y_i]->set_num_stones((*new_board)[x_i][y_i]->get_num_stones() + i);
      } else
      {
        (*new_board)[x_i][y_i]->set_num_stones((*new_board)[x_i][y_i]->get_num_stones() + sq_num_stones);
        sq_num_stones = 0;
      }

      (*new_board)[x_i][y_i]->set_occupant(current_player);
    }

    (*new_board)[x][y]->set_num_stones(sq_num_stones);

    if (sq_num_stones == 0)
    {
      (*new_board)[x][y]->set_occupant(Square::NONE);
      break;
    }
  }

  return new Board(new_board, sq_opponent);
}

void Board::print_board()
{
  printf("\nPlayer to move: %s\n", current_player == Square::BLACK ? "BLACK" : "WHITE");

  const char* hyphens = std::string(SQUARE_DIMENSION * 6 - 1, '-').c_str();
  printf(" %s\n", hyphens);

  for (int y = SQUARE_DIMENSION - 1; y >= 0; --y)
  {
    for (int x = 0; x < SQUARE_DIMENSION; ++x)
    {
      Square* sq = (*board)[x][y];
      printf("| %s%-2d ", sq->get_occupant() == Square::BLACK ? "B" : (sq->get_occupant() == Square::WHITE ? "W" : "E"), sq->get_num_stones());
    }

    printf("|\n");
  }

  printf(" %s\n", hyphens);
}

//Evaluate function 1
//The idea is this: the game score of the board is the number of moves
//with squares_with_Multistone you may
//make minus the number of moves your opponent may make
/*
-----------------------
| B10 | E0  | E0  | E0  |
| E0  | E0  | E0  | E0  |
| E0  | E0  | E0  | E0  |
| E0  | E0  | E0  | W10 |
 -----------------------

 is a gamescore of 0 (3 - 3)

 -----------------------
| E0 | E0  | E0  | E0  |
| B1 | E0  | E0  | E0  |
| B2 | E0  | E0  | E0  |
| B7 | W9  | W1  | E0  |
-----------------------
 is a gamescore of 1 (4 - 3)
 -----------------------
| B0 | E0  | E0  | B1  |
| B1 | E0  | B2  | W1  |
| B2 | B4  | W8  | E0  |
| B0 | E0  | E1  | W0  |
-----------------------
is a gamescore of 7 (13 - 6)

int Board::evaluate(Square::Player evaluate_for_player)
{
  int player_score = 0;
  int opponent_score = 0;
  for (int i = 0; i < SQUARE_DIMENSION; ++i)
  {
    for (int j = 0; j < SQUARE_DIMENSION; ++j)
    {
      if ((*board)[i][j]->get_num_stones() > 1)
      {
        if ((*board)[i][j]->get_occupant() == evaluate_for_player)
        {
          player_score += (find_available_directions(*(*board)[i][j])).size();
        } else
        {
          opponent_score += (find_available_directions(*(*board)[i][j])).size();
        }
      }
    }
  }
  return (player_score - opponent_score);
}*/

//gamescore is based on the location of the opponents pieces
/*
-----------------------
| 0 |  1  |  2  | 3  |
| -1|  0  |  1  | 2  |
| -2|  -1 |  0  | 1  |
| -3|  -2 |  -1 | 0  |
-----------------------

int Board::evaluate(Square::Player evaluate_for_player)
{
  int player_score = 0;
  for (int x = 0; x < SQUARE_DIMENSION; ++x)
  {
    for (int y = 0; y < SQUARE_DIMENSION; ++y)
    {
      if ((*board)[x][y]->get_occupant() == toggle_player(evaluate_for_player))
      {
        int indexSum = x + y;
        switch(indexSum)
        {
          case (0):
            player_score -= 3;
            break;
          case(1):
            player_score -= 2;
            break;
          case(2):
            player_score -= 1;
            break;
          case(4):
            player_score += 1;
            break;
          case(5):
            player_score += 2;
            break;
          case(6):
            player_score += 3;
            break;
          default:
            break;
        }
      }
    }
  }

  return player_score;
}*/
// This evaluation is similar to the first one, without the requirement of >1
//stones needed
/*int Board::evaluate(Square::Player evaluate_for_player)
{
  int player_score = 0;
  int opponent_score = 0;
  for (int i = 0; i < SQUARE_DIMENSION; ++i)
  {
    for (int j = 0; j < SQUARE_DIMENSION; ++j)
    {
      if ((*board)[i][j]->get_occupant() == evaluate_for_player)
      {
        player_score += (find_available_directions(*(*board)[i][j])).size();
      } else
      {
        opponent_score += (find_available_directions(*(*board)[i][j])).size();
      }
    }
  }
  return (player_score - opponent_score);
}*/
// this evaluation function only cares about the moves the opponent can make,
// max score is 0 (win).
int Board::evaluate(Square::Player evaluate_for_player)
{
  int player_score = 0;
  Square::Player opponent = toggle_player(evaluate_for_player);
  for (int i = 0; i < SQUARE_DIMENSION; ++i)
  {
    for (int j = 0; j < SQUARE_DIMENSION; ++j)
    {
      if ((*board)[i][j]->get_occupant() == opponent)
      {
        player_score -= (find_available_directions(*(*board)[i][j])).size();
      }
    }
  }
  return player_score;
}

void Board::do_best_move()
{
  int best_score = INT_MIN;
  Board* best_board = 0;

  for (int x = 0; x < SQUARE_DIMENSION; ++x)
  {
    for (int y = 0; y < SQUARE_DIMENSION; ++y)
    {
      if ((*board)[x][y]->get_occupant() == current_player)
      {
        std::vector<Board::Direction> available_directions = find_available_directions(*(*board)[x][y]);

        for (int i = 0; i < available_directions.size(); ++i)
        {
          Board* new_board = travel(*(*board)[x][y], available_directions[i]);

          int new_board_min_score = new_board->min_max_possible_score(current_player, true, MIN_MAX_TREE_DEPTH, best_score);

          if (best_score < new_board_min_score) {
            best_score = new_board_min_score;

            delete best_board;
            best_board = new_board;
          } else
          {
            delete new_board;
          }
        }
      }
    }
  }

  if (best_board)
  {
    advance_board(best_board->board);

    delete best_board;
  } else
  {
    // No moves possible
    printf("Player %s has won\n", current_player == Square::BLACK ? "WHITE" : "BLACK");
    game_over = true;
  }
}

int Board::min_max_possible_score(Square::Player for_player, bool calculate_min, unsigned int depth, int alpha_beta)
{
  if (depth == 0)
  {
    return evaluate(for_player);
  }

  int current_score = calculate_min ? INT_MAX : INT_MIN;

  for (int x = 0; x < SQUARE_DIMENSION; ++x)
  {
    for (int y = 0; y < SQUARE_DIMENSION; ++y)
    {
      if ((*board)[x][y]->get_occupant() == current_player)
      {
        std::vector<Board::Direction> available_directions = find_available_directions(*(*board)[x][y]);

        for (int i = 0; i < available_directions.size(); ++i)
        {
          Board* new_board = travel(*(*board)[x][y], available_directions[i]);
          int new_board_score = new_board->min_max_possible_score(for_player, !calculate_min, depth - 1, current_score);

          delete new_board;

          if (calculate_min && new_board_score < current_score)
          {
            current_score = new_board_score;
          } else if (!calculate_min && new_board_score > current_score)
          {
            current_score = new_board_score;
          }
        }
      }

      // Alpha beta pruning
      if (calculate_min && current_score <= alpha_beta)
      {
        // If we are calculating min, then parent is calculating max.
        // If parent score is greater than current score, then we dont need
        // to keep going because this score won't even be used anyways because
        // any future resulting calculation will only result in a current_score
        // value is that equal to the current_score or less.
        return current_score;
      } else if (!calculate_min && current_score >= alpha_beta)
      {
        // If we are calculating max, then parent is calculating min.
        // If parent score is less than current score, then we don't need to
        // keep going because this score won't even be used anyways because
        // any future resulting calculation will only result in a current_score
        // value that is equal to the current_score or greater.
        return current_score;
      }
    }
  }

  return current_score;
}

Square::Player Board::get_current_player()
{
  return current_player;
}

void Board::do_random_move()
{
  Board* new_board = 0;

  for (int x = 0; x < SQUARE_DIMENSION; ++x)
  {
    for (int y = 0; y < SQUARE_DIMENSION; ++y)
    {
      if ((*board)[x][y]->get_occupant() == current_player)
      {
        std::vector<Board::Direction> available_directions = find_available_directions(*(*board)[x][y]);
        int count_directions = available_directions.size();

        if (count_directions == 0)
        {
          continue;
        }

        int direction_idx = rand() % count_directions;

        new_board = travel(*(*board)[x][y], available_directions[direction_idx]);
        break;
      }
    }

    if (new_board)
    {
      break;
    }
  }

  if (new_board)
  {
    advance_board(new_board->board);
    delete new_board;
  } else
  {
    // No moves possible
    printf("Player %s has won\n", current_player == Square::BLACK ? "WHITE" : "BLACK");
    game_over = true;
  }
}

void Board::advance_board(CongaBoard* new_conga_board)
{
  for (int x = 0; x < SQUARE_DIMENSION; ++x)
  {
    for (int y = 0; y < SQUARE_DIMENSION; ++y)
    {
      (*board)[x][y]->set_occupant((*new_conga_board)[x][y]->get_occupant());
      (*board)[x][y]->set_num_stones((*new_conga_board)[x][y]->get_num_stones());
    }
  }

  current_player = toggle_player(current_player);
}
