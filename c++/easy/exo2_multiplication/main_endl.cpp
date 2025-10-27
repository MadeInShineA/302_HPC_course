#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;
using namespace std::chrono;
int main() {

    // Number to loop on
    int number;

    // Aks the user a number;
    cout << "Please can you enter a number: ";
    cin >> number;

    // Start chrono
    auto start = high_resolution_clock::now();

    // Open the file test.txt
    ofstream myfile("multiplication_endl.txt");

    // Print the multiplication table
    myfile << "Multiplication table of " << number << ":\n";
    for (int i = 1; i <= 100000; ++i) {
        myfile << i << " - " << number * i << endl;
    }

    // Close the file
    myfile.close();

    // End chrono
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(end - start);

    // Print the time
    cout << "Time: " << duration.count() << " s\n";

    return 0;
}