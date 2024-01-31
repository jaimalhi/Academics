// Contains method implementations of the Stack class
#include "Stack.h"
#include <iostream>
using std::cout;
using std::endl;

// Linked List Implementation
// Constructors and destructor
Stack::Stack()
{
	top = nullptr;
}

// Constructor that sets capacity of stack to its parameter
// TO DO Consider preventing inserting into a notionally full stack
Stack::Stack(int n)
{
	top = nullptr;
}

// Copy constructor - makes a DEEP copy, not a SHALLOW copy
// TO DO Should do something with bad_alloc exception
Stack::Stack(const Stack & st)
{
	copyStack(st);
}

// Oveloaded assignment operator - makes a DEEP copy, not a SHALLOW copy
// TO DO Should do something with bad_alloc exception
Stack& Stack::operator=(const Stack& st)
{
	if (this != &st) { //this is a pointer to calling object
		deleteStack();
		copyStack(st);
	}
	return *this; // so you can do: st1 = st2 = st3
}

// Destructor
Stack::~Stack()
{
	deleteStack();
}

// Mutators
// PRE: Stack is not full
// PARAM: value - value to be inserted
// POST: value is inserted at the top of the stack
// TO DO Should do something with bad_alloc exception
void Stack::push(int value)
{
	// Note that this handles general case and empty case
	StackNode* newNode = new StackNode(value, top);
	top = newNode;
}

// PRE: Stack is not empty
// POST: removes and returns value at the top of the stack
int Stack::pop()
{
	if (empty()) {
		throw out_of_range("stack is empty");
	}

	StackNode* old_top = top;
	int result = top->data;
	top = top->next;
	delete old_top;

	return result;
}

// Accessors
// PRE: Stack is not empty
// POST: returns value at the top of the stack
int Stack::peek() const
{
	if (empty()) {
		throw out_of_range("stack is empty");
	}
	return top->data;
}

// POST: returns true if stack is empty, false otherwise
bool Stack::empty() const
{
	return top == nullptr;
}

// POST: prints contents of stack from top to bottom
// NOTE: for illustration only
void Stack::print() const
{
	StackNode* p = top;
	while (p != nullptr) {
		cout << p->data << endl;
		p = p->next;
	}
}

// POST: Deallocates dynamic memory associated with linked list
void Stack::deleteStack()
{
	while (top != nullptr) {
		StackNode* temp = top;
		top = top->next;
		delete temp;
	}
}

void Stack::copyStack(const Stack& st)
{
	top = nullptr;
	StackNode* original = st.top;

	if (original != nullptr) {
		// Copy top of st
		top = new StackNode(original->data);
		original = original->next;
		StackNode* copy = top;

		// Copy rest of st
		while (original != nullptr) {
			StackNode* newNode = new StackNode(original->data);
			copy->next = newNode;
			copy = copy->next;
			original = original->next;
		}
	}
}

// Array Implementation
/*
// Constructor and destructor
// Default constructor, capacity = 10
// TO DO Should do something with bad_alloc exception
Stack::Stack()
{
	capacity = 10;
	top = -1;
	arr = new int[capacity];
}

// Constructor that sets capacity of stack to its parameter
// TO DO Should do something with bad_alloc exception
Stack::Stack(int n)
{
	capacity = n;
	top = -1;
	arr = new int[capacity];
}

// Destructor
Stack::~Stack()
{
	delete[] arr;
}

// Mutators
// PRE: Stack is not full
// PARAM: value - value to be inserted
// POST: value is inserted at the top of the stack
void Stack::push(int value)
{
	//top = top + 1;
	//arr[top] = value;
	if (top == capacity - 1) {
		throw out_of_range("stack is full");
	}
	arr[++top] = value;
}

// PRE: Stack is not empty
// POST: removes and returns value at the top of the stack
int Stack::pop()
{
	//top = top - 1;
	//return arr[top + 1];
	if (empty()) {
		throw out_of_range("stack is empty");
	}
	return arr[top--];
}

// Accessors
// PRE: Stack is not empty
// POST: returns value at the top of the stack
int Stack::peek()
{
	if (empty()) {
		throw out_of_range("stack is empty");
	}
	return arr[top];
}

// POST: returns true if stack is empty, false otherwise
bool Stack::empty()
{
	//if (top == -1) {
	//	return true;
	//}
	//else {
	//	return false;
	//}
	
	return top == -1;
}

// POST: prints contents of stack from top to bottom
// NOTE: for illustration only
void Stack::print()
{
	cout << "not implemented (yet)" << endl;
}
*/
