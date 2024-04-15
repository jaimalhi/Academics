#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "pcb.h"
#include "main.h"

typedef struct Semaphore_struct Semaphore;
struct Semaphore_struct {
    int value;     // The semaphore value
    int semID;     // The semaphore ID
    List* waitList;  // List of PCBs waiting on this semaphore
};

// allocate memory for the semaphore, initialize its value, 
// and create a new list to hold any waiting processes
// @return: created sem on success, NULL on failure
Semaphore* Semaphore_create(int initialValue, int semID);

// The P (wait) operation decrements the semaphore. If the value 
// becomes negative, the process executing the operation is 
// blocked and added to the semaphore's wait list
void Semaphore_P(int semID);

// The V (signal) operation increments the semaphore. If the value 
// is zero or negative, a process is unblocked and removed from 
// the semaphore's wait list
void Semaphore_V(int semID);


#endif 