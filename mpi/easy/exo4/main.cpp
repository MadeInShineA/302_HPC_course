#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {

  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int NUMBERS_PER_ARRAY = 100;
  int num_arrays[world_size][NUMBERS_PER_ARRAY];

  if (rank == 0) {
    for (int i = 0; i < world_size; i++) {
      for (int j = 0; j < NUMBERS_PER_ARRAY; j++) {
        num_arrays[i][j] = rand() % 100;
      }
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);

  int num_array[NUMBERS_PER_ARRAY];
  MPI_Scatter(num_arrays, NUMBERS_PER_ARRAY, MPI_INT, num_array,
              NUMBERS_PER_ARRAY, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank != 0) {
    cout << "Process - " << rank << " " << num_array << endl;
  }

  MPI_Finalize();
}
