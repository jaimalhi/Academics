//Queue.cpp
#include "Queue.h"
#include <stdexcept>
#include <iostream>
using namespace std;


// Desc:  Constructor
Queue::Queue() : size(0), capacity(INITIAL_SIZE), frontindex(0), backindex(0) {
    arr = new int[INITIAL_SIZE];
} // constructor


// Desc:  Destructor
Queue::~Queue() {
    delete[] arr;
} // destructor


// Desc:  Copy Constructor
Queue::Queue(const Queue &other) {
    if (this != &other) {
        size = other.size;
        capacity = other.capacity;
        frontindex = other.frontindex;
        backindex = other.backindex;

        arr = new int[capacity];
        for(unsigned i = 0; i < capacity; i++){
            arr[i] = other.arr[i];
        }
    }
} // copy constructor


// Desc:  Assignment operator
Queue & Queue::operator=(const Queue &rhs) { 
    if (this != &rhs) {
        size = rhs.size;
        capacity = rhs.capacity;
        frontindex = rhs.frontindex;
        backindex = rhs.backindex;

        delete[] arr;
        arr = new int[capacity];
        for(unsigned i = 0; i < capacity; i++){
            arr[i] = rhs.arr[i];
        }
    }
    return *this;
} // lhs = rhs


// Desc:  Inserts element x at the back (O(1))
void Queue::enqueue(int x) { 
    if(size >= capacity){ //resizing array
        int* temp = new int[capacity*2];
        for(unsigned i = 0;i < capacity;i++){
                temp[i] = peek(); //use peek to maintain order of queue
                size--; //decrement size
                frontindex = (frontindex + 1) % capacity; //increment frontindex
            }
        temp[capacity] = x;

        //Set values
        frontindex = 0;
        size = capacity+1;
        backindex = capacity+1;
        capacity *= 2;

        delete[] arr;
        arr = temp;
    }
    else{
        size++; //increment size
        arr[backindex] = x;
        backindex = (backindex + 1) % capacity; //increment backindex
    }
} // enqueue


// Desc:  Removes the frontmost element (O(1))
//  Pre:  Queue not empty
void Queue::dequeue() {
    //Throw error if arr is empty
    if(size < 1) throw std::logic_error("Queue is empty\n");

    if((size < (capacity/4)) && (capacity >= INITIAL_SIZE)){ //resizing array
        int* temp = new int[capacity/2];
        unsigned ogSize = size; //original size
        for(unsigned i = 0;i < ogSize;i++){
            temp[i] = peek(); //use peek to maintain order of queue
            size--; //decrement size
            frontindex = (frontindex + 1) % capacity; //increment frontindex
        }
        //Set values
        frontindex = 0;
        size = ogSize;
        backindex = ogSize;
        capacity /= 2; 

        delete[] arr;
        arr = temp;
    }
    size--; //decrement size
    frontindex = (frontindex + 1) % capacity; //increment frontindex
} // dequeue


// Desc:  Returns a copy of the frontmost element (O(1))
//  Pre:  Queue not empty
int Queue::peek() const {
    //Throw error if arr is empty
    if(size < 1) throw std::logic_error("Queue is empty\n");
    return arr[frontindex];
} // top


// Desc:  Returns true if and only if queue empty (O(1))
bool Queue::isEmpty() const {
    return size == 0;
} // isempty