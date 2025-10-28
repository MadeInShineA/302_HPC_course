#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
using namespace chrono;

int main() {
  cout << "Enter your number" << endl;

  int n;

  cin >> n;

  if (cin.fail()) {
    cout << "Invalid input!" << endl;
    return 1;
  }

  int MAX_ITERATIONS = 100'000;

  string file_name = "output.txt";

  ofstream outfile(file_name);

  auto start = high_resolution_clock::now();

  for (int i = 1; i <= MAX_ITERATIONS; i++) {
    outfile << (i * n) << "\n";
  }

  outfile.close();

  auto end = high_resolution_clock::now();

  auto duration = duration_cast<milliseconds>(end - start);
  cout << "Results written to " << file_name << " in " << duration.count()
       << " milliseconds" << endl;
  return 0;
}
