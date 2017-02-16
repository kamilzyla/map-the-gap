#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <fstream>
#include <cstdlib>
#include <cassert>

#include "common.h"

double toDecimalDegrees(std::string const &degreesMinutesSecondsString) {
  assert(degreesMinutesSecondsString.size() == 12); // Should be "DDEMM'SS"""
  double degrees = atoi(degreesMinutesSecondsString.c_str() + 1);
  double minutes = atoi(degreesMinutesSecondsString.c_str() + 4);
  double seconds = atoi(degreesMinutesSecondsString.c_str() + 7);
  return degrees + minutes / 60 + seconds / 3600;
}

class BTS {
 public:
  typedef double Coordinate;

  BTS(const Tokens &tokens) {
    x_ = toDecimalDegrees(tokens[4]);
    y_ = toDecimalDegrees(tokens[5]);
  }

  Coordinate getX() const {
    return x_;
  }

  Coordinate getY() const {
    return y_;
  }

 private:
  Coordinate x_;
  Coordinate y_;
};

typedef std::vector<BTS> BTSes;

BTSes parseBTSFile(const std::string &path) {
  std::ifstream file(path.c_str());
  std::string line;

  BTSes btsSet;
  dropHeader(file);
  while (std::getline(file, line)) {
    Tokens tokens = getTokens(line, ',');
    btsSet.push_back(BTS(tokens));
  }
  return btsSet;
}

int runBTSParser() {
  std::string const btsPath = "../bts_truncated.csv";
  BTSes btsSet = parseBTSFile(btsPath);
  std::cout << "Number of BTSes: " << btsSet.size() << std::endl;

  BTSes::iterator it = btsSet.begin();
  for (int i = 0; i < 10; ++i) {
    std::cout << "BTS(" << it->getX() << ", " << it->getY() << ")" << std::endl;
    it++;
  }
}
