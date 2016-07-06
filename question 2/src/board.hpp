// Prototype file for Board class
// Used to create a Conga Board and solve using Minimax with Alpha-Beta Pruning
//@file board.hpp
#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "square.hpp" //Need Square::Player
#include <vector>

#define SQUARE_DIMENSION 4

class Board
{
public:
  typedef std::vector<std::vector<Square*>> CongaBoard;
  typedef std::vector<CongaBoard*> MoveArray;

  typedef enum Direction
  {
    NORTH = 0,
    SOUTH,
    WEST,
    EAST,
    NORTH_WEST,
    NORTH_EAST,
    SOUTH_WEST,
    SOUTH_EAST
  } Direction;

  Board();
  ~Board();

  void simulate_game();
  void print_board();
  void do_best_move();
  int min_max_possible_score(Square::Player, bool, unsigned int, int);
  Square::Player get_current_player();
  void do_random_move();

private:
  CongaBoard* board;
  Square::Player current_player;
  bool game_over;

  Board(CongaBoard*, Square::Player);

  Square::Player toggle_player(Square::Player);
  std::vector<Direction> find_available_directions(Square&);
  Board* travel(Square&, Direction);
  int evaluate(Square::Player);
  void min_max();
  void advance_board(CongaBoard*);
};

#endif //__BOARD_HPP__
