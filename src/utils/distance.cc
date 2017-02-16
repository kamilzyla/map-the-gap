//
// Created by zak on 2/16/17.
//
#include <cmath>
#include "distance.h"

// see http://stackoverflow.com/a/1416950

const double d2r = (M_PI / 180.0);

double computeDistance(Point p1, Point p2) {
  double dlong = (p2.getX() - p1.getX()) * d2r;
  double dlat = (p2.getY() - p1.getY()) * d2r;
  double a = pow(sin(dlat / 2.0), 2) + cos(p1.getY() * d2r) * cos(p2.getY() * d2r) * pow(sin(dlong / 2.0), 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  double d = 6367 * c;

  return d;
}