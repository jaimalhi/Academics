
#include <iostream>
#include "Sequence.h"

using namespace std;



Sequence::Sequence() : head(NULL), tail(NULL) {
} // Sequence



void Sequence::append(int x) {
    node * newNode = new node(x, NULL);

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
} // append



void Sequence::print(ostream& os) {
    /*
    node * curr = head;

    while (curr != NULL) {
        os << curr->data << ' ';
        curr = curr->next;
    }
    os << endl;
    */

    for (node * curr = head; curr != NULL; curr = curr->next) {
        os << curr->data << ' ';
    }
    os << endl;


    /* 
    for (int i = 0; i < size; i++) {
        os << arr[i] << ' ';
    }
    os << endl;
    */
} // print



void Sequence::set(unsigned index, int x) {
    node * curr = head;
    //unsigned count = 0;

    // while (curr != NULL && count != index) {
    while (curr != NULL && index--) {
        curr = curr->next;
        //count++;
    }

    if (curr != NULL) {
        curr->data = x;
    }
} // set



void Sequence::insert(unsigned index, int x) {
    node * prev = NULL;
    node * curr = head;

    while (curr != NULL && index--) {
        prev = curr;
        curr = curr->next;
        // prev = prev->next;
    }

    node * newNode = new node(x, curr);
    prev->next = newNode;
} // insert



/*
int Sequence::get(unsigned index) {
} // get
*/



/*
void Sequence::trunc(unsigned newSize) {
} // trunc
*/



/*
unsigned Sequence::getSize() {
} // getSize
*/




