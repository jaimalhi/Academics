#include "main.h"

List* allProcesses = NULL;
List* blockedProcesses = NULL;
List* priorityZeroQ = NULL;
List* priorityOneQ = NULL;
List* priorityTwoQ = NULL;
List* messageQ = NULL;
List* semList = NULL; 
// check if a semaphore is already initialized
bool semInitialized[5] = {false, false, false, false, false}; 

void freeItem(void* pItem){
    if(pItem != NULL){
        free(pItem);
    }
}

void init(){
    printf("========= System Initialization =========\n");
    blockedProcesses = List_create();
    priorityZeroQ = List_create();
    priorityOneQ = List_create();
    priorityTwoQ = List_create();
    messageQ = List_create();
    semList = List_create();
}

void shutdown(){
    printf("========= System Shutdown =========\n");
    List_free(allProcesses, &freeItem);
    List_free(blockedProcesses, &freeItem);
    List_free(priorityZeroQ, &freeItem);
    List_free(priorityOneQ, &freeItem);
    List_free(priorityTwoQ, &freeItem);
    List_free(messageQ, &freeItem);
    List_free(semList, &freeItem);
}

void totalInfo(){
    printf("========= Total Information =========\n");

    int totalProcesses = List_count(allProcesses);
    printf("Total number of processes: %d\n", totalProcesses);
    // display the contents of all queues
    Node* node = List_first(allProcesses);
    PCB* process = (PCB*)List_curr(allProcesses);
    while (node != NULL) {
        printf("PID: %d, Priority: %d, ", process->pid, process->priority);
        if(process->state == 0){
            printf("State: RUNNING\n");
        } else if(process->state == 1){
            printf("State: READY\n");
        } else if(process->state == 2){
            printf("State: BLOCKED\n");
        } else if(process->state == 3){
            printf("State: TERMINATED\n");
        }
        node = List_next(allProcesses);
        process = (PCB*)List_curr(allProcesses);
    }
}

int main() {
    init(); // initialize the system

    allProcesses = List_create();
    if(allProcesses == NULL){
        printf("Failed to create all Processes list\n");
        return -1;
    }
    bool running = true; // flag to keep the program running

    pcb_initProcess(); // create the init process with pid 0

    while(running){
        // Handle user input.
        printf("\n\n");
        char response = menu_response();
        menu_handleUserInput(response, &running);

        // Check if the init process should be run.
        if (List_count(allProcesses) == 1) {
            PCB* initProcess = pcb_findProcessById(INIT_PID);
            // If the init process not terminated, consider running
            if(initProcess != NULL && initProcess->state == READY){
                printf("Init process running\n");
                initProcess->state = RUNNING;
            } else if (initProcess != NULL && initProcess->state != TERMINATED){
                printf("Running process with PID: %d\n", initProcess->pid);
            }
        } else if (List_count(allProcesses) == 2){
            // Run scheduler to first non-init process (if any)
            PCB* nextProcess = pcb_scheduleNextProcess();
            if (nextProcess != NULL) {
                printf("Running process with PID: %d\n", nextProcess->pid);
            }
        } // else: run next process when QUANTUM called

        // Check if the simulation should terminate.
        if (List_count(allProcesses) == 1 && pcb_findProcessById(INIT_PID)->state == TERMINATED) {
            running = false;
        }
    }
    shutdown();
    return 0;
}