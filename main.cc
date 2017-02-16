#include <iostream>
#include <mpi.h>
#include "parser/bts_parser.h"


int main(int argc, char *argv[]) {
  MPI::Init(argc, argv);
  std::cerr << "Running...\n";
  runParser();
  return 0;
}
