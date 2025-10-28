
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

  long long vector_size;

  try {
    vector_size = stoll(argv[1]); // converts string to int
    if (vector_size <= 0) {
      throw invalid_argument("Vector size must be positive.");
    }
  } catch (const invalid_argument &e) {
    cerr << "Error: invalid vector size. Must be a positive integer." << endl;
    exit(1);
  } catch (const out_of_range &e) {
    cerr << "Error: vector size too large." << endl;
    exit(1);
  }

  vector<int> vec1(vector_size);
  vector<int> vec2(vector_size);

  for (long long i = 0; i < vector_size; i++) {
    vec1[i] = rand() % 100;
    vec2[i] = rand() % 100;
  }

  auto start = high_resolution_clock::now();

  long long scalar_product = 0;

  for (int i = 0; i < vector_size; i++) {
    scalar_product += vec1[i] * vec2[i];
  }

  auto end = high_resolution_clock::now();

  auto duration = duration_cast<milliseconds>(end - start);

  cout << "The resulting scalar product is: " << scalar_product << "\n"
       << "Calculated in " << duration.count() << " milliseconds" << endl;

  return 0;
}
