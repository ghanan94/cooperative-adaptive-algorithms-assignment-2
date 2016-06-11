// Header file for class Point
//@file Point.hpp
#ifndef __POINT_HPP__
#define __POINT_HPP__
class Point
{
public:
  Point(int, int, bool);
  ~Point();

  const int   get_x();
  const int   get_y();
  bool        get_is_blocked();
  bool        get_is_visited();
  Point*      get_parent();
  void        reset();
  void        set_visited();

private:
  const int   x;
  const int   y;
  bool        is_blocked;
  bool        is_visited;
  Point*      parent;
};

#endif //__POINT_HPP__
