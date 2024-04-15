#include "threadHandler.h"
#include "socketHandler.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Mutexs
static pthread_mutex_t mutexSendQueue = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexReceiveQueue = PTHREAD_MUTEX_INITIALIZER;
// Condition variables
static pthread_cond_t condSendQueueNotEmpty = PTHREAD_COND_INITIALIZER;
static pthread_cond_t condReceiveQueueNotEmpty = PTHREAD_COND_INITIALIZER;
// Threads
static pthread_t threadProducer, threadSender, threadReceiver, threadConsumer;

// max length for messages
#define MAX_MESSAGE_LEN 1024

// Read user input and queue for sending
void* ThreadHandler_producer(void* threadargs) {
    ListShare* threadArguments = (ListShare*)threadargs;
    List* sendQueue = threadArguments->sharedList;
    char input[MAX_MESSAGE_LEN];
    //Reading input
    while (1) {
        fputs("Enter message ('!' to quit): ", stdout);
        if (fgets(input, sizeof(input), stdin)) {
            pthread_mutex_lock(&mutexSendQueue);
            {
                List_prepend(sendQueue, strdup(input)); 
                pthread_cond_signal(&condSendQueueNotEmpty);
            }
            pthread_mutex_unlock(&mutexSendQueue);
        } else {
            perror("ERROR: Cannot read input");
        }
    }
    return NULL;
}
// sends message over network
void* ThreadHandler_sender(void* threadargs) {
    ListShare* threadArguments = (ListShare*)threadargs;
    List* sendQueue = threadArguments->sharedList;
    char* message;
    //loop until ! is called
    while (1) {
        pthread_mutex_lock(&mutexSendQueue);
        {
            while (List_count(sendQueue) == 0) {
                pthread_cond_wait(&condSendQueueNotEmpty, &mutexSendQueue);
            }
            message = List_trim(sendQueue);
        }
        pthread_mutex_unlock(&mutexSendQueue);
        //send message
        if (message) {
            SocketHandler_socketSend(threadArguments->ip_address, threadArguments->port, message);
            if (strcmp(message, "!\n") == 0) {
                free(message);
                ThreadHandler_shutdown();
                break;
            }
            free(message);
        }
    }
    return NULL;
}
// recieve message from network and queue them
void* ThreadHandler_receiver(void* threadargs) {
    ListShare* threadArguments = (ListShare*)threadargs;
    List* receiveQueue = threadArguments->sharedList;
    char* message;
    //loop until ! is called
    while (1) {
        message = SocketHandler_socketReceive(threadArguments->port);
        if (message) {
            if (strcmp(message, "!\n") == 0) {
                free(message);
                ThreadHandler_shutdown(); 
                break; 
            }
            pthread_mutex_lock(&mutexReceiveQueue);
            {
                //insert the message into the list
                List_prepend(receiveQueue, message);
                pthread_cond_signal(&condReceiveQueueNotEmpty);
            }
            pthread_mutex_unlock(&mutexReceiveQueue);
        } else {
            sleep(1); // Avoid busy-waiting
        }
    }
    return NULL;
}
// displays messages
void* ThreadHandler_consumer(void* threadargs) {
    ListShare* threadArguments = (ListShare*)threadargs;
    List* receiveQueue = threadArguments->sharedList;
    char* message;
    //process recieved messages
    while (1) {
        pthread_mutex_lock(&mutexReceiveQueue);
        {
            while (List_count(receiveQueue) == 0) {
                pthread_cond_wait(&condReceiveQueueNotEmpty, &mutexReceiveQueue);
            }
            message = List_trim(receiveQueue); // get messages from list
        }
        pthread_mutex_unlock(&mutexReceiveQueue);
        //write on console
        if (message) {
            fputs("RECIEVED: ", stdout);
            fputs(message, stdout);
            free(message);
        }
    }
    return NULL;
}
// initialize all threads
void ThreadHandler_init(int listenPort, int targetPort, char* targetIP, List* sendQueue, List* receiveQueue) {
    ListShare sendParams = {
        .sharedList = sendQueue, 
        .port = targetPort, 
        .ip_address = targetIP
    };
    ListShare receiveParams = {
        .sharedList = receiveQueue, 
        .port = listenPort
    };
    printf("Listening on port: %d\n", listenPort);

    //create threads for all these actions
    pthread_create(&threadProducer, NULL, ThreadHandler_producer, &sendParams);
    pthread_create(&threadSender, NULL, ThreadHandler_sender, &sendParams);
    pthread_create(&threadReceiver, NULL, ThreadHandler_receiver, &receiveParams);
    pthread_create(&threadConsumer, NULL, ThreadHandler_consumer, &receiveParams);
    //wait for all threads to finish
    pthread_join(threadProducer, NULL);
    pthread_join(threadSender, NULL);
    pthread_join(threadReceiver, NULL);
    pthread_join(threadConsumer, NULL);
}
// shutdown all threads
void ThreadHandler_shutdown() {
    pthread_cancel(threadProducer);
    pthread_cancel(threadSender);
    pthread_cancel(threadReceiver);
    pthread_cancel(threadConsumer);
}