#include <chrono>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <string>

using namespace std;
using namespace chrono;

string received_line;
int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  string first_line;
  int line_length = 0;

  if (rank == 0) {
    string file_path = "./data.txt";
    ifstream file(file_path);

    if (!file.is_open()) {
      cerr << "Error: could not open file at " << file_path << endl;
      exit(1);
    }

    getline(file, first_line);
    file.close();

    line_length = first_line.size();
  }

  // Broadcast the length from rank 0 to all
  MPI_Bcast(&line_length, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // Now all ranks resize their buffer
  first_line.resize(line_length);

  MPI_Bcast(&first_line[0], line_length, MPI_CHAR, 0, MPI_COMM_WORLD);
  cout << "Rank " << rank << ": " << first_line << endl;

  MPI_Finalize();
  return 0;
}
