#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <mpi.h>
#include "algorithm.h"
#include "compute_pi.h"
#include "message.h"
#include "solution.h"

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

void runSolution() {
  time_t start, end;
  time(&start);
  Solution solution = run("data/LTE1800 - stan na 2017-01-25.csv", "data/bp_konkurs_2_20160912.csv");
  time(&end);
  printSolution(solution);
  printSummary(start, end, solution);
}

int main(int argc, char *argv[]) {
  init(&argc, &argv);
  if (argc <= 1)
    runSolution();
  else if (argc == 2) {
    if (strcmp(argv[1], "pi") == 0)
      computePi();
    else
      std::cerr << "Unrecognized option: " << argv[1] << '\n';
  } else if (argc > 2) {
    std::cerr << "Expected 0 or 1 argument.\n";
  }
  return finalize();
}
