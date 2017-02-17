#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <mpi.h>
#include <iomanip>
#include "algorithms/algorithm_runner.h"
#include "algorithms/solution.h"
#include "compute_pi.h"
#include "message.h"
#include "utils/runner.h"

int main(int argc, char *argv[]) {
  init(&argc, &argv);
  Runner runner("PROG", run);
  runner.registerFunc("sol", run);
  runner.registerFunc("pi", computePi);
  runner.run();
  return finalize();
}
