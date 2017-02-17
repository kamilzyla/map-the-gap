#include "slave.h"

#include "message.h"
#include "utils/point.h"
#include "utils/distance.h"

const int MASTER_ID = 0;

std::vector<Point> getVector() {
  int count = getInt(MASTER_ID);
  std::vector<Point> points;
  for (int i = 0; i < count; ++i) {
    points.push_back(Point(getDouble(MASTER_ID), getDouble(MASTER_ID)));
  }
  return points;
}

void putPoint(const Point &p) {
  putDouble(MASTER_ID, p.getX());
  putDouble(MASTER_ID, p.getY());
}

void slave() {
  receive(MASTER_ID);
  std::vector<Point> access_points = getVector();
  getDouble(MASTER_ID);  // Ignored - on Michal's request.
  std::vector<Point> houses = getVector();
  double budget = getDouble(MASTER_ID);

  if (access_points.empty()) {
    putInt(MASTER_ID, 0);
    send(MASTER_ID);
    return;
  }

  Point ap = access_points.back();
  size_t connected = 0;
  double cost = 0;

  while (connected < houses.size()) {
    double add = computeDistance(ap, houses[connected]);
    if (cost + add <= budget) {
      cost += add;
      ++connected;
    } else {
      break;
    }
  }

  putInt(MASTER_ID, connected);
  for (size_t i = 0; i < connected; ++i) {
    putInt(MASTER_ID, 1);
    putPoint(ap);
    putPoint(houses[i]);
  }
}
