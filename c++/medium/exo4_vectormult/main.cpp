#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {
    
    // Array initialization
    int size = 100'000'000;
    int* vector1 = new int[size];
    int* vector2 = new int[size];

    for (int i = 0; i < size; i++){
        vector1[i] = rand() % 1000;
        vector2[i] = rand() % 10;
    }

    // Start chrono
    auto start = high_resolution_clock::now();

    // vector-vector
    int result = 0;
    for (int i = 0; i < size; i++){
        result += vector1[i]*vector2[i];
    }
    
    // End chrono
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    // Print the time
    cout << "The dot product vector-vector has taken: " << duration.count() << " ms\n";

    delete[] vector1, vector2;

    return 0;
}
