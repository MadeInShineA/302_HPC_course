
#include <cstdlib> // for rand()
#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int ARRAY_SIZE = 1'000'000;

  long long number_array[ARRAY_SIZE];

  // To avoid giving the same seed to all process
  srand(rank + 1);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    number_array[i] = rand() % 1'000'000'000;
  }

  long long max = number_array[0];

  for (int i = 1; i < ARRAY_SIZE; i++) {
    long long current_number = number_array[i];

    if (current_number > max) {
      max = current_number;
    }
  }

  long long maximums[world_size];
  MPI_Gather(&max, 1, MPI_LONG_LONG, &maximums, 1, MPI_LONG_LONG, 0,
             MPI_COMM_WORLD);

  if (rank == 0) {
    cout << "Array of maximum numbers: \n";
    for (int i = 0; i < world_size; i++) {
      cout << maximums[i] << "\n";
    }
    cout << endl;
  }

  MPI_Finalize();
  return 0;
}
