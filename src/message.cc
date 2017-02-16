#include "message.h"
#include <mpi.h>

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

void putChar(int target, char value) {

}

void putInt(int target, int value) {

}

void putDouble(int target, double value) {

}

void send(int target) {

}

int receive(int source) {
  return 0;
}

char getChar(int source) {
  return 0;
}

int getInt(int source) {
  return 0;
}

double getDouble(int source) {
  return 0;
}
