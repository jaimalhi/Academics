#include "threadHandler.h"
#include "socketHandler.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Mutexs
static pthread_mutex_t sendListMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t receiveListMutex = PTHREAD_MUTEX_INITIALIZER;
// Condition variables
static pthread_cond_t inputListNotEmpty = PTHREAD_COND_INITIALIZER;
static pthread_cond_t outputListNotEmpty = PTHREAD_COND_INITIALIZER;
// Threads
static pthread_t outputThread;
static pthread_t receiveThread;
static pthread_t inputThread;
static pthread_t sendThread;

#define MAX_MESSAGE_LEN 1024

// read from user input and insert into list
void* ThreadHandler_inputThread(void* threadarg){
    // wrap threadarg with struct to pass in List
    ListShare* threadArguments = (ListShare*) threadarg;
    List* sendList = threadArguments->sharedList;
    
    char input[MAX_MESSAGE_LEN];

    while(1) {
        fputs("Enter to send, ! to quit: ", stdout);

        if(fgets(input, sizeof(input), stdin) != NULL) {            
            pthread_mutex_lock(&sendListMutex);
            {
                List_prepend(sendList, input);
                pthread_cond_signal(&outputListNotEmpty);
            }
            pthread_mutex_unlock(&sendListMutex);
        } 
        else {
            perror("Error reading input");
        }
    }
    return NULL;
}

// pick message from list and send message
void* ThreadHandler_sendThread(void* threadarg) {
    ListShare* threadArguments = (ListShare*) threadarg;
    List* sendList = threadArguments->sharedList;
    const char* destinationIpAddress = threadArguments->ip_address;
    int destinationPort = threadArguments->port;
    char* message;
    
    while(1) { 
        pthread_mutex_lock(&sendListMutex);
        {
            //pick message from list
            while(List_count(sendList) == 0){
                pthread_cond_wait(&outputListNotEmpty, &sendListMutex);
            }

            message = List_trim(sendList);
        }
        pthread_mutex_unlock(&sendListMutex);

        // If the list is empty (message is NULL)
        if(message == NULL) {
            sleep(1); // wait before checking again
            continue;
        }

        // send message
        SocketHandler_socketSend(destinationIpAddress, destinationPort, message);

        if(strcmp(message, "!\n") == 0){
            ThreadHandler_shutdown();
            break;
        }
    }
    return NULL;
}

// receive message and insert the message into the list
void* ThreadHandler_receiveThread(void* threadarg) {
    ListShare* threadArguments = (ListShare*) threadarg;
    List* receiveList = threadArguments->sharedList;
    int listeningPort = threadArguments->port;
    char* message;

    while(1){
        //retreive message with receive_socket
        message = SocketHandler_socketReceive(listeningPort);

        //if message exists
        if(message != NULL){
            // help protect against unexpected overwrites
            char* storedMessage = strdup(message);

            if(strcmp(storedMessage, "!\n") == 0){
                free(message);
                free(storedMessage);
                ThreadHandler_shutdown();
                break;
            }
            pthread_mutex_lock(&receiveListMutex);
            {
                //insert the message into the list
                List_prepend(receiveList, storedMessage);
                pthread_cond_signal(&inputListNotEmpty);
                //free original message
                free(message);
            }
            pthread_mutex_unlock(&receiveListMutex);
        } else {
            sleep(1); //avoid busy-wait
        }
    }
    return NULL;
}

//pick message from receive list and write onto the console
void* ThreadHandler_outputThread(void* threadarg){
    ListShare* threadArguments = (ListShare*) threadarg;
    List* displayList = threadArguments->sharedList;
    char* message;

    while(1){
        pthread_mutex_lock(&receiveListMutex);
        {
            while(List_count(displayList) == 0){
                pthread_cond_wait(&inputListNotEmpty, &receiveListMutex);
            }
            message = List_trim(displayList); // get messages from list
        }
        pthread_mutex_unlock(&receiveListMutex);

        if(message == NULL) {
            sleep(1); //wait before checking again
            continue;
        }
        
        //write on console
        fputs("\nMessage: ", stdout);
        fputs(message, stdout);
        free(message);
    }
    return NULL;
}

void ThreadHandler_init(int port, int remotePort, char* remoteIp, List* inputList, List* outputList){
    // Shared input
    ListShare inputArgs;
    inputArgs.sharedList = inputList;
    inputArgs.port = port;

    // Shared output
    ListShare outputArgs;
    outputArgs.sharedList = outputList;
    outputArgs.ip_address = remoteIp;
    outputArgs.port = remotePort;

    printf("Listening on port: %d\n\n", port);

    // create threads
    pthread_create(&inputThread, NULL, ThreadHandler_inputThread, &outputArgs);
    pthread_create(&sendThread, NULL, ThreadHandler_sendThread, &outputArgs);
    pthread_create(&receiveThread, NULL, ThreadHandler_receiveThread, &inputArgs);
    pthread_create(&outputThread, NULL, ThreadHandler_outputThread, &inputArgs);
    
    // wait for all threads to finish
    pthread_join(inputThread, NULL);
    pthread_join(sendThread, NULL);
    pthread_join(receiveThread, NULL);
    pthread_join(outputThread, NULL);
}

void ThreadHandler_shutdown(){
    pthread_cancel(outputThread);
    pthread_cancel(receiveThread);
    pthread_cancel(inputThread);
    pthread_cancel(sendThread);
}
