#include "Stack.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::out_of_range;
using std::bad_alloc;
using std::vector;

// Postfix Calculator
string getNext(string input, int& pos);
int postFixCalculator(string exp);
void postFixTest(string exp);
void postFixExample();

// Stack operation tests
void simpleTest();
void pushpopTest();
void copyTest();
void assignmentTest();
void printStack();
void exceptionTest();

void doubleArray(int arr[], int n);
void printArray(int arr[], int n);

void doubleVector(vector<int> v);
void printVector(vector<int> v);

int main()
{
	/*
	int arr[] = { 1,2,3,4 };
	int n = 4;
	printArray(arr, n);
	cout << "double contents of array in function" << endl;
	doubleArray(arr, n);
	printArray(arr, n);
	cout << endl;

	vector<int> vec = { 1,2,3,4 };
	printVector(vec);
	cout << "double contents of vector in function" << endl;
	doubleVector(vec);
	printVector(vec);
	*/

	//simpleTest();
	//pushpopTest();
	//copyTest();
	assignmentTest();
	//exceptionTest();
	//printStack();

	//postFixExample();
	cout << "end main" << endl;
	return 0;
}

void doubleArray(int arr[], int n)
{
	for (int i = 0; i < n; i++) {
		arr[i] *= 2;
	}
}
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++) {
		cout << arr[i] << endl;
	}
}

void doubleVector(vector<int> v)
{
	for (int i = 0; i < v.size(); i++) {
		v[i] *= 2;
	}
}

void printVector(vector<int> v)
{
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
}

// Test of class and method names
void simpleTest()
{
	try {
		Stack st;
		st.push(1);
		st.push(2);
		cout << st.pop() << endl;
		cout << st.pop() << endl;
		cout << "Bad pop!" << endl;
		cout << st.pop() << endl; // bad pop
	}
	catch (out_of_range& oor) {
		cout << "caught oor exception" << endl;
		cout << oor.what() << endl;
	}
	catch (bad_alloc& ba) {
		cout << ba.what() << endl;
	}
}

// Stack Operation Tests
// Quick test of push and pop
void pushpopTest()
{
	cout << endl << "PUSH, POP TEST" << endl << endl;
	// Insert values in stack
	int n = 4;
	Stack st(n);
	for (int i = 0; i < n; i++) {
		st.push(i + 1);
	}

	// Remove and print values in stack
	while (!st.empty()) {
		cout << st.pop() << endl;
	}

	cout << endl << "test complete (4 3 2 1)" << endl;
}

// Quick test of the copy constructor
void copyTest()
{
	// The copy constructor allows us to pass-by-value foo(st1)
	cout << endl << "COPY TEST" << endl << endl;
	int n = 4;
	Stack st1(n);
	for (int i = 0; i < n; i++) {
		st1.push(i + 1);
	}
	// st1 = {4,3,2,1}

	// Create st2 - a copy of st1
	
	Stack st2(st1);
	cout << "push 1, 2, 3 and 4 onto st1" << endl;
	cout << "Stack st2(st1)" << endl;
	cout << "ST1 (4-3-2-1)" << endl;
	cout << "-------------" << endl;
	st1.print();
	cout << "ST2 (4-3-2-1)" << endl;
	cout << "-------------" << endl;
	st2.print();
	
	///*
	// Change st2
	st2.pop();
	st2.pop();
	st2.pop();
	st2.push(21);
	st2.push(22);
	// st2 = {22,21,1}

	// Demonstrate that st2 and st1 are different
	cout << "pop 3 times from st2 then push 21 and 22" << endl << endl;
	cout << "ST1 (4-3-2-1)" << endl;
	cout << "-------------" << endl;
	st1.print();
	cout << endl;
	cout << "ST2 (22-21-1)" << endl;
	cout << "-------------" << endl;
	st2.print();
	//*/

	cout << endl << "END COPY CONSTRUCTOR TEST" << endl;
}

// Quick test of the overloaded assignment operator
void assignmentTest()
{
	// The overloaded assignment operator allows us to return objects
	// and assign them to existing objects: st1 = bar()
	cout << endl << "ASSIGNMENT TEST" << endl << endl;
	int n = 4;
	Stack st1(n);
	for (int i = 0; i < n; i++) {
		st1.push(i + 1);
	}

	// Create st2
	n = 8;
	Stack st2(n);
	for (int i = 0; i < n; i++) {
		st2.push(i + 1);
	}

	st2 = st1;
	// Change st2
	st2.pop();
	st2.pop();
	st2.pop();
	st2.push(21);
	st2.push(22);

	// Demonstrate that st2 and st1 are different
	cout << "ST1" << endl << "---" << endl;
	st1.print();
	cout << endl;
	cout << "ST2" << endl << "---" << endl;
	st2.print();

	// Self-assignment
	st2 = st2;
	cout << endl << "ST2" << endl << "---" << endl;
	st2.print();

	cout << "END ASSIGNMENT OPERATOR TEST" << endl;
}

void printStack()
{
	cout << endl << "PRINT TEST" << endl << endl;
	int n = 4;
	Stack st1(n);
	for (int i = 0; i < n; i++) {
		st1.push(i + 1);
	}

	cout << "ST1" << endl << "---" << endl;
	st1.print();
	cout << endl;
}

void exceptionTest()
{
	try {
		// Throws an out_of_range error
		Stack st;

		int test = st.pop();
	}
	catch (out_of_range oor) {
		cout << oor.what() << endl;
	}
	catch (...) {
		cout << "unknown error" << endl;
	}
}

//----------------------
// Postfix Calclator
// Parses a RPN string, returning the next operand or operator from
// the given position
// PRE: input is in the correct format
// PARAM: input - the RPN string
//        pos - the position to start parsing from
// Format: the string should contain a series of integer operands and 
//         the +, - * and / operators separated by spaces
string getNext(string input, int& pos) {
	string result = "";
	int nextSpace = 0;
	// Ignore current space (given by pos)
	if (pos > 0) {
		pos++;
	}
	if (pos < (int)input.size()) {
		// Find next space
		nextSpace = (int)input.find(" ", pos + 1);
		// DEBUG
		// cout << "nextSpace = " << nextSpace << endl;
		// END DEBUG
		result = input.substr(pos, nextSpace - pos);
		pos = nextSpace;
	}
	return result;
}

// Calculates and returns the result of a RPN expression
// PRE: input is in the correct format
// PARAM: expression - the RPN string
int postFixCalculator(string expression) {
	// Initialize variables
	int pos = 0; // For parsing exp
	string next = ""; // Next operand or operator
	Stack st((int)expression.size());
	int leftOp = 0;
	int rightOp = 0;

	// Process each operator or operand
	while (pos != -1) {
		next = getNext(expression, pos);
		// DEBUG
		// cout << "next op: " << next << endl;
		// END DEBUG

		// Push operand onto stack
		if (next != "+" && next != "-" && next != "/" && next != "*") {
			st.push(atoi(next.c_str()));
		}
		// Or process each operator
		else {
			rightOp = st.pop();
			leftOp = st.pop();
			// DEBUG
			cout << leftOp << " " << next << " " << rightOp << endl;
			// END DEBUG
			if (next == "+") { // +
				st.push(leftOp + rightOp);
			}
			else if (next == "-") { // -
				st.push(leftOp - rightOp);
			}
			else if (next == "*") { // *
				st.push(leftOp * rightOp);
			}
			else if (next == "/") { // /
				st.push(leftOp / rightOp);
			}
		}
	}

	// Return result
	return st.pop();
}

// Test function for the postFixCalculator function
void postFixTest(string exp)
{
	int result = postFixCalculator(exp);
	cout << exp << " = " << result;
}

// Calls postFixTest three times
void postFixExample()
{
	cout << "POSTFIX TEST" << endl << endl;
	postFixTest("5 1 2 + 4 * + 3 -");
	cout << endl << "should = 14" << endl << endl;
	postFixTest("9 7 + 5 3 - /");
	cout << endl << endl;
	postFixTest("3 5 2 * 17 7 - + * 11 3 * -");
	cout << endl << "END POSTFIX TEST" << endl << endl;
}


