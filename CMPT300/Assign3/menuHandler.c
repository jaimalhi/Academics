#include "menuHandler.h"

void menu_startUp(){
    printf("====== MENU: CHOOSE ONE OF THE FOLLOWING OPTIONS ======\n");
    printf("C = Create a new process\n");
    printf("F = Fork current process\n");
    printf("K = Kill & Remove named process\n");
    printf("E = Exit current process\n");
    printf("Q = Expire time quantum of running process\n");
    printf("S = Send message to another process\n"); // BLOCKING
    printf("R = Receive message from another process\n"); // BLOCKING
    printf("Y = Reply to sender\n");
    printf("N = Create new semaphore\n");
    printf("P = Semaphore P operation\n");
    printf("V = Semaphore V operation\n");
    printf("I = Print all information\n");
    printf("T = Print the process control block of all processes\n");
    printf("X = Exit the program\n");
    printf("=======================================================\n");
    printf("Enter a letter to select an option: ");
}

char menu_response(){
    menu_startUp(); // display the menu
    char input; // user input

    while ((input = getchar()) == '\n' || input == EOF) { } 

    return toupper(input); // convert to uppercase
}

void menu_handleUserInput(char response, bool *runState){
    char input; // user input if needed
    int nextProcess; // next process to run
    int pid; // process id
    int semID; // semaphore id
    switch(response){
        // ================== Create (C) ==================
        case 'C':
            printf("Create a new process, enter priority (0 - high, 1 - medium, 2 - low)\n");
            // Consume any extra newline characters left in the input buffer.
            while ((input = getchar()) != '\n' && input != EOF) { } 
            int priority;
            // Use scanf to read the process ID.
            if (scanf("%d", &priority) == 1) { 
                if(priority < 0 || priority > 2){
                    printf("Invalid priority: %d\n", priority);
                    break;
                }
                pcb_create(priority);
            } else {
                printf("Invalid input\n");
            }
            break;
        // ================== Fork (F) =========================
        case 'F':
            printf("Fork current process\n");
            int result = pcb_fork();
            if (result == -1) {
                printf("Failed to fork process\n");
            } else {
                printf("Forked process with PID: %d\n", result);
            }
            break;
        // ================== Kill (K) =========================
        case 'K':
            if(List_count(allProcesses) <= 1){
                printf("No processes to kill\n"); 
                break;
            }
            printf("Kill & Remove named process, enter id to remove: ");

            // Consume any extra newline characters left in the input buffer.
            while ((input = getchar()) != '\n' && input != EOF) { } 
            // Use scanf to read the process ID.
            if (scanf("%d", &pid) == 1) { 
                int result = pcb_kill(pid);
                if (result == -1) {
                    printf("Failed to kill process with PID: %d\n", pid);
                } else {
                    printf("Killed process with PID: %d\n", pid);
                }
            } else {
                printf("Invalid input. Please enter a valid process ID.\n");
                // Clear the input buffer to avoid hanging 
                while ((input = getchar()) != '\n' && input != EOF) { } 
            }
            break;
        // ================== Exit (E) =========================
        case 'E':
            printf("Exit current process\n");
            nextProcess = pcb_exit();
            printf("Next process to run (pid): %d\n", nextProcess);
            break;
        // ================== Quantum (Q) ======================
        case 'Q':
            printf("Expire time quantum of running process\n");
            if(List_count(allProcesses) <= 2){
                printf("No sibling process to switch to\n");
                break;
            }
            nextProcess = pcb_quantum();
            printf("Next process to run (pid): %d\n", nextProcess);
            break;
        // ================== Send (S) =========================
        case 'S':
            printf("Send message to another process\n");

            printf("Enter the pid of the receiver: ");
            if (scanf("%d", &pid) != 1) { // Clear the buffer
                printf("Invalid input for PID.\n");
                while ((input = getchar()) != '\n' && input != EOF) { }
                break; 
            }
            // Clear leftover newline character before reading next input
            while ((input = getchar()) != '\n' && input != EOF) { }

            // Get the message to send
            char messageToSend[41];
            printf("Enter the message to send (max 40 characters): ");
            if (fgets(messageToSend, 41, stdin) == NULL) {
                printf("Error reading message.\n");
                break;
            }
            // Remove newline character, if present
            messageToSend[strcspn(messageToSend, "\n")] = 0;

            // Send the message
            Message* messageSent = pcb_send(pid, messageToSend);
            if (messageSent == NULL) {
                printf("Failed to send message.\n");
            } else {
                printf("Message sent successfully\n");
                printf("Sender PID: %d\n", messageSent->sender_pid);
                printf("Receiver PID: %d\n", messageSent->receiver_pid);
                printf("Message: %s\n", messageSent->msg);
            }
            break;
        // ================== Receive (R) ======================
        case 'R':
            printf("Receive message from another process\n");
            Message* messageReceived = pcb_receive();
            if (messageReceived == NULL) {
                printf("Failed to receive message\n");
            } else {
                printf("Message received successfully\n");
                printf("Sender PID: %d\n", messageReceived->sender_pid);
                printf("Receiver PID: %d\n", messageReceived->receiver_pid);
                printf("Message: %s\n", messageReceived->msg);
            }
            free(messageReceived);
            break;
        // ================== Reply (Y) ========================
        case 'Y':
            printf("Reply to sender\n");

            printf("Enter the pid of the sender you are replying to: ");
            // Read the PID using scanf and clear the input buffer afterward
            if (scanf("%d", &pid) != 1) {
                printf("Invalid input for PID.\n");
                // Clear the buffer
                while ((input = getchar()) != '\n' && input != EOF) { }
                break; // Skip further processing if PID input is invalid
            }
            // Clear leftover newline character before reading next input
            while ((input = getchar()) != '\n' && input != EOF) { }

            // Get the message to send
            char messageReplied[41];
            printf("Enter the reply message (max 40 characters): ");
            if (fgets(messageReplied, 41, stdin) == NULL) {
                printf("Error reading message.\n");
                break;
            }
            // Remove newline character, if present
            messageReplied[strcspn(messageReplied, "\n")] = 0;

            int replyResult = pcb_reply(pid, messageReplied);
            if (replyResult == -1) {
                printf("Failed to send reply.\n");
            } else {
                printf("Reply sent successfully.\n");
                printf("Your PID: %d\n", pid);
                printf("Message: %s\n", messageReplied);
            }
            break;
        // ================== New Semaphore (N) ================
        case 'N':
            printf("Create new semaphore\n");
            semID = -1;
            for (int i = 0; i < 5; i++) {
                if (!semInitialized[i]) {
                    semID = i;
                    break;
                }
            }
            if (semID == -1) {
                printf("All semaphores already initialized\n");
            } else {
                printf("Enter the initial value of the semaphore (>0): ");
                // Clear the input buffer before reading the next input
                while ((input = getchar()) != '\n' && input != EOF) { } 
                int semValue;
                // Use scanf to read the process ID.
                if (scanf("%d", &semValue) == 1) { 
                    Semaphore* result = Semaphore_create(semValue, semID);
                    if (result == NULL) {
                        printf("Failed to create semaphore");
                    } else {
                        printf("Created semaphore");
                    }
                } else {
                    printf("Invalid input. Please enter a valid ID.\n");
                    // Clear the input buffer to avoid hanging 
                    while ((input = getchar()) != '\n' && input != EOF) { } 
                }
            }
            break;
        // ================== Semaphore P (P) ==================
        case 'P':
            printf("Semaphore P operation\n");
            // display the semaphore ids available
            printf("Available semaphore IDs: ");
            for (int i = 0; i < 5; i++) {
                if (semInitialized[i]) {
                    printf("%d ", i);
                }
            }
            printf("\nEnter the id of the semaphore: ");

            // Read the semaphore ID using scanf and clear the input buffer afterward
            if (scanf("%d", &semID) != 1) {
                printf("Invalid input. Please enter a valid semaphore ID.\n");
                // Clear the buffer
                while ((input = getchar()) != '\n' && input != EOF) { }
                break; // Skip further processing if input is invalid
            }

            if (semID < 0 || semID >= 5) {
                printf("Invalid semaphore id: %d\n", semID);
            } else if (!semInitialized[semID]) {
                printf("Semaphore not initialized: %d\n", semID);
            } else {
                printf("Running Semaphore P operation: %d\n", semID);
                Semaphore_P(semID);
            }
            break;
        // ================== Semaphore V (V) ==================
        case 'V':
            printf("Semaphore V operation\n");
            // display the semaphore ids available
            printf("Available semaphore IDs: ");
            for (int i = 0; i < 5; i++) {
                if (semInitialized[i]) {
                    printf("%d ", i);
                }
            }
            printf("\nEnter the id of the semaphore: ");

            // Read the semaphore ID using scanf and clear the input buffer afterward
            if (scanf("%d", &semID) != 1) {
                printf("Invalid input. Please enter a valid semaphore ID.\n");
                // Clear the buffer
                while ((input = getchar()) != '\n' && input != EOF) { }
                break; // Skip further processing if input is invalid
            }

            if (semID < 0 || semID >= 5) {
                printf("Invalid semaphore id: %d\n", semID);
            } else if (!semInitialized[semID]) {
                printf("Semaphore not initialized: %d\n", semID);
            } else {
                printf("Running Semaphore V operation: %d\n", semID);
                Semaphore_V(semID);
            }
            break;
        // ================== Print all info (I) ===============
        case 'I':
            printf("Print process information, enter id: ");
            // Consume any extra newline characters left in the input buffer.
            while ((input = getchar()) != '\n' && input != EOF) { } 
            // Use scanf to read the process ID.
            if (scanf("%d", &pid) == 1) { // Ensure scanf successfully reads an integer.
                pcb_procInfo(pid);
            } else {
                printf("Invalid input. Please enter a valid process ID.\n");
                // Clear the input buffer to avoid hanging 
                while ((input = getchar()) != '\n' && input != EOF) { } 
            }
            break;
        // ================== Print PCBs (T) ====================
        case 'T':
            printf("Print the process control block of all processes\n");
            totalInfo();
            break;
        // ================== Exit Program (X) =================
        case 'X':
            printf("Exit the program\n");
            *runState = false;
            break;
        default:
            printf("Invalid input: No process found\n");
            break;
    }
    input = getchar(); // clear the buffer
    nextProcess = -1; // reset the process value
    pid = -1; // reset the pid value
    semID = -1; // reset the semaphore id
}