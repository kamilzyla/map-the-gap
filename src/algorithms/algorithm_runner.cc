//
// Created by zak on 2/17/17.
//

#include "algorithm_runner.h"

#include <cstdlib>

#include <iomanip>
#include <iostream>
#include <map>

#include "algorithms/slave.h"
#include "message.h"
#include "parser/bts_parser.h"


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

void partitionData(const std::string &btsPath, const std::string &bpPath) {
  BTSesWithGminas btsesWithGminas = parseBTSFile(btsPath);
  std::map<int, BTSes> btsesInGminas;
  for (size_t i = 0; i < btsesWithGminas.size(); ++i) {
    btsesInGminas[btsesWithGminas[i].second].push_back(btsesWithGminas[i].first);
  }
}

std::vector<Solution> gatherPartialSolutions() {
  // TODO
  return std::vector<Solution>();
}

Solution joinSolutions(const std::vector<Solution> partial_solutions) {
  // TODO
  return Solution();
}

void master(const std::string &btsPath, const std::string &bpPath) {
  time_t start, end;
  time(&start);

  partitionData(btsPath, bpPath);
  std::vector<Solution> partialSolutions = gatherPartialSolutions();
  Solution solution = joinSolutions(partialSolutions);

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
