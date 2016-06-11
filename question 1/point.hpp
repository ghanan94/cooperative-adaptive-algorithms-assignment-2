// Header file for class Point
//@file Point.hpp

class Point
{
public:
  Point(int x, int y, Point& parent);
  ~Point();

  const int   get_x();
  const int   get_y();
  Point&      get_parent();

private:
  const int   x;
  const int   y;
  bool        is_empty;
  Point&      parent;
};
