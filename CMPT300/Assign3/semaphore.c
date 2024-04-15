#include "semaphore.h"

//* ================== HELPER FUNCTIONS ==============
// Find a semaphore by id
// @return reference to the semaphore with the ID, NULL if not found
Semaphore* getSemById(int semID){
    Node* node = List_first(semList);
    Semaphore* sem = (Semaphore*)List_curr(semList);
    while(node != NULL){
        if(sem->semID == semID){
            return sem;
        }
        node = List_next(semList);
        sem = (Semaphore*)List_curr(semList);
    }
    return NULL;
}

//* ================== SEMAPHORE FUNCTIONS ==================
Semaphore* Semaphore_create(int initialValue, int semID) {
    if (semID < 0 || semID >= 5 || semInitialized[semID]) {
        perror("Semaphore initialization failed: Invalid ID or Semaphore already initialized");
        return NULL;
    }
    
    Semaphore* semaphore = malloc(sizeof(Semaphore));
    if (semaphore == NULL) {
        perror("Failed to allocate memory for Semaphore");
        return NULL;
    }
    
    semaphore->value = initialValue;
    semaphore->semID = semID;
    semaphore->waitList = List_create();
    if (semaphore->waitList == NULL) {
        perror("Failed to create waitList for Semaphore");
        free(semaphore);
        return NULL;
    }
    
    semInitialized[semID] = true;
    List_append(semList, semaphore);
    return semaphore;
}


void Semaphore_P(int semID) {
    if (semID < 0 || semID >= 5 || !semInitialized[semID]) {
        perror("Semaphore P operation failed: Invalid ID or Semaphore not initialized");
        return;
    }

    Semaphore* sem = getSemById(semID);
    sem->value--;

    PCB* currentProcess = pcb_getRunningProcess();
    if (sem->value < 0) {
        // Block the current process and add it to the semaphore's wait list
        currentProcess->state = BLOCKED;
        List_append(sem->waitList, currentProcess);
        List_append(blockedProcesses, currentProcess);
    }
    // If the semaphore's value is not negative, the process continues
}


void Semaphore_V(int semID) {
    if (semID < 0 || semID >= 5 || !semInitialized[semID]) {
        perror("Semaphore V operation failed: Invalid ID or Semaphore not initialized");
        return;
    }

    Semaphore* sem = getSemById(semID);
    sem->value++;

    if (sem->value <= 0) {
        // Unblock one process from the wait list
        PCB* processToUnblock = List_trim(sem->waitList); // Following FIFO
        if (processToUnblock != NULL) {
            processToUnblock->state = READY;
            List_trim(blockedProcesses);

            PCB* nextProc = pcb_scheduleNextProcess();
            if(nextProc == NULL){
                printf("No process to run\n");
            }
        }
    }
    // If the semaphore's value is positive, no process needs to be unblocked
}


