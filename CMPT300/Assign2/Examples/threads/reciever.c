#include "reciever.h"
#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>  
#include <unistd.h> 
#include <netdb.h>

#define MAX_LEN 1024
#define PORT 22110
#define DYNAMIC_LEN 128

// create a mutex for critical section handling
static pthread_mutex_t dynamicMsgMutex = PTHREAD_MUTEX_INITIALIZER;

static int socketDescriptor;
static pthread_t threadPID;
static char* s_rxMessage;

// Everyone dynamicMessage is used should be treated as a critical section
static char* dynamicMessage;


void* receiveThread(void* unused){
    // dynamically allocate message
    pthread_mutex_lock(&dynamicMsgMutex);
    { // inside critical section
        strcpy(dynamicMessage, "Dynamic!")
    }
    pthread_mutex_unlock(&dynamicMsgMutex);

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin)); // clear memory for sin
    sin.sin_family = AF_INET; // connection may be from network
    sin.sin_addr.s_addr = htonl(INADDR_ANY); // Host to Network Long
    sin.sin_port = htons(PORT); // Host to Network Short

    // Create and bind to socket
    socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);

    // bind socket to specified port & open socket
    bind(socketDescriptor, (struct sockaddr*)&sin, sizeof(sin));

    while(1){
        // Receive Data (blocking call)
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char messageRx[MAX_LEN]; // buffer Rx

        // clients data written into messageRx string
        // sinRemote is output parameter
        // sinLen is input/output parameter (passed as pointers)
        int bytesRx = recvfrom(socketDescriptor, messageRx, MAX_LEN, 0, (struct sockaddr*) &sinRemote, &sin_len);

        // do somethihng amazing with the received message!
        pthread_mutex_lock(&dynamicMsgMutex);
        { // inside critical section
            printf("%s >> %s: %s\n", dynamicMessage, s_rxMessage, messageRx);
        }
        pthread_mutex_unlock(&dynamicMsgMutex);
    }

    // NEVER EXECUTES B\C THREAD IS CANCELLED
    printf("Done rx thread!");
    return NULL;
}

void Receiver_init(char* rxMessage){
    dynamicMessage = malloc(DYNAMIC_LEN);

    s_rxMessage = rxMessage;
    pthread_create(
        &threadPID,     // PID (by pointer)
        NULL,           // attributes  
        receiveThread,  // functions
        NULL            // attributes passed to the function
    );
}

void Receiver_changeDynamicMessage(char* newDynamicMessage){
    pthread_mutex_lock(&dynamicMsgMutex);
    { // inside critical section
        strncpy(dynamicMessage, newDynamicMessage, DYNAMIC_LEN);
    }
    pthread_mutex_unlock(&dynamicMsgMutex);
}

void Receiver_shutdown(void){
    // close socket
    close(socketDescriptor);
    // cancel the thread
    pthread_cancel(threadPID);
    // wait for the threads to finish before exiting
    pthread_join(threadPID, NULL);
    
    // cleanup memory (overkill b/c program is ending, but good practice)
    pthread_mutex_lock(&dynamicMsgMutex);
    { // inside critical section
        free(dynamicMessage); 
    }
    pthread_mutex_unlock(&dynamicMsgMutex);
}