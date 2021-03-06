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
  int         get_cost();
  void        set_cost(int);
  void        set_parent(Point*);
  bool        get_visiting();
  void        set_visiting();
  int         get_est_cost();
  void        set_est_cost(int);

private:
  const int   x;
  const int   y;
  bool        is_blocked;
  bool        is_visited;
  Point*      parent;
  int         cost;
  bool        visiting;
  int         est_cost;
};

#endif //__POINT_HPP__
