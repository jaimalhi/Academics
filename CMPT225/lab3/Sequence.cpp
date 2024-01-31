//Sequence.cpp
#include <iostream>
#include <cassert>
#include <stdexcept>
#include "Sequence.h"

using namespace std;



Sequence::Sequence(unsigned size) {
    this->size = size;
    arr = new int[size];
} // constructor



void Sequence::set(unsigned index, int x) {
    if (index < size) {
        arr[index] = x;
    }
} // set


// Desc: returns the int value at arr[index] (given index)
//  Pre: 0 <= index <= length of array-1
// Post: int value at arr[index] is returned
int Sequence::get(unsigned index) {
    if (index < size) {
        return arr[index];
    }
    throw out_of_range("get(i): index out of range");
    //assert(false);
    //return 0;
} // get



void Sequence::append(int x) {
    int * newArr = new int[size + 1];
    
    for (unsigned i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    newArr[size++] = x;

    if (arr) {
        delete [ ] arr;
    }
    arr = newArr;
} // append



void Sequence::trunc(unsigned newSize) {
    if (newSize < size) {
        size = newSize;
    }
} // trunc



unsigned Sequence::getSize() {
    return size;
} // getSize



void Sequence::print(ostream& os) {
    for (unsigned i = 0; i < size; i++) {
        os << arr[i] << ' ';
    }
    os << endl;
} // print

