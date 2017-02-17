//
// Created by zak on 2/16/17.
//

#ifndef MAP_THE_GAP_SOLUTION_H
#define MAP_THE_GAP_SOLUTION_H

#include <ostream>
#include "../point/Point.h"
class Path {
 public:
  explicit Path(const BTS &bts): bts_(bts) {}

  void addBP(const BP &bp) {
    bps_.push_back(bp);
  }

  BPs getBPs() const {
    return bps_;
  }

  BTS getBTS() const {
    return bts_;
  }

  size_t getNumConnectedBPs() const {
    return bps_.size();
  }

  friend std::ostream& operator<<(std::ostream& os, const Path& path);

 private:
  BTS bts_;
  BPs bps_;
};

class Solution {
 public:
  void addPath(const Path &path) {
    paths_.push_back(path);
  }

  std::vector<Path> getPaths() const {
    return paths_;
  }

  size_t getNumConnectedBPs() const {
    size_t numConnectedBPs = 0;
    for (int i = 0; i < (int) paths_.size(); ++i) {
      numConnectedBPs += paths_[i].getNumConnectedBPs();
    }
    return numConnectedBPs;
  }

  friend std::ostream& operator<<(std::ostream& os, const Solution& solution) {
    os << solution.paths_.size() << std::endl;
    for (int i = 0; i < (int) solution.paths_.size(); ++i) {
      os << solution.paths_[i];
    }

    return os;
  }

 private:
  std::vector<Path> paths_;
};

#endif //MAP_THE_GAP_SOLUTION_H
