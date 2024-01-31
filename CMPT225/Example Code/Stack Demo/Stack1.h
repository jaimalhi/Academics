// Interface for a stack to store integers
// Author: John Edgar
// Date: May 2022
#pragma once //include guard

#include <stdexcept>
using std::out_of_range;

class StackNode {
public:
	
	int data;
	StackNode* next;

	// Constructors: note the use of initialization lists
	StackNode() : data(0), next(nullptr) {}
	StackNode(int val) : data(val), next(nullptr) {}
	StackNode(int val, StackNode* nxt) : data(val), next(nxt) {}
};

class Stack {
public:
	// Constructor and destructor
	// Default constructor
	Stack();
	// Constructor that sets size of stack - capacity 10 stack
	Stack(int n);
	// Copy constructor - makes a DEEP copy, not a SHALLOW copy
	// Necessary to allow objects to be passed by value to functions
	Stack(const Stack & st);
	// Destructor
	// Deallocates dynamic memory associated with object
	~Stack(); //~ a tilde
	// Overloaded assignment operator - makes a DEEP copy, not a SHALLOW copy
	// Necessary to allow objects to be returned from functions
	Stack& operator=(const Stack& st);

	// Mutators
	// PRE: Stack is not full
	// PARAM: value - value to be inserted
	// POST: value is inserted at the top of the stack
	void push(int value);

	// PRE: Stack is not empty
	// POST: removes and returns value at the top of the stack
	int pop();

	// Accessors
	// PRE: Stack is not empty
	// POST: returns value at the top of the stack
	int peek() const;

	// POST: returns true if stack is empty, false otherwise
	bool empty() const;
	// POST: prints contents of stack from top to bottom
	// NOTE: for illustration only
	void print() const;

private: 
	// Linked List Implementation
	StackNode* top;
	void deleteStack();
	void copyStack(const Stack& st);
	
	// Array implementation
	/*
	int* arr;
	int top;
	int capacity;
	*/
};