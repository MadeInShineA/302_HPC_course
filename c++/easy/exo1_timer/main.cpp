// Necessary header files for input output functions
#include <chrono>
#include <iostream>
using namespace std;
using namespace chrono;

// main() function: where the execution of
// C++ program begins
int main() {

  auto start = high_resolution_clock::now();

  // This statement prints "Hello World"
  cout << "Hello World" << endl;

  auto end = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(end - start);

  cout << "Execution time: " << duration.count() << " microseconds" << endl;

  return 0;
}
