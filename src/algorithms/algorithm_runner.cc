//
// Created by zak on 2/17/17.
//

#include "algorithm_runner.h"

#include <cstdlib>

#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "algorithms/slave.h"
#include "algorithms/partitioner.h"
#include "utils/point.h"


const int MASTER_ID = 0;

void printSolution(const Solution &solution) {
  std::cout << solution;
}

void printSummary(const time_t &start, const time_t &end, const Solution &solution) {
  std::cout << "Janusze Programowania kdmszk28" << std::endl;
  std::cout << "https://github.com/miazgatron/map-the-gap" << std::endl;
  std::cout << solution.getNumConnectedBPs() << std::endl;
  std::cout << std::setprecision(2) << difftime(end, start) << std::endl;
  std::cout << getenv("UC_NODES") << ' ' << getenv("UC_TOTAL_PROCESSORS") << std::endl;
}

void receivePartialSolution(int nodeId, Solution &solution) {
  receive(nodeId);
  int numPaths = getInt(nodeId);
  for (int pathIdx = 0; pathIdx < numPaths; ++pathIdx) {
    int numBPOnPath = getInt(nodeId);
    double x, y;
    x = getDouble(nodeId);
    y = getDouble(nodeId);
    Path path(BTS(x, y));
    for (int bpIdx = 0; bpIdx < numBPOnPath; ++bpIdx) {
      x = getDouble(nodeId);
      y = getDouble(nodeId);
      path.addBP(BP(x, y));
    }
    solution.addPath(path);
  }
}

void master(const std::string &btsPath, const std::string &bpPath) {
  time_t start, end;
  time(&start);

  partitionData(btsPath, bpPath);
  Solution solution;
  for (int nodeId = 0; nodeId < nodes(); ++nodeId) {
    if (nodeId != MASTER_ID) {
      receivePartialSolution(nodeId, solution);
    }
  }

  time(&end);
  printSolution(solution);
  printSummary(start, end, solution);
}

void run() {
  if (id() == MASTER_ID)
    master("data/preprocessed_bts.csv", "data/bp.csv");
  else
    slave();
}
