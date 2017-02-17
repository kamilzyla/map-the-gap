//
// Created by zak on 2/16/17.
//

#include "solution.h"

std::ostream& operator<<(std::ostream& os, const Path& path) {
  os << path.bps_.size() << " " << 1 << " " << path.bps_.size() << std::endl;
  for (int i = 0; i < (int) path.bps_.size(); ++i) {
    os << path.bps_[i] << std::endl;
  }
  os << path.bts_ << std::endl;

  if (!path.bps_.empty()) {
    os << path.bts_ << " " << path.bps_[0] << std::endl;
  }
  for (int i = 1; i < (int) path.bps_.size(); ++i) {
    os << path.bps_[i - 1] << " " << path.bps_[i] << std::endl;
  }

  return os;
}
