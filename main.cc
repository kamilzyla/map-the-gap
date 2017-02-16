#include <mpi.h>
#include <cstdio>

int main(int argc, char *argv[]) {
  MPI::Init(argc, argv);
  puts("Yolo");
  return 0;
}
