#include <iostream>
#include <mpi.h>
#include "algorithm.h"
#include "compute_pi.h"

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  compute_pi();
  // int numConnectedPoints = run("data/LTE1800 - stan na 2017-01-25.csv", "data/bp_konkurs_2_20160912.csv");
  // std::cout << "Number connected points: " << numConnectedPoints << std::endl;
  MPI_Finalize();
  return 0;
}
