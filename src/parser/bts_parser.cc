#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <fstream>
#include <cstdlib>
#include <cassert>

#include "common.h"
#include "../point/Point.h"

double toDecimalDegrees(std::string const &degreesMinutesSecondsString) {
  assert(degreesMinutesSecondsString.size() == 12); // Should be "DDEMM'SS"""
  double degrees = atoi(degreesMinutesSecondsString.c_str() + 1);
  double minutes = atoi(degreesMinutesSecondsString.c_str() + 4);
  double seconds = atoi(degreesMinutesSecondsString.c_str() + 7);
  return degrees + minutes / 60 + seconds / 3600;
}

BTS createBTS(const Tokens &tokens) {
  double x = toDecimalDegrees(tokens[4]);
  double y = toDecimalDegrees(tokens[5]);
  return BTS(x, y);
}

BTSes parseBTSFile(const std::string &path) {
  std::ifstream file(path.c_str());
  std::string line;

  BTSes btsSet;
  dropHeader(file);
  while (std::getline(file, line)) {
    Tokens tokens = getTokens(line, ',');
    btsSet.push_back(createBTS(tokens));
  }
  return btsSet;
}
