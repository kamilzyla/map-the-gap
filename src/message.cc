#include "message.h"
#include <vector>
#include <mpi.h>

enum {
  SIZE_TAG, DATA_TAG
};

// Currently not used so the implementation get be really simplified...
class SendBuf {
 public:
  void putChar(char value) {
    put<char>(value, MPI_CHAR);
  }

  void putInt(int value) {
    put<int>(value, MPI_INT);
  }

  void putDouble(double value) {
    put<double>(value, MPI_DOUBLE);
  }

  void send(int target) {
    if (!buf_.empty()) {
      MPI_Send(&buf_.front(), 1, MPI_PACKED, target, DATA_TAG, MPI_COMM_WORLD);
      buf_.clear();
    }
  }

 private:
  std::vector<char> buf_;

  template<class T>
  void put(T value, MPI_Datatype datatype) {
    int pos = buf_.size(), add;
    MPI_Pack_size(1, datatype, MPI_COMM_WORLD, &add);
    buf_.resize(pos + add);
    MPI_Pack(&value, 1, datatype, &buf_[pos], buf_.size(), &pos, MPI_COMM_WORLD);
    buf_.resize(pos);
  }
};


void messageInit(int *argc, char ***argv) {
  MPI_Init(argc, argv);
}

void messageFinalize() {
  MPI_Finalize();
}

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
  MPI_Send(&value, 1, MPI_CHAR, target, DATA_TAG, MPI_COMM_WORLD);
}

void putInt(int target, int value) {
  MPI_Send(&value, 1, MPI_INT, target, DATA_TAG, MPI_COMM_WORLD);
}

void putDouble(int target, double value) {
  MPI_Send(&value, 1, MPI_DOUBLE, target, DATA_TAG, MPI_COMM_WORLD);
}

void send(int target) {
  // Currently a NOP.
}

int receive(int source) {
  // Currently a NOP.
  return source;
}

char getChar(int source) {
  char x;
  MPI_Status status;
  MPI_Recv(&x, 1, MPI_CHAR, source, DATA_TAG, MPI_COMM_WORLD, &status);
  return x;
}

int getInt(int source) {
  int x;
  MPI_Status status;
  MPI_Recv(&x, 1, MPI_INT, source, DATA_TAG, MPI_COMM_WORLD, &status);
  return x;
}

double getDouble(int source) {
  double x;
  MPI_Status status;
  MPI_Recv(&x, 1, MPI_DOUBLE, source, DATA_TAG, MPI_COMM_WORLD, &status);
  return x;
}
