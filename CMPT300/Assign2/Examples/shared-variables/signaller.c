#include "signaller.h"
#include "general.h"
#include "printer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>  
#include <unistd.h> 

static pthread_t threadSignaller;

static const char* MESSAGE = "Hello, World in Sync!";

void* signallerThread(void* unused){
    for(const char* msg = MESSAGE; *msg != '\0'; msg++){
        sleep_msec(100);
        
        // signal other thread
        Printer_signalNextChar();
    }

    return NULL;
}

void Signaller_init(){
    pthread_create(&threadSignaller, NULL, signallerThread, NULL);
}

void Signaller_waitForShutdown(){
    pthread_join(threadSignaller, NULL);
}