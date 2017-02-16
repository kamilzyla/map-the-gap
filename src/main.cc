#include <iostream>
#include <mpi.h>
#include "algorithm.h"
#include "solution.h"

int main(int argc, char *argv[]) {
  MPI::Init(argc, argv);
  std::cerr << "Running..." << std::endl;
  Solution solution = run("data/LTE1800 - stan na 2017-01-25.csv", "data/bp_konkurs_2_20160912.csv");
  std::cout << solution;
  MPI::Finalize();
  return 0;
}
