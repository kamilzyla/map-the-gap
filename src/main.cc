#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <mpi.h>
#include <iomanip>
#include "compute_pi.h"
#include "algorithms/solution.h"
#include "message.h"
#include "runner.h"
#include "algorithms/algorithm_runner.h"

int main(int argc, char *argv[]) {
  init(&argc, &argv);
  Runner runner("PROG", run);
  runner.registerFunc("sol", run);
  runner.registerFunc("pi", computePi);
  runner.run();
  return finalize();
}
