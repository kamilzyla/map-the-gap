#include <mpi.h>
#include <cstdio>

int main(int argc, char *argv[]) {
  MPI::Init(argc, argv);
  auto f = []() { puts("Yolo"); };
  f ();
  return 0;
}
