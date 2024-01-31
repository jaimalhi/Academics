#include <iostream>
#include <string>
using namespace std;

// Question 1
//PARAM: arr is array to print the Cartesian product of, n is size of arr
void cartesianProduct(int arr[], int n, int& ops){
    int i = 0;
    ops = 1; //initializes cost for the first statement
    while (i < n) {
        int j = 0;
        ops += 2; //while comparison and above line
        while (j < n) {
            cout << "{" << arr[i] << "," << arr[j] << "}";
            j++;  
            cout << " ";
            ops += 4; //while comparison and above 3 lines
        }
        ops++; //terminating while comparison
        cout << endl;
        i++;
        ops += 2; //above 2 lines
    }
    ops++; //terminating while comparison
}
//Cost function: 4n^2 + 5n + 2
//Barometer ops: Inner while loop condition and all
//               operations within this loop
//O-Notation: O(n^2)

// Question 2
void triangle(int x, int& ops){
    int i = 0;
    ops = 1; //initializes cost for the first statement

    while (i < x) {
        int j = 0;
        ops += 2; //while comparison and above line
        while (j <= i) {
            cout << j << " ";
            j++;
            ops += 3; //while comparison and above 2 lines
        }
        ops++; //while terminated
        cout << endl;
        i++;
        ops += 2; //above 2 lines
    }
    ops++; //while terminated

    while (i > 0) {
        i--;
        int j = 0;
        ops += 3; //while comparison and above 2 lines
        while (j <= i) {
            cout << j << " ";
            j++;
            ops += 3; //while comparison and above 2 lines
        }
        ops++; //while terminated
        cout << endl;
        ops += 1; //above line
    }
    ops++; //while terminated
}
//Cost function: (6n^2)/2 + 13n + 3
//Barometer ops: both Inner while loop conditions and all
//               operations within these loops
//O-Notation: O(n^2)

// Question 3
//Returns the index of a 1d array representing a matrix
//given row (r) and column (c) values
int rcIndex(int r, int c, int columns, int& ops){
    ops++; //below operations
    return r * columns + c;
}

//PRE: m represents a square matrix of size rows * rows
//PARAM: rows represents the number of both rows and columns
//POST: Returns a pointer to an array (matrix) of the same size as m
//NOTE: values are indexed r0c0,r0c1,…,r0cn-1,r1c0,…
int* matrixSelfMultiply(int* m, int rows, int& ops){
    // Create result array
    int columns = rows;
    int* result = new int[rows * columns];
    int r = 0;
    ops = 3; //initializes cost for the first statement

    while (r < rows) {
        int c = 0;
        ops += 2; //while comparison and above line
        while (c < columns) { //columns = rows
            int next = 0;
            int iNext = 0;
            ops += 3; //while comparison and above 2 lines

            while (iNext < rows) {
                next += m[rcIndex(r, iNext, columns, ops)] * m[rcIndex(iNext, c, columns, ops)];
                iNext++;
                ops += 3; //while comparison and above 2 lines
            }
            ops++; //while termination

            result[rcIndex(r, c, columns, ops)] = next;
            c++;
            ops += 2; //above 2 lines
        }
        ops++; //while termination
        r++;
        ops += 1; //above line
    }
    ops++; //while termination
    return result;
}
//Cost function: 5n^3 + 7n^2 + 4n + 4
//Barometer ops: Inner while loop condition and all
//               operations within this loop
//O-Notation: O(n^3)

// Question 4 
//PARAM: arr is array to be sorted, n is size of array, i should initially = 0
void ssort(int arr[], int n, int i, int& ops){
    if (i < n-1) {
        // Find and swap smallest remaining
        int next = i + 1;
        int smallest = i;
        ops += 3; //if statement and above 2 lines

        while (next < n) {
            ops += 1; //while statement
            if (arr[next] < arr[smallest]) {
                smallest = next;
                ops += 1; //above line
            }
            ops += 1; //if statement
            next++;
            ops += 1; //above line
        }
        ops++; //while terminated

        // Swap i with smallest
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        ops += 3; //above 3 lines

        ssort(arr, n, i + 1, ops);
    }
    else{
        ops++; //if statement false
    }
}
//Cost function: 1.75n^2 + 5.5n - 6 //for even inputs
//               1.75n^2 + 5.5n - 6.25 //for odd inputs
//Barometer ops: Inner while loop condition and all
// operations within this loop
//O-Notation: O(n^2)

// Question 5
//PRE: n is a power of 2 greater than zero.
//PRE: Initial call should be to i = 0
//e.g. pattern(8, 0)
void pattern(int n, int i, int& ops){
    if (n > 0) {
        pattern(n/2, i, ops); //ops++;
        // Print i spaces
        cout << string(i, ' '); //1+3 ops
        ops += 5; //above line and if statement

        // A loop to print n asterisks, each one followed by a space
        int ast = 0;
        ops++; //above line
        while (ast < n) {
            cout << "* ";
            ast++;
            ops += 3; //while statement and above two lines
        }
        ops++; //while terminated

        cout << endl;
        i += n;
        ops += 2; //above 2 lines
        pattern(n / 2, i, ops); //ops++;
    }
    else{
        ops++; //if statement false
    }
}
//Cost function: 3nlogn + 23n - 9
//Barometer ops: Inner while loop condition and all
// operations within this loop
//O-Notation: O(nlogn)

// Question 6
//Desc: Linear search.  Reports position if found, else -1
//Post: Elements unchanged
int lsearch(int arr[], unsigned int len, int target, int& ops) {
    if (len == 0){
        ops++; //if statement true
        return -1; 
    }
    ops++; //if statement false
    if (arr[0] == target){
        ops++; //if statement true
        return 0;
    }
    ops++; //if statement false
    if (lsearch(arr+1, len-1, target, ops) == -1) {
        ops += 2; //if statement true & lsearch()
        return -1;
    } 
    else {
        ops += 2; //if statement false & lsearch() 
        return 1 + lsearch(arr+1, len-1, target, ops);
    }
} // lsearch
//Cost function: 3*(2^(n)) - 4
//Barometer ops: first two if statments, len==0 and arr[0]==target
//O-Notation: O(2^n)

// Question 7
unsigned pow(unsigned int base, unsigned int exp, int& ops) {
    unsigned int ret = 1; //ubtret?
    ops = 1; //above line
    while (exp > 0) {
        ops++; //while statement
        if (exp & 1) { //true if exp is odd
            ret *= base;
            ops++; //above line
        }
        ops++; //if statment

        exp >>= 1; //sets exp to itself shifted 1 bit to the right
        //ex. exp=5=0101, 'exp >>= 1' converts 0101 (5) to 0010 (2)
        base = base * base;
        ops += 2; //above 2 lines
    }
    ops++; //while terminated
    return ret;
} // pow
//Cost function: floor(6*ln(n) + 7) //ln = log base e
//Barometer ops: the while condition, the if statement, exp >>= 1
// base = base*base
//O-Notation: O(logn)