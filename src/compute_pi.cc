#include "compute_pi.h"
#include <cstdlib>
#include <iostream>
#include "message.h"

typedef long long LL;

const int ATTEMPTS = 1e5;
const int MASTER_ID = 0;
const int DEFAULT_TAG = 0;


static LL sq(int x) {
  return static_cast<LL>(x)*x;
}

static void master() {
  std::cout << "nodes: " << nodes() << '\n';
  LL total = 0;
  for (int node = 0; node < nodes(); ++node) if (node != MASTER_ID) {
    receive(node);
    total += getInt(node);
  }
  std::cout << static_cast<double>(4 * total) / (nodes() * ATTEMPTS) << '\n';
}

static void slave() {
  int res = 0;
  for (int i = 0; i < ATTEMPTS; ++i) {
    if (sq(rand()-RAND_MAX/2) + sq(rand()-RAND_MAX/2) <= sq(RAND_MAX/2))
      ++res;
  }
  putInt(MASTER_ID, res);
  send(MASTER_ID);
}

void computePi() {
  if (id() == MASTER_ID)
    master();
  else
    slave();
}
