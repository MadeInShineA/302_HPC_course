#include <chrono>
#include <iostream>

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

// Function to print an array
void printArray(int* tab, int size) {
    cout << "[ ";
    for (int i = 0; i < size; i++){cout << tab[i] << " ";}
    cout << "]\n";
}

int main() {
    
    // Array initialization
    int size = 500000;
    int* tab = new int[size];

    for (int i = 0; i < size; i++){
        tab[i] = rand() % 1000;
    }
    

    // Print the initial array
    //cout << "The inital array is \n";
    //printArray(tab, size);

    // Start chrono
    auto start = high_resolution_clock::now();

    mergeSort(tab, 0, size-1); // First recursion, left = 0 and right = size-1

    // End chrono
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    // Print the time
    cout << "The sorted algorithm has taken: " << duration.count() << " ms\n";

    // Print the sorted array
    //cout << "The final array is \n";
    //printArray(tab, size);

    delete[] tab;

    return 0;
}
