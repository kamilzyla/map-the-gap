#include <iostream>
#include <mpi.h>
#include "parser/bts_parser.h"
#include "parser/bp_parser.h"

int main(int argc, char *argv[]) {
  MPI::Init(argc, argv);
  std::cerr << "Running...\n";
  runBTSParser();
  runBPParser();
  return 0;
}
