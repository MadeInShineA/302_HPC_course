#include <chrono>
#include <iostream>

// MPI 
#include "mpi.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
    
    // MPI: initialization
    MPI_Init(&argc, &argv);

    // MPI: get the number of processors 
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // MPI: get the processor rank
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Array initialization
    int global_size = 100'000'000;
    int local_size = global_size / world_size;

    // Vectors
    int* global_vector1;
    int* global_vector2;
    int* local_vector1 = new int[local_size];
    int* local_vector2 = new int[local_size];

    if (rank==0){
        global_vector1 = new int[global_size];
        global_vector2 = new int[global_size];

        for (int i = 0; i < global_size; i++){
            global_vector1[i] = rand() % 1000;
            global_vector2[i] = rand() % 10;
        }

    }

    MPI_Scatter(global_vector1, local_size, MPI_INT, local_vector1, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(global_vector2, local_size, MPI_INT, local_vector2, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Start chrono
    auto start = high_resolution_clock::now();

    // vector-vector
    int result = 0;
    for (int i = 0; i < local_size; i++){
        result += local_vector1[i]*local_vector2[i];
    }
    
    int global_result;
    MPI_Reduce(&result, &global_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // End chrono
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    // Print the time
    if (rank==0){
        cout << "The dot product vector-vector has taken: " << duration.count() << " ms\n";
    }

    if (rank==0){delete[] global_vector1, global_vector2;}
    delete[] local_vector1, local_vector2;

    // Finalisation de MPI
    MPI_Finalize();

    return 0;
}
