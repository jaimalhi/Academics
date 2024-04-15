#include "pcb.h"

// This variable will keep its value between function calls
static int pid_counter = 0; 

//* ================== HELPER FUNCTIONS ==============

PCB* pcb_getRunningProcess(){
    PCB* process = (PCB*)List_first(allProcesses);
    while(process != NULL){
        if(process->state == RUNNING){
            return process;
        }
        process = (PCB*)List_next(allProcesses);
    }
    return NULL;
}

PCB* pcb_findProcessById(int pid){
    PCB* process = (PCB*)List_first(allProcesses);
    while(process != NULL){
        if(process->pid == pid){
            return process;
        }
        process = (PCB*)List_next(allProcesses);
    }
    return NULL;
}

PCB* pcb_scheduleNextProcess() {
    if(priorityZeroQ == NULL || priorityOneQ == NULL || priorityTwoQ == NULL){
        printf("ERROR: Priority queues not initialized\n");
        return NULL;
    }
    // Check the highest priority queue first
    List* queues[] = {priorityZeroQ, priorityOneQ, priorityTwoQ};

    for (int i = 0; i < 3; i++) {
        if (List_count(queues[i]) > 0) {
            PCB* process = (PCB*)List_first(queues[i]);
            while (process != NULL) {
                if (process->state == READY) {
                    // Found a ready process, set it to RUNNING
                    process->state = RUNNING;
                    // Set the init process to READY if not the one running
                    if(process->pid != INIT_PID){
                        pcb_setInitToReady();
                    }
                    // Remove from the ready queue
                    List_remove(queues[i]);
                    // Append to the end for round-robin behavior within the same priority
                    List_append(queues[i], process);
                    return process; // Return the process to run next
                }
                process = (PCB*)List_next(queues[i]);
            }
        }
    }
    return NULL; 
}

void pcb_initProcess(){
    if(List_count(allProcesses) > 0){
        printf("ERROR: Init process already exists\n");
        return;
    }
    PCB* newPCB = (PCB*)malloc(sizeof(PCB));
    if(newPCB == NULL){
        printf("Failed to allocate memory for init PCB");
    }
    newPCB->pid = 0;
    newPCB->priority = 0;
    newPCB->state = RUNNING;
    List_append(allProcesses, newPCB);
}

void pcb_setInitToReady(){
    PCB* initProcess = pcb_findProcessById(INIT_PID);
    if(initProcess != NULL){
        initProcess->state = READY;
    }
}

bool comparePID(void* process, void* pid) {
    PCB* pcbProcess = (PCB*)process;
    int targetPID = *(int*)pid;

    // Debug prints
    printf("\n\nComparing process PID: %d with target PID: %d\n\n", pcbProcess->pid, targetPID);
    return (pcbProcess->pid == targetPID) ? true : false;
}

//* ================== PCB FUNCTIONS ==================

int pcb_create(int priority){
    PCB* newPCB = (PCB*)malloc(sizeof(PCB));
    if(newPCB == NULL){
        printf("Failed to allocate memory for PCB");
        return -1;
    }

    // Increment the counter and assign the new value as pid
    newPCB->pid = ++pid_counter; 
    newPCB->priority = priority;
    //If first process on the queue, then it will run
    if(List_count(allProcesses) == 0){
        newPCB->state = RUNNING;
    } else { 
        newPCB->state = READY;
    }

    List_append(allProcesses, newPCB);
    // Add the new PCB to the appropriate queue
    if(priorityZeroQ != NULL && priority == 0){
        List_append(priorityZeroQ, newPCB);
    } else if(priorityOneQ != NULL && priority == 1){
        List_append(priorityOneQ, newPCB);
    } else if(priorityTwoQ != NULL && priority == 2){
        List_append(priorityTwoQ, newPCB);
    }

    return newPCB->pid;
}

int pcb_fork(){
    PCB* runningProcess = pcb_getRunningProcess();
    if(runningProcess->pid == INIT_PID){
        printf("ERROR: Cannot fork the init process");
        return -1;
    }
    if(runningProcess == NULL){
        printf("ERROR: No running process to fork");
        return -1;
    }

    PCB* newPCB = (PCB*)malloc(sizeof(PCB));
    if(newPCB == NULL){
        printf("Failed to allocate memory for PCB");
        return -1;
    }

    // Increment the counter and assign the new value as pid
    newPCB->pid = ++pid_counter; 
    newPCB->priority = runningProcess->priority;
    newPCB->state = READY;

    List_append(allProcesses, newPCB);
    // Add the new PCB to the appropriate queue
    if(priorityZeroQ != NULL && newPCB->priority == 0){
        List_append(priorityZeroQ, newPCB);
    } else if(priorityOneQ != NULL && newPCB->priority == 1){
        List_append(priorityOneQ, newPCB);
    } else if(priorityTwoQ != NULL && newPCB->priority == 2){
        List_append(priorityTwoQ, newPCB);
    }

    return newPCB->pid;
}

int pcb_kill(int pid) {
    if (List_count(allProcesses) == 0) {
        printf("ERROR: Process list is empty\n");
        return -1;
    }

    // Check if this is the init process and if it is allowed to be killed
    if (pid == INIT_PID && List_count(allProcesses) == 1) {
        PCB* initProcess = pcb_findProcessById(pid);
        if (initProcess != NULL) {
            initProcess->state = TERMINATED;
            // Since init is terminated, terminate the simulation
            return 0; // special case
        }
    } else if(pid == INIT_PID){
        printf("Cannot kill init when processes still exist");
        return -1;
    }

    PCB* processToKill = pcb_findProcessById(pid);
    if (processToKill == NULL) {
        printf("ERROR: Process with PID: %d not found\n", pid);
        return -1;
    }

    if(priorityZeroQ == NULL || priorityOneQ == NULL || priorityTwoQ == NULL){
        printf("ERROR: Priority queues not initialized\n");
        return -1;
    }
    // Remove the process from its respective priority queue
    List* queues[] = {priorityZeroQ, priorityOneQ, priorityTwoQ};
    if (processToKill->priority >= 0 && processToKill->priority <= 2) {
        List* queue = queues[processToKill->priority];
        Node* node = List_first(queue);
        while (node != NULL) {
            PCB* process = (PCB*)List_curr(queue);
            if (process->pid == pid) {
                List_remove(queue); 
                break;
            }
            node = List_next(queue);
        }
    }

    // If the process to kill is currently running, schedule the next process
    if (processToKill->state == RUNNING) {
        pcb_scheduleNextProcess();
    }

    // Now remove the process from the allProcesses list
    Node* node = List_first(allProcesses);
    while (node != NULL) {
        PCB* process = (PCB*)List_curr(allProcesses);
        if (process->pid == pid) {
            List_remove(allProcesses); 
            free(processToKill); 
            break;
        }
        node = List_next(allProcesses);
    }
    return 0; // Success
}

int pcb_exit(){
    PCB* runningProcess = pcb_getRunningProcess();
    if(runningProcess == NULL){
        printf("ERROR: No running process to exit");
        return -1;
    }
    // Kill the running process, get pid of next process to run
    int exitResult = pcb_kill(runningProcess->pid);
    if(exitResult == -1){
        printf("ERROR: Failed to exit the running process");
        return -1;
    }
    return exitResult;
}

int pcb_quantum(){
    PCB* runningProcess = pcb_getRunningProcess();
    if(runningProcess == NULL){
        printf("ERROR: No running process to expire quantum");
        return -1;
    };
    // Get the next process in the queue and return its PID
    PCB* nextProcess = pcb_scheduleNextProcess();

    // set state to ready after setting new process to running
    runningProcess->state = READY;
    return nextProcess->pid;
}

Message* pcb_send(int receiver_pid, char* msg) {
    PCB* sender = pcb_getRunningProcess();
    PCB* receiver = pcb_findProcessById(receiver_pid);

    if (sender == NULL || receiver == NULL || strlen(msg) > 40) {
        return NULL; // Fail conditions
    }

    Message* message = (Message*)malloc(sizeof(Message));
    if (message == NULL) {
        printf("Failed to allocate memory for message");
        return NULL;
    }

    message->sender_pid = sender->pid;
    message->receiver_pid = receiver->pid;
    strncpy(message->msg, msg, 40);
    message->msg[40] = '\0'; // Ensure null-termination

    List_append(messageQ, message);
    sender->state = BLOCKED;
    List_append(blockedProcesses, sender);

    PCB* nextProc = pcb_scheduleNextProcess(); 
    if(nextProc == NULL){
        printf("ERROR: Failed to schedule next process after sending message\n");
        return NULL;
    }

    return message;
}

Message* pcb_receive(){
    PCB* receiver = pcb_getRunningProcess();
    if (receiver == NULL) {
        printf("ERROR: No running process to receive message\n");
        return NULL; // No running process
    }

    PCB* senderProc = (PCB*)List_first(messageQ);
    while (senderProc != NULL) {
        Message* message = (Message*)List_curr(messageQ);
        if (message->receiver_pid == receiver->pid) {
            List_remove(messageQ); 
            return message;
        }
        senderProc = (PCB*)List_next(messageQ);
    }
    // No message found, block the receiver
    receiver->state = BLOCKED;
    List_append(blockedProcesses, receiver);

    PCB* nextProc = pcb_scheduleNextProcess(); 
    if(nextProc == NULL){
        printf("ERROR: Failed to schedule next process after sending message\n");
        return NULL;
    }

    return NULL; // No message found
}

int pcb_reply(int pid, char* reply_msg) {
    PCB* receiver = pcb_getRunningProcess();
    PCB* sender = pcb_findProcessById(pid);

    if (receiver == NULL || sender == NULL || strlen(reply_msg) > 40) {
        return -1; // Invalid parameters or reply message too long
    }

    // Create the reply message
    Message* reply = (Message*)malloc(sizeof(Message));
    if (reply == NULL) {
        perror("Failed to allocate memory for reply");
        return -1;
    }
    reply->sender_pid = receiver->pid;
    reply->receiver_pid = sender->pid;
    strncpy(reply->msg, reply_msg, 40);
    reply->msg[40] = '\0'; // Ensure null termination

    // Unblocks the sender
    sender->state = READY;
    // Remove the sender from the blocked queue 
    List_trim(blockedProcesses);

    // Add the reply to the sender's message queue
    List_append(messageQ, reply);

    return 0;
}

void pcb_procInfo(int pid){
    PCB* process = pcb_findProcessById(pid);
    if(process == NULL){
        printf("ERROR: Process ID %d not found\n", pid);
    } else {
        printf("Process ID: %d\n", process->pid);
        printf("Priority: %d\n", process->priority);
        if(process->state == 0){
            printf("State: RUNNING\n");
        } else if(process->state == 1){
            printf("State: READY\n");
        } else if(process->state == 2){
            printf("State: BLOCKED\n");
        } else if(process->state == 3){
            printf("State: TERMINATED\n");
        }
    }
    return;
}