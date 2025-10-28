// main.cpp
#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
    cout << "Number of processors: " << size << endl;
  }

  cout << "Processor " << rank << " - Hello World" << endl;

  MPI_Finalize();
  return 0;
}
