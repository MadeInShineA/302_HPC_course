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

    if (rank == 0){
        cout << "Number of processors: " << world_size << "\n";
    }

    for (int i = 0; i < world_size; i++){
        
        cout << "Processor " << rank << " - Hello World\n";
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Finalisation de MPI
    MPI_Finalize();

    return 0;

}