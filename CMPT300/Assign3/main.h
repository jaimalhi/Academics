#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "list.h"
#include "pcb.h"
#include "semaphore.h"
#include "menuHandler.h"

#define INIT_PID 0

extern List* allProcesses;
extern List* blockedProcesses;

extern List* priorityZeroQ;
extern List* priorityOneQ;
extern List* priorityTwoQ;

extern List* messageQ;
extern List* semList; 

extern bool semInitialized[5];


void init();

void shutdown();

// free all memory allocated for the process queues
void freeItem(void* item);

// display all process queues and their contents onto the screen
void totalInfo();

#endif 