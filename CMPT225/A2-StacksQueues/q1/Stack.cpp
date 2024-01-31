#include "Stack.h"
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

//Default Constructor
Stack::Stack(){
    //STACKCAP = 8
    //arr[STACKCAP]
    size = 0;
}

//Push: insert element x to the top of the stack.
void Stack::push(int x){
    size++; //increment # of elements in arr
    if(size-1 >= STACKCAP){
        throw std::logic_error("Cannot push, Size >= to STACKCAP\n");
    }
    int temp[STACKCAP];
    for(int i = 0;i < size;i++){
        temp[i] = arr[i]; 
    } //copy all elements of arr into temp
    arr[0] = x;
    for(int i = 0;i < size;i++){
        arr[i+1] = temp[i];
    } //copy all elements back into arr, index+1
}

//Pop: remove and return element at the top of the stack.
int Stack::pop(){
    if(size <= 0){
        throw std::logic_error("Cannot pop, stack has no elements\n");
    }
    size--; //decrement # of elements in arr
    int top = arr[0];
    int temp[STACKCAP];
    for(int i = 0;i < size;i++){
        temp[i] = arr[i+1]; 
    } //copy all elements of arr (execept top) into temp
    for(int i = 0;i < size;i++){
        arr[i] = temp[i];
    } //copy all elements back into arr, without top

    return top;
}

//Peek: return the topmost element of the stack
int Stack::peek() const {
    if(size <= 0) throw std::logic_error("Stack has no elements to view");
    return arr[0];
}

//isEmpty: returns true if stack is empty, false otherwise
bool Stack::isEmpty() const {
    if(size == 0) return true;
    return false;
}