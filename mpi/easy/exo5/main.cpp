#include <iostream>
#include <fstream>
#include <string>

// MPI
#include "mpi.h"

using namespace std;

int main(int argc, char** argv) {

    // MPI: initialization
    MPI_Init(&argc, &argv);

    // MPI: get the number of processors 
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // MPI: get the processor rank
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int max_line_length = 1024;
    char line[max_line_length];

    if (rank == 0) {
        ifstream file("data.txt");

        if (!file.is_open()) {
            cerr << "Erreur : impossible d'ouvrir le fichier.\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        file.getline(line, max_line_length);
        file.close();
    }

    // MPI: Send line to all rank
    MPI_Bcast(line, max_line_length, MPI_CHAR, 0, MPI_COMM_WORLD);

    cout << "Processus " << rank << " a reçu : " << line << endl;

    // Finalisation de MPI
    MPI_Finalize();

    return 0;
}