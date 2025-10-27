#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main(){

    // Start chrono
    auto start = high_resolution_clock::now();

    // Print Hello World
    cout << "Hello World \n";

    // End chrono
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // Print the time
    cout << "Time: " << duration.count() << " μs\n";

    return 0;
}