#include <iostream>
#include <mpi.h>
#include <iomanip>
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
  std::cout << "<number_of_nodes> <number_of_cores>";
}

int main(int argc, char *argv[]) {
  messageInit(&argc, &argv);
  std::cerr << "Running..." << std::endl;
  time_t start, end;
  time(&start);
  Solution solution = run("data/LTE1800 - stan na 2017-01-25.csv", "data/bp_konkurs_2_20160912.csv");
  time(&end);
  printSolution(solution);
  printSummary(start, end, solution);
  messageFinalize();
  return 0;
}
