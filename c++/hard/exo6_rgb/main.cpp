#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using namespace std::chrono;

// Open file and compute the R G B values
void computeMeanRGB(const string& filename, double& meanR, double& meanG, double& meanB) {

    // Open File
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    int r, g, b;
    int sumR = 0, sumG = 0, sumB = 0, count = 0;

    // Sum the various R G B over the file
    while (getline(file, line)) {
        stringstream ss(line);
        char comma;
        if (ss >> r >> comma >> g >> comma >> b) {
            sumR += r;
            sumG += g;
            sumB += b;
            count += 1;
        }
    }

    // Close File
    file.close();

    // Compute the mean values
    meanR = float(sumR) / count;
    meanG = float(sumG) / count;
    meanB = float(sumB) / count;

}

int main() {

    // Start chrono
    auto start = high_resolution_clock::now();

    // File to open
    string filenames[] = {"Pictures/Black_Hole_RGB.txt", "Pictures/Blue_Whirl_RGB.txt", "Pictures/Brinicle_RGB.txt", "Pictures/Bubble_Simulating_Earth_RGB.txt", "Pictures/Drop_Impact_1_RGB.txt", "Pictures/Drop_Impact_2_RGB.txt", "Pictures/Fire_Tornado_1_RGB.txt", "Pictures/Fire_Tornado_2_RGB.txt",
        "Pictures/Lighting_Balls_RGB.txt", "Pictures/Magnetosphere_RGB.txt", "Pictures/Mammatus_Clouds_RGB.txt", "Pictures/Plasma_Vortex_RGB.txt", "Pictures/Plateau_Rayleigh_Instability_RGB.txt", "Pictures/Plunging_Breaking_Wave_RGB.txt", "Pictures/Quasar_RGB.txt", "Pictures/Sonoluminescence_RGB.txt", "Pictures/Tornado_RGB.txt"};

    // Mean Values
    double meanR, meanG, meanB;

    for (int i = 0; i < size(filenames); i++){

        string file = filenames[i];

        // Compute the Mean Values
        computeMeanRGB(file, meanR, meanG, meanB);

        // Print the data
        cout << "File: " << file << "\nMean R: " << meanR << "\nMean G: "<< meanG << "\nMean B: " << meanB << "\n\n";

    }

    // End chrono
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    // Print the time
    cout << "The program has taken: " << duration.count() << " ms\n";

    return 0;
}
