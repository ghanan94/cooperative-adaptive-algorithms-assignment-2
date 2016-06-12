// Prototype of class Square
//@file square.hpp

class Square
{
public:
  typedef enum Player
  {
    BLACK = 0,
    WHITE = 1,
    NONE  = 2
  } Player;

  Square(int, int);
  ~Square();

  const int get_x();
  const int get_y();
  Player    get_occupant();
  void      set_occupant(Player);
  int       get_num_stones();
  void      set_num_stones(int);

private:
  const int   x;
  const int   y;

  Player      occupant;
  int         num_stones;
};
