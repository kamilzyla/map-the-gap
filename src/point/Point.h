//
// Created by zak on 2/16/17.
//

#ifndef MAP_THE_GAP_POINT_H
#define MAP_THE_GAP_POINT_H

#include <vector>
#include <ostream>

class Point {
 public:
  virtual ~Point() {}
  Point(double x, double y): x_(x), y_(y) {}

  double getX() const { return x_; }
  double getY() const { return y_; }

  friend std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << point.x_ << " " << point.y_;
    return os;
  }

 protected:
  double x_;
  double y_;
};

class BTS: public Point {
 public:
  BTS(double x, double y): Point(x, y) {}
};

typedef std::vector<BTS> BTSes;

class BP: public Point {
 public:
  BP(double x, double y): Point(x, y) {}
};

typedef std::vector<BP> BPs;

#endif //MAP_THE_GAP_POINT_H
