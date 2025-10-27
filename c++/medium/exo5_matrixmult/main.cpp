#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

int* computeMatrixMatrix(const int* A, const int* B, const int rows, const int columns){

    // = Result of the Matrix.Matrix
    int* result = new int[rows * rows];

    // Matrix-Matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            for (int k = 0; k < columns; ++k) {
                result[i * rows + j] += A[i * columns + k] * B[k * rows + j];
            }
        }
    }

    return result;
}

int main() {

    // Start chrono
    auto start = high_resolution_clock::now();

    // Matrix and vector initialization
    int rows = 1000;
    int columns = 1000;

    // = Matrix1
    int* matrix1 = new int[rows * columns]; //rows x columns
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix1[i * columns + j] = rand() % 1000;
        }
    }

    // = Matrix2
    int* matrix2 = new int[columns * rows]; //columns x rows
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            matrix2[i * rows + j] = rand() % 10;
        }
    }

    // = Result of the Matrix.Matrix
    int* result = computeMatrixMatrix(matrix1, matrix2, rows, columns);

    // Clean up
    delete[] matrix1, matrix2, result;

    // End chrono
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    // Print the time
    cout << "The matrix-matrix multiplication has taken: " << duration.count() << " ms\n";

    return 0;
}
