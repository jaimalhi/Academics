//*  g++ -o q1a q1a.cpp
//* ====================================================
// C++ program to compare Merge sort and Insertion sort assuming running times of:
// Merge sort:  64nlogn
// Insertion sort: 8n^2
// Assuming 10^6 (1,000,000) instructions per second
#include <bits/stdc++.h>
using namespace std;

// Driver code
int main(){
    const int INSTRUCTIONS_PER_SECOND = 1000000;
	const int n = 43;

    cout << "===================================================\n";

    // Merge sort calculation
    double mergeSort = ((64*n)*log2(n)) / INSTRUCTIONS_PER_SECOND;
    cout << "Merge Sort ran in " << mergeSort << " seconds with an n=" << n << endl;

    // Insertion sort calculation
    double insertionSort = (8*pow(n, 2)) / INSTRUCTIONS_PER_SECOND;
    cout << "Insertion Sort ran in " << insertionSort << " seconds with an n=" << n << endl;

    cout << "===================================================\n";

    // showing which is slower
    if(mergeSort == insertionSort){
        cout << "Both ran in the same time" << endl;
    } else if (mergeSort > insertionSort) {
        cout << "Insertion sort was faster by " << mergeSort-insertionSort << endl;
    } else {
        cout << "Merge sort was faster by " << insertionSort-mergeSort << endl;
    }

    cout << "===================================================\n";

	return 0;
}
