//Lab11 - search.cpp
#include <iostream>
using namespace std;

// Function Prototypes
int iterativeSearch(int arr[], int size, int target);
int recursiveSearch(int arr[], int next, int target);
void printSmallArray(int arr[], int n);

int main()
{
    int size = 11;
	int arr[] = { 1,3,5,7,9,11,13,15,17,19,21};
	int target = 0;

	cout << "arr = ";
	printSmallArray(arr, size);
	cout << endl << endl;

	cout << "ITERATIVE SEARCH TESTS" << endl;
	cout << "search for " << target << ": " << iterativeSearch(arr, size, target) << endl;
	target = 1;
	cout << "search for " << target << ": " << iterativeSearch(arr, size, target) << endl;
	target = 21;
	cout << "search for " << target << ": " << iterativeSearch(arr, size, target) << endl;
	target = 12;
	cout << "search for " << target << ": " << iterativeSearch(arr, size, target) << endl;
	target = 13;
	cout << "search for " << target << ": " << iterativeSearch(arr, size, target) << endl;

	cout << endl <<  "RECURSIVE SEARCH TESTS" << endl;
	target = 0;
	cout << "search for " << target << ": " << recursiveSearch(arr, size-1, target) << endl;
	target = 1;
	cout << "search for " << target << ": " << iterativeSearch(arr, size-1, target) << endl;
	target = 21;
	cout << "search for " << target << ": " << recursiveSearch(arr, size-1, target) << endl;
	target = 12;
	cout << "search for " << target << ": " << recursiveSearch(arr, size-1, target) << endl;
	target = 13;
	cout << "search for " << target << ": " << recursiveSearch(arr, size-1, target) << endl;

        return 0;
}

// Function to print an array on one line like this:
//    {2,5,3,9,7}
//    Warning - only useful for small arrays!
// PARAM: arr - array to be printed, n - size of arr
// POST: contents of arr are printed to standard output
void printSmallArray(int arr[], int n)
{
	cout << "{";
	for (int i = 0; i < n; ++i) {
		cout << arr[i];
		if (i != n - 1) {
			cout << ",";
		}
	}
	cout << "}";
}

int iterativeSearch(int arr[], int size, int target)
{
    for(int i = 0;i < size;i++){
        if(arr[i] == target){
            return i;
        }
    }
    return -1;
}

//PARAM: next = next index of array to look at, starting at last legal index
int recursiveSearch(int arr[], int next, int target)
{
    if(arr[next] == target){
        return next;
    }
    else if(arr[next] == 0){
        return -1;
    }
    else{
        return recursiveSearch(arr, next-1, target);
    }
}
