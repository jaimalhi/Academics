#include <iostream>
using namespace std;

// Global Variables for Array Sizes
const int ARR1SIZE = 4;
const int ARR2SIZE = 3;

// Function Prototypes
void getSequence(int arr[], int n, int start, int gap);
int minimumElement(int arr[], int n);
void printArray(int arr[], int n);

int main()
{
	// Tests of the getSequence function
	int arr1[ARR1SIZE];
	int arr2[ARR2SIZE];
	cout << "SEQUENCE TESTS" << endl;

	// TEST 1
	// should print the values 7, 9, 11, and 13
	cout << "TEST 1 { 7,9,11,13 } " << endl;
	getSequence(arr1, ARR1SIZE, 7, 2);
	cout << endl;
	printArray(arr1, ARR1SIZE);
	cout << endl;

	// TEST 2
	// should print the values 2, -1, and -4
	cout << "TEST 2 { 2,-1,-4 } " << endl;
	getSequence(arr2, ARR2SIZE, 2, -3);
	cout << endl;
	printArray(arr2, ARR2SIZE);
	cout << endl << endl;


	// Tests of the minimumElement function
	cout << "MINIMUM ELEMENT TESTS" << endl;

	// TEST 1
	int arr3[] = { 17, 3, 12, 11, 4 };
	// should print the value 3
	cout << "TEST 1 (3): " << minimumElement(arr3, 5) << endl;

	// TEST 1
	int arr4[] = { 1, 0, 7, 23, 2, -1 };
	// should print the value -1
	cout << "TEST 2 (-1): " << minimumElement(arr4, 6) << endl;

	cout << endl << endl;
	return 0;
}

// Prints the contents of arr from index 0 to n, one element per line
void printArray(int arr[], int n){
	for(int i = 0;i < n;i++){
        cout << arr[i] << endl;
	}
}

// Populates arr with a sequence of n integers
// The sequence starts with start and increases by gap
void getSequence(int arr[], int n, int start, int gap){

	for(int i = 0;i < n;i++){
        arr[i] = start + gap*i;
        cout << arr[i] << " ";
	}
}

// Returns the smallest element in arr[0:n]
int minimumElement(int arr[], int n){
	int smallest = arr[0];

	for(int i = 0;i < n;i++){
        if(arr[i] < smallest){
            smallest = arr[i];
        }
	}

	return smallest;
}

