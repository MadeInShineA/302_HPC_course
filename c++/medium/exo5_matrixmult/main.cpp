

#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {

  if (argc != 2) {
    cerr << "Error: incorrect usage." << endl;
    cerr << "Usage: " << argv[0] << " <vector_size>" << endl;
    exit(1);
  }

  long long matrix_size;

  try {
    matrix_size = stoll(argv[1]); // converts string to int
    if (matrix_size <= 0) {
      throw invalid_argument("Vector size must be positive.");
    }
  } catch (const invalid_argument &e) {
    cerr << "Error: invalid vector size. Must be a positive integer." << endl;
    exit(1);
  } catch (const out_of_range &e) {
    cerr << "Error: vector size too large." << endl;
    exit(1);
  }

  vector<vector<int>> matrix1(matrix_size, vector<int>(matrix_size));
  vector<vector<int>> matrix2(matrix_size, vector<int>(matrix_size));

  for (long long i = 0; i < matrix_size; i++)
    for (long long j = 0; j < matrix_size; j++) {
      matrix1[i][j] = rand() % 100;
      matrix2[i][j] = rand() % 100;
    }

  auto start = high_resolution_clock::now();

  long long scalar_product = 0;

  for (int i = 0; i < matrix_size; i++) {
    for (int j = 0; j < matrix_size; j++) {
      scalar_product += matrix1[i][j] * matrix2[i][j];
    }
  }

  auto end = high_resolution_clock::now();

  auto duration = duration_cast<milliseconds>(end - start);

  cout << "The resulting scalar product is: " << scalar_product << "\n"
       << "Calculated in " << duration.count() << " milliseconds" << endl;

  return 0;
}
