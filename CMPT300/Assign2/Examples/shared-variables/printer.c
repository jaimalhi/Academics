#include "printer.h"
#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>  
#include <unistd.h> 

static pthread_t threadPrinter;

// Syncronization
static pthread_cond_t s_syncOkToPrintCondVar = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t s_syncOkToPrintMutex = PTHREAD_MUTEX_INITIALIZER;

static const char* MESSAGE = "Hello, World in Sync!";

void* printerThread(void* unused){
    for(const char* msg = MESSAGE; *msg != '\0'; msg++){
        // wait until signalled
        pthread_mutex_lock(&s_syncOkToPrintMutex);
        {
            // pass in the mutex to guard against deadlock 
            pthread_cond_wait(&s_syncOkToPrintCondVar, &s_syncOkToPrintMutex);
        }
        pthread_mutex_unlock(&s_syncOkToPrintMutex);

        printf("%c", *msg);
        fflush(stdout);
    }

    return NULL;
}

void Printer_signalNextChar(){
    // signal other thread
    pthread_mutex_lock(&s_syncOkToPrintMutex);
    {
        pthread_cond_signal(&s_syncOkToPrintCondVar);
    }
    pthread_mutex_unlock(&s_syncOkToPrintMutex);
}

void Printer_init(){
    pthread_create(&threadPrinter, NULL, printerThread, NULL);
}

void Printer_waitForShutdown(){
    pthread_join(threadPrinter, NULL);

}