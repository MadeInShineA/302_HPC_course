#include <iostream>

// MPI 
#include "mpi.h"

using namespace std;
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
    int size = 1'000'000;
    int* vector1 = new int[size];

    for (int i = 0; i < size; i++){
        vector1[i] = rand() % 1000;
    }

    // Local Vector Sum
    int local_max = vector1[0];
    for (int i = 1; i < size; i++){
        if (vector1[i] > local_max){
            local_max = vector1[i];
        }
    }
    
    // Gather all maximums
    int* vector_maximum = new int[world_size];
    MPI_Gather(&local_max, 1, MPI_INT, vector_maximum, world_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank==0){
        for (int i = 0; i < world_size; i++){
            cout << "Rank: " << i << ", maximum is: "<< vector_maximum[i]<< "\n";
        }
    }

    delete[] vector1, vector_maximum;

    // Finalisation de MPI
    MPI_Finalize();

    return 0;

}