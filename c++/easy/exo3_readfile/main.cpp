#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;
int main(int argc, char *argv[]) {

    string filename;
    // Get the filename
    if (argc == 2){
        filename = argv[1];
    }
    else {
        // Print an error if the number of argument is wrong
        cerr << "There must be one argument while executing the program.\n";
        exit(1); 
    }

    // Start chrono
    auto start = high_resolution_clock::now();

    // Open the file test.txt
    ifstream myfile(filename);

    if (myfile.is_open()){

        // Read the 15 first lines
        for (int i = 0; i < 15; i++) {
            string line;
            getline(myfile,line);
            cout << "Line " << i+1 << " : " << line << "\n";
        }

    }
    else {
        // Print an error if the file does not exist
        cerr << "Error: file \"" << filename << "\" can't be opened.\n";
        exit(1); 
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