#include <iostream>
#include <string>
#include "Queue.h"

using std::cout;
using std::endl;
using std::logic_error;
using std::string;
using std::to_string;

void testConstructor();
void testCopyConstructor(); // Regular test
void testCopyConstructor2(); // Delete one
void testAssignmentOperator(); // Regular test
void testAssignmentOperator2(); // Delete one
void testAssignmentOperator3();
void testEnqueue();
void testEnqueue2();
void testEnqueue3();
void testEnqueue4();
void testDequeue();
void testDequeue2();
void testDequeue3();

// 	g++ -g -ggdb3 -Wall -std=c++11 -o test test_queue.cpp
int main() {
    testConstructor();
    testCopyConstructor();
    testCopyConstructor2();
    testAssignmentOperator();
    testAssignmentOperator2();
    testAssignmentOperator3();
    testEnqueue();
    testEnqueue2();
    testEnqueue3();
    testEnqueue4();
    testDequeue();
    testDequeue2();
    testDequeue3();
}

void testConstructor() {
    cout << "Testing default constructor" << endl;
    cout << "================================================================================" << endl;
    Queue q;
    bool empty = q.isEmpty();
    cout << "Empty: " << empty << endl;
    try {
        int peek = q.peek();
        cout << "Peek " << peek << " from empty queue" << endl;
    } catch(const logic_error &) {
        cout << "Cannot peek, queue empty" << endl;
    }
    try {
        q.dequeue();
    } catch (const logic_error &) {
        cout << "Cannot dequeue, queue empty" << endl;
    }
    q.enqueue(1);
    int peek = q.peek();
    cout << "Inserted " << peek << " into empty queue" << endl;
    cout << "================================================================================" << endl;

}

void testCopyConstructor() {
    cout << "Testing copy constructor" << endl;
    cout << "================================================================================" << endl;    
    Queue q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    Queue q2(q1);
    string s1 = "", s2 = "";
    while (!q1.isEmpty() && !q2.isEmpty()) {
        int peek1 = q1.peek();
        int peek2 = q2.peek();
        s1 += to_string(peek1) + " ";
        s2 += to_string(peek2) + " ";
        q1.dequeue();
        q2.dequeue();
    }
    if (s1.compare(s2) == 0) {
        cout << s1 << endl;
        cout << s2 << endl;
        cout << "Queue values are the same" << endl;
    }
    cout << "================================================================================" << endl;

}

void testCopyConstructor2() {
    cout << "Testing copy constructor 2" << endl;
    cout << "================================================================================" << endl;    
    Queue q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    Queue q2(q1);
    while (!q1.isEmpty()) {
        int peek = q1.peek();
        cout << "Removing " << peek << " from q1" << endl;
        q1.dequeue();
    }
    if (q1.isEmpty() && !q2.isEmpty()) {
        cout << "q1 is empty and q2 is not empty" << endl;
    }
    cout << "================================================================================" << endl;

}

void testAssignmentOperator() {
    cout << "Testing assignment operator" << endl;
    cout << "================================================================================" << endl;    
    Queue q1, q2;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q2 = q1;
    string s1 = "", s2 = "";
    while (!q1.isEmpty() && !q2.isEmpty()) {
        int peek1 = q1.peek();
        int peek2 = q2.peek();
        s1 += to_string(peek1) + " ";
        s2 += to_string(peek2) + " ";
        q1.dequeue();
        q2.dequeue();
    }
    if (s1.compare(s2) == 0) {
        cout << s1 << endl;
        cout << s2 << endl;
        cout << "Queue values are the same" << endl;
    }
    cout << "================================================================================" << endl;

}

void testAssignmentOperator2() {
    cout << "Testing assignment operator 2" << endl;
    cout << "================================================================================" << endl;    
    Queue q1, q2;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q2 = q1;
    while (!q1.isEmpty()) {
        int peek = q1.peek();
        cout << "Removing " << peek << " from q1" << endl;
        q1.dequeue();
    }
    if (q1.isEmpty() && !q2.isEmpty()) {
        cout << "q1 is empty and q2 is not empty" << endl;
    }    
    cout << "================================================================================" << endl;

}

void testAssignmentOperator3() {
    cout << "Testing assignment operator 3" << endl;
    cout << "================================================================================" << endl;    
    Queue q1, q2;
    for(int i = 1; i <= 12; i++){
        q1.enqueue(i);
    }
    q2 = q1;

    int q1size = 0;
    int q2size = 0;

    while (!q1.isEmpty()) {
        int peek = q1.peek();
        cout << "Removing " << peek << " from q1" << endl;
        q1.dequeue();
        q1size++;
    }
    if (q1.isEmpty() && !q2.isEmpty()) {
        cout << "q1 is empty and q2 is not empty. Part 1 correct" << endl;
    }
    while (!q2.isEmpty()) {
        int peek = q2.peek();
        cout << "Removing " << peek << " from q2" << endl;
        q2.dequeue();
        q2size++;
    }
    if(q1size == q2size) cout << "sizes were equal. both portions passed" << endl;

    cout << "================================================================================" << endl;
}

void testEnqueue() {
    cout << "Testing enqueue" << endl;
    cout << "================================================================================" << endl;    
    // insert 0, 1, 2, 3, 4, 5
    Queue q;
    for (int i = 0; i < 6; i++) {
        q.enqueue(i);
    }
    // Remove first three
    // q: [] [] [] 3 4 5
    for (int i = 0; i < 3; i++) {
        q.dequeue();
    }
    // insert 6 7 8
    // q: 6 7 8 3 4 5 
    for (int i = 6; i < 9; i++) {
        q.enqueue(i);
    }

    q.enqueue(9);

    cout << "Desire output: 3 4 5 6 7 8 9" << endl;

    string s = "";
    while (!q.isEmpty()) {
        int peek = q.peek();
        q.dequeue();
        s += to_string(peek) + " ";
    }
    cout << "Final output: " << s << endl;
    cout << "================================================================================" << endl;

}

void testEnqueue2() {
    cout << "Testing enqueue 2" << endl;
    cout << "================================================================================" << endl;    
    // insert 0, 1, 2, 3, 4, 5
    Queue q;
    for (int i = 0; i < 6; i++) {
        q.enqueue(i);
    }

    q.enqueue(9);

    cout << "Desire output: 0 1 2 3 4 5 9" << endl;

    string s = "";
    while (!q.isEmpty()) {
        int peek = q.peek();
        q.dequeue();
        s += to_string(peek) + " ";
    }
    cout << "Final output: " << s << endl;
    cout << "================================================================================" << endl;

}

void testEnqueue3() {
    cout << "Testing enqueue 3" << endl;
    cout << "================================================================================" << endl;    
    // insert 0, 1, 2, 3, 4, 5
    Queue q;
    for (int i = 0; i < 6; i++) {
        q.enqueue(i);
    }

    // Remove 5
    // q: [] [] [] [] [] [] 5 
    for (int i = 0; i < 5; i++) {
        q.dequeue();
    }

    // insert 6 7 8 9 10

    for (int i = 6; i < 11; i++) {
        q.enqueue(i);
    }

    q.enqueue(11);

    cout << "Desire output: 5 6 7 8 9 10 11" << endl;

    string s = "";
    while (!q.isEmpty()) {
        int peek = q.peek();
        q.dequeue();
        s += to_string(peek) + " ";
    }
    cout << "Final output: " << s << endl;
    cout << "================================================================================" << endl;

}

void testEnqueue4() {
    cout << "Testing enqueue 4" << endl;
    cout << "================================================================================" << endl;    
    // insert 0, 1, 2, 3, 4, 5
    Queue q;
    for (int i = 0; i < 6; i++) {
        q.enqueue(i);
    }

    // Remove 1
    // q: [] 1 2 3 4 5 
    q.dequeue();

    // insert 6
    q.enqueue(6);

    q.enqueue(7);

    cout << "Desire output: 1 2 3 4 5 6 7" << endl;

    string s = "";
    while (!q.isEmpty()) {
        int peek = q.peek();
        q.dequeue();
        s += to_string(peek) + " ";
    }
    cout << "Final output: " << s << endl;
    cout << "================================================================================" << endl;
    
}

void testDequeue() {
    cout << "Testing dequeue" << endl;
    cout << "================================================================================" << endl;    

    Queue q;

    // insert 1 -> 7
    // q: 1 2 3 4 5 6 7 [] [] [] [] []
    int size = 0;
    for (int i = 1; i < 8; i++) {
        q.enqueue(i);
        size++;
    }    
    cout << "size: " << size << endl;
    // remove 1 -> 5
    // q: [] [] [] [] [] 6 7 [] [] [] [] []
    for (int i = 0; i < 5; i++) {
        q.dequeue();
        size--;
    }
    cout << "size: " << size << endl;

    string s = "";
    while (!q.isEmpty()) {
        int peek = q.peek();
        q.dequeue();
        s += to_string(peek) + " ";
    }
    cout << "Desired output: 6 7" << endl;
    cout << "Final output: " << s << endl;
    cout << "================================================================================" << endl;

}

void testDequeue2() {
    cout << "Testing dequeue 2" << endl;
    cout << "================================================================================" << endl;    

    Queue q;

    // insert 1 -> 12
    // q: 1 2 3 4 5 6 7 8 9 10 11 12
    int size = 0;
    for (int i = 1; i < 13; i++) {
        q.enqueue(i);
        size++;
    }    
    cout << "size: " << size << endl;
    // remove 1 -> 9
    // q: [] [] [] [] [] [] [] [] [] 10 11 12
    for (int i = 0; i < 9; i++) {
        q.dequeue();
        size--;
    }
    cout << "size: " << size << endl;

    // q: [13] [] [] [] [] [] [] [] [] 10 11 12
    q.enqueue(13);
    size++;

    // q: [13] [] [] [] [] [] [] [] [] [] [] 12
    q.dequeue();
    q.dequeue();
    size--;
    size--;
    cout << "size: " << size << endl;

    string s = "";
    while (!q.isEmpty()) {
        int peek = q.peek();
        q.dequeue();
        s += to_string(peek) + " ";
    }
    cout << "Desired output: 12 13" << endl;
    cout << "Final output: " << s << endl;
    cout << "================================================================================" << endl;

}

void testDequeue3() {
    cout << "Testing dequeue 3" << endl;
    cout << "================================================================================" << endl;    

    Queue q;

    // insert 1 -> 24
    // q: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 ... 24
    int size = 0;
    for (int i = 1; i < 25; i++) {
        q.enqueue(i);
        size++;
    }   
    cout << "size: " << size << endl;
    // remove 1 -> 21
    // q: [] [] [] [] [] [] ... 19 20 21 22 23 24
    for (int i = 0; i < 18; i++) {
        q.dequeue();
        size--;
    }
    int peek = q.peek();
    cout << "size: " << size << endl;
    cout << "peak: " << peek << endl;

    cout << "Adding on the left side"  << endl;

    // q: 25 26 27 ... [] [] [] [] [] [] [] [] [] .. 19 20 21 22 23 24
    q.enqueue(25);
    size++;
    q.enqueue(26);
    size++;
    q.enqueue(27);
    size++;

    cout << "size: " << size << endl;

    cout << "Removing from the right side" << endl;

    // q: 25 26 27 ... [] [] [] [] [] [] [] [] [] .. 23 24    
    q.dequeue();
    size--;  
    q.dequeue();
    peek = q.peek();
    size--;  
    q.dequeue();
    size--;  
    q.dequeue();
    size--;                

    peek = q.peek();
    cout << "size: " << size << endl;
    cout << "peak: " << peek << endl;

    string s = "";
    while (!q.isEmpty()) {
        int peek = q.peek();
        q.dequeue();
        s += to_string(peek) + " ";
    }
    cout << "Desired output: 23 24 25 26 27" << endl;
    cout << "Final output: " << s << endl;
    cout << "================================================================================" << endl;

}