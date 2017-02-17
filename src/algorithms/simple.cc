//
// Created by zak on 2/16/17.
//

#include <string>
#include <queue>

#include "../parser/bts_parser.h"
#include "../parser/bp_parser.h"
#include "../utils/distance.h"
#include "solution.h"

const double MAX_DISTANCE = 1000000;

struct pair_cmp {
  typedef std::pair<double, BP> Val;
  bool operator()(const Val &l, const Val &r) const {
    return l.first < r.first;
  }
};

Solution run(const std::string &btsPath, const std::string &bpPath) {
  BTSes btses = parseBTSFile(btsPath);
  BPs bps = parseBPFile(bpPath);

  BTS randomBTS = *btses.begin();
  std::priority_queue<std::pair<double, BP>, std::vector<std::pair<double, BP> >, pair_cmp> q;
  for (BPs::iterator it = bps.begin(); it != bps.end(); ++it) {
    q.push(std::make_pair(computeDistance(*it, randomBTS), *it));
  }

  double totalDistance = 0;
  int numConnectedBPs = 0;
  Solution solution;
  while (!q.empty()) {
    std::pair<double, BP> distanceToPoint = q.top();
    q.pop();
    double distance = distanceToPoint.first;
    if (distance + totalDistance <= MAX_DISTANCE) {
      Path path(randomBTS);
      path.addBP(distanceToPoint.second);
      solution.addPath(path);

      totalDistance += distance;
      numConnectedBPs++;
    } else {
      break;
    }
  }

  return solution;
}
