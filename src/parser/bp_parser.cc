#include "bp_parser.h"

#include <fstream>
#include <cstdlib>
#include <iostream>

#include "common.h"
#include "wgs84_do_puwg92.h"
#include "../point/Point.h"

BP createBP(const Tokens &tokens) {
  int x_puwg92 = atoi(tokens[11].c_str() + 1); // First character is: '"'
  int y_puwg92 = atoi(tokens[12].c_str() + 1);
  double x;
  double y;
  puwg92_do_wgs84(x_puwg92, y_puwg92, &y, &x);
  return BP(x, y);
}

BPs parseBPFile(const std::string &path) {
  std::ifstream file(path.c_str());
  std::string line;

  BPs bpSet;
  dropHeader(file);
  while (std::getline(file, line)) {
    Tokens tokens = getTokens(line, ';');
    bpSet.push_back(createBP(tokens));
  }
  return bpSet;
}

int runBPParser() {
  std::string const btsPath = "data/bp_truncated.csv";
  BPs bpSet = parseBPFile(btsPath);
  std::cout << "Number of BTSes: " << bpSet.size() << std::endl;

  BPs::iterator it = bpSet.begin();
  for (int i = 0; i < 10; ++i) {
    std::cout << "BTS(" << it->getX() << ", " << it->getY() << ")" << std::endl;
    it++;
  }
}
