#include <chrono>
#include <iostream>
#include "mpi.h"

using namespace std;
using namespace std::chrono;

// Function to merge two arrays
void merge(int* tab, int leftIndex, int midIndex, int rightIndex) {

    // Get the arrays size
    int sizeLeft = midIndex - leftIndex + 1;
    int sizeRight = rightIndex - midIndex;

    // Create temporary arrays to not modify the main array
    int leftTab[sizeLeft];
    for (int i = 0; i < sizeLeft; i++) {leftTab[i] = tab[leftIndex + i];}

    int rightTab[sizeRight];
    for (int j = 0; j < sizeRight; j++) {rightTab[j] = tab[midIndex + 1 + j];}


    int indexLeft = 0; // Left array index
    int indexRight = 0; // Right array index
    int indexTab = leftIndex; // Starting index of the tab
    while (indexLeft < sizeLeft && indexRight < sizeRight) { // Do while both array are not empty
        if (leftTab[indexLeft] <= rightTab[indexRight]) {
            tab[indexTab] = leftTab[indexLeft];
            indexLeft++;
        } 
        else {
            tab[indexTab] = rightTab[indexRight];
            indexRight++;
        }
        indexTab++;
    }

    if (indexRight == sizeRight){ // Loop of the leftTab if the rightTab is empty
        while (indexLeft < sizeLeft) { 
            tab[indexTab] = leftTab[indexLeft];
            indexLeft++;
            indexTab++;
        }
    }
    else {// Loop of the rightTab if the leftTab is empty
        while (indexRight < sizeRight) { 
            tab[indexTab] = rightTab[indexRight];
            indexRight++;
            indexTab++;
        }
    }

}

// Function to split the array into two different arrays and sort them
void mergeSort(int* tab, int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) { // And not leftIndex = rightIndex -> one element

        // Compute the middle index for splitting
        int midIndex = leftIndex + (rightIndex - leftIndex) / 2;

        // Sort first and second arrays
        mergeSort(tab, leftIndex, midIndex);
        mergeSort(tab, midIndex + 1, rightIndex);

        // Finally merge both sorted arrays into one
        merge(tab, leftIndex, midIndex, rightIndex);
    }
}

int main(int argc, char** argv) {

    // MPI: initialization
    MPI_Init(&argc, &argv);

    // MPI: get the number of processors 
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // MPI: get the processor rank
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Array initialization
    int size = 1'000'000;
    int local_size = size / world_size;

    int* tab = new int[local_size];
    int* global_tab;

    if (rank == 0) {
        global_tab = new int[size];
        for (int i = 0; i < size; i++) {
            global_tab[i] = rand() % 1000;
        }
    }

    auto start = high_resolution_clock::now();

    MPI_Scatter(global_tab, local_size, MPI_INT, tab, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    mergeSort(tab, 0, local_size - 1);

    MPI_Gather(tab, local_size, MPI_INT, global_tab, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        mergeSort(global_tab, 0, size - 1);

        // End chrono
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        // Print the time
        cout << "The sorted algorithm has taken: " << duration.count() << " ms\n";

        delete[] global_tab;
    }

    delete[] tab;

    // Finalisation de MPI
    MPI_Finalize();

    return 0;
}
