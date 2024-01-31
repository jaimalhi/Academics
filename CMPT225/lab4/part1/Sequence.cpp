//Sequence.cpp
#include <iostream>
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



int Sequence::get(unsigned index) {
    if (index < size) {
        return arr[index];
    }
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


