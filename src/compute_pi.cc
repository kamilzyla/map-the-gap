#include "compute_pi.h"
#include <cstdlib>
#include <iostream>
#include <mpi.h>

typedef long long LL;

const int ATTEMPTS = 1e5;
const int MASTER_ID = 0;
const int DEFAULT_TAG = 0;

int nodes() {
  int x;
  MPI_Comm_size(MPI_COMM_WORLD, &x);
  return x;
}

int id() {
  int x;
  MPI_Comm_rank(MPI_COMM_WORLD, &x);
  return x;
}

static LL sq(int x) {
  return static_cast<LL>(x)*x;
}

static void master() {
  std::cout << "nodes: " << nodes() << '\n';
  LL total = 0;
  for (int node = 0; node < nodes(); ++node) if (node != MASTER_ID) {
    int res;
    MPI_Status status;
    MPI_Recv(&res, 1, MPI_INT, node, DEFAULT_TAG, MPI_COMM_WORLD, &status);
    total += res;
  }
  std::cout << static_cast<double>(4 * total) / (nodes() * ATTEMPTS) << '\n';
}

static void slave() {
  int res = 0;
  for (int i = 0; i < ATTEMPTS; ++i) {
    if (sq(rand()-RAND_MAX/2) + sq(rand()-RAND_MAX/2) <= sq(RAND_MAX/2))
      ++res;
  }
  MPI_Send(&res, 1, MPI_INT, MASTER_ID, DEFAULT_TAG, MPI_COMM_WORLD);
}

void compute_pi() {
  if (id() == MASTER_ID)
    master();
  else
    slave();
}
