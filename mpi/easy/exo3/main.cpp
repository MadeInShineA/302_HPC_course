#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    cout << "Number of processors: " << world_size << "\n";
  }

  if (rank != 0) {
    int signal;
    MPI_Recv(&signal, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
  }

  cout << "Hello World!" << rank << endl;

  if (rank != world_size - 1) {
    int signal = 1;
    MPI_Send(&signal, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
