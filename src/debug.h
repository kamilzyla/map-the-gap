#ifndef DEBUG_H_
#define DEBUG_H_

#include <cstdio>

#define DEBUG 1
#define DEB(args...) do { if (DEBUG) fprintf(stderr, args); } while (0)

#endif  // DEBUG_H_
