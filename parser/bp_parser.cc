#include "bp_parser.h"

#include <fstream>
#include <cstdlib>
#include <iostream>

#include "common.h"
#include "wgs84_do_puwg92.h"

class BP {
 public:
  BP(const Tokens &tokens) {
    int x_puwg92 = atoi(tokens[11].c_str() + 1); // First character is: '"'
    int y_puwg92 = atoi(tokens[12].c_str() + 1);
    puwg92_do_wgs84(x_puwg92, y_puwg92, &y_, &x_);
  }

  double getX() const { return x_; }
  double getY() const { return y_; }

 private:
  double x_;
  double y_;
};

typedef std::vector<BP> BPs;

BPs parseBPFile(const std::string &path) {
  std::ifstream file(path.c_str());
  std::string line;

  BPs bpSet;
  dropHeader(file);
  while (std::getline(file, line)) {
    Tokens tokens = getTokens(line, ';');
    bpSet.push_back(BP(tokens));
  }
  return bpSet;
}

int runBPParser() {
  std::string const btsPath = "../bp_truncated.csv";
  BPs bpSet = parseBPFile(btsPath);
  std::cout << "Number of BTSes: " << bpSet.size() << std::endl;

  BPs::iterator it = bpSet.begin();
  for (int i = 0; i < 10; ++i) {
    std::cout << "BTS(" << it->getX() << ", " << it->getY() << ")" << std::endl;
    it++;
  }
}
