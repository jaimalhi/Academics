#ifndef PCB_H
#define PCB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "main.h"

// process state enum
enum State {
    RUNNING,
    READY,
    BLOCKED,
    TERMINATED
};

// PCB structure
typedef struct PCB_struct PCB;
struct PCB_struct {
    int pid;
    int priority; // (0, 1, 2) 0 is highest priority
    enum State state; // Use enum instead of char for state
};

// Message structure
typedef struct Message_struct Message;
struct Message_struct {
    int sender_pid; 
    int receiver_pid; 
    char msg[41]; // fixed message size 40 chars
};

//* ================== HELPER FUNCTIONS ==============
// Get the current running process
// @return reference to the current running process, null if none
PCB* pcb_getRunningProcess();

// Find a process by PID
// @return reference to the process with given PID, NULL if not found
PCB* pcb_findProcessById(int pid);

// schedule next process based on preemptive round robin scheduling
// @return reference to the next process to run, NULL if none
PCB* pcb_scheduleNextProcess();

// initialize the init process to create first process with pid 0
void pcb_initProcess();

// set the init process state to READY
void pcb_setInitToReady();

// compare function to find a process by PID
// @return 0 if the process has the same PID, 1 otherwise
bool comparePID(void* process, void* pid);

//* ================== PCB FUNCTIONS ==================
// create a process and put it on the appropriate queue
// @return pid of the created process on success, -1 on failure
int pcb_create(int priority);

// copy the running process and put it on the appropriate queue
// attempting to fork the init process should fail
// @return pid of the resulting (new) process on success, -1 on failure
int pcb_fork();

// kill the named process and remove it from the queue
// allowed to kill a process that is not running (eg. blocked process)
// @return action taken & success (0) or failure (-1)
int pcb_kill(int pid);

// exit (kill) ONLY the currently running process
// @return pid of next process to run on success, -1 on failure
int pcb_exit();

// Time quantum has expired for the currently running process
// ONLY way to signal that the time quantum for round robin scheduling 
// has expired
// Move the process to the back of the queue, and run the next process,
// if no other process is ready to run, run init process
// @return pid of next process to run on success, -1 on failure
int pcb_quantum();

// send message to another process, BLOCKED until reply
// @return Message struct on success, NULL on failure
Message* pcb_send(int pid, char* msg);

// receive message from another process, BLOCKED until message received
// @return Message struct on success, NULL on failure
Message* pcb_receive();

// reply to a message from another process
// unblocks sender and delivers reply
// @return success (0) or failure (-1)
int pcb_reply(int pid, char* msg);

// print all information of a process to the screen
void pcb_procInfo(int pid);

#endif