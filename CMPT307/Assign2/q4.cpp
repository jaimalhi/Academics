//*  g++ -o x q4.cpp

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

//* ============================ HELPER FUNCTIONS ============================ *//
vector<int> generateRandomArray(int n) {
    vector<int> A(n);
    for (int &element : A) {
        element = rand() % (n * 10); // Random numbers from 0 to 10*n
    }
    return A;
}

// Function to copy a vector (to use the same array for different sorts)
vector<int> copyArray(const vector<int>& A) {
    return vector<int>(A.begin(), A.end());
}

//* ============================ FUNCTIONS USED BY BOTH VARIANTS ============================ *//
// Utility function to swap elements
void exchange(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function used in quicksort
int Partition(vector<int>& A, int l, int r) {
    int pivot = A[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; j++) {
        if (A[j] <= pivot) {
            i++;
            exchange(A[i], A[j]);
        }
    }
    exchange(A[i + 1], A[r]);
    return i + 1;
}

// Randomized partition function
int RandomizedPartition(vector<int>& A, int l, int r) {
    int i = l + rand() % (r - l + 1); // Randomly select i between l and r
    exchange(A[i], A[r]); // Exchange A[i] with A[r]
    return Partition(A, l, r);
}

//* ============================ RANDOMIZED QUICKSORT VARIANT ============================ *//
void RandomizedQuicksort(vector<int>& A, int l, int r) {
    if (l < r) {
        int q = RandomizedPartition(A, l, r); // Randomized partitioning
        RandomizedQuicksort(A, l, q - 1); // Recursively sort the left part
        RandomizedQuicksort(A, q + 1, r); // Recursively sort the right part
    }
}

//* ============================ QUICKSORT/INSERTION SORT VARIANT ============================ *//
void ModifiedQuicksort(std::vector<int>& A, int l, int r, int k) {
    if (r - l + 1 >= k) {
        int q = RandomizedPartition(A, l, r); // Randomized partitioning
        ModifiedQuicksort(A, l, q - 1, k); // Recursively sort the left part
        ModifiedQuicksort(A, q + 1, r, k); // Recursively sort the right part
    }
}

// Insertion sort function
void InsertionSort(vector<int>& A) {
    int n = A.size();
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;

        // Move elements of A[0..i-1], that are greater than key, to one position ahead of their current position
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
}

// Main function to run RandomizedQuicksort
int main() {
    srand(time(0)); // Seed for random number generation
    
    vector<int> ks = {1, 5, 10, 15, 20}; // Different values of k to try
    vector<int> sizes = {1, 2, 4, 8, 16, 32}; // 2^i * 1000 (ex. 2^0=1, 2^1=2, ... 2^5=32)
    
    for (int size : sizes) {
        cout << "===================================================\n";
        size *= 1000;
        vector<int> originalArray = generateRandomArray(size);

        // Measure time for Randomized-Quicksort
        vector<int> arrayForRandomizedQuicksort = copyArray(originalArray);
        auto start = std::chrono::high_resolution_clock::now();
        RandomizedQuicksort(arrayForRandomizedQuicksort, 0, size - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        cout << "Randomized-Quicksort for n=" << size << ": " << elapsed.count() << " seconds.\n";
        
        // Measure time for the variant of Randomized-Quicksort with insertion sort
        for (int k : ks) {
            vector<int> arrayForVariant = copyArray(originalArray);
            start = std::chrono::high_resolution_clock::now();
            ModifiedQuicksort(arrayForVariant, 0, size - 1, k);
            InsertionSort(arrayForVariant);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            cout << "Variant Randomized-Quicksort with k=" << k << " for n=" << size << ": " << elapsed.count() << " seconds.\n";
        }
    }
    
    return 0;
}