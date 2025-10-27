#include <iostream>
#include <chrono>

// MPI 
#include "mpi.h"

using namespace std;
using namespace std::chrono;
int main(int argc, char** argv){
    
    // MPI: initialization
    MPI_Init(&argc, &argv);

    // MPI: get the number of processors 
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // MPI: get the processor rank
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Array initialization
    int size = 67'200'000;
    int local_size = size/world_size;
    int* vector1 = new int[local_size];
    int* fullVector1;

    // Array Scatter
    if (rank==0){
        fullVector1 = new int[size];

        for (int i = 0; i < size; i++){
            fullVector1[i] = rand() % 1000;
        }
        MPI_Scatter(fullVector1, local_size, MPI_INT, vector1, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Scatter(fullVector1, local_size, MPI_INT, vector1, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Start chrono
    auto start = high_resolution_clock::now();

    // Local Vector Sum
    int local_sum = 0;
    for (int i = 0; i < local_size; i++){
        local_sum += vector1[i];
    }

    // Global Sum
    int global_sum;
    //MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Allreduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if (rank==0){
        cout << "The global sum is: " << global_sum << "\n";
    }

    // End chrono
    if (rank==0){
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        // Print the time$
        cout << "The vector sum has taken: " << duration.count() << " ms\n";
    }

    delete[] vector1;
    if (rank == 0) delete[] fullVector1;

    // Finalisation de MPI
    MPI_Finalize();

    return 0;

}