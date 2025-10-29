#include <chrono>
#include <cstdlib> // for rand()
#include <iostream>
#include <mpi.h>

using namespace std;
using namespace chrono;

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const int NUMBERS_PER_ARRAY = 1'000'000;

  // Only rank 0 allocates the full array (dynamically to avoid stack overflow)
  int (*num_arrays)[NUMBERS_PER_ARRAY] = nullptr;
  if (rank == 0) {
    num_arrays = new int[world_size][NUMBERS_PER_ARRAY];
    for (int i = 0; i < world_size; i++) {
      for (int j = 0; j < NUMBERS_PER_ARRAY; j++) {
        num_arrays[i][j] = rand() % 100;
      }
    }
  }

  int num_array[NUMBERS_PER_ARRAY];
  int local_sum = 0;
  int global_sum = 0;

  auto start = high_resolution_clock::now();

  // Scatter data from rank 0 to all ranks
  MPI_Scatter((rank == 0) ? &(num_arrays[0][0]) : nullptr, NUMBERS_PER_ARRAY,
              MPI_INT, num_array, NUMBERS_PER_ARRAY, MPI_INT, 0,
              MPI_COMM_WORLD);

  // EVERY rank (including rank 0) computes its local sum
  for (int i = 0; i < NUMBERS_PER_ARRAY; i++) {
    local_sum += num_array[i];
  }

  // Reduce all local sums to rank 0
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  auto end = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(end - start);

  if (rank == 0) {
    cout << "Sum of the array: " << global_sum << "\n"
         << "Duration: " << duration.count() << " milliseconds" << endl;
    delete[] num_arrays; // Clean up
  }

  MPI_Finalize();
  return 0;
}
