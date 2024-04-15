#include <stdio.h>
#include <pthread.h>
#include <string.h>  
#include "general.h"

void* receiveThread(void* msgAsVoid){
    char* msg = msgAsVoid;
    for(unsigned int i = 0; i < strlen(msg); i++){
        printf("%c", msg[i]);
        fflush(stdout); // flush the output buffer to print each character immediately, otherwise it will wait for a newline or buffer to fill up
        sleep_msec(200);
    }

    return NULL;
}

int main(int argCount, char *argv[]) {  
    printf("***** DONE PROGRAM *****\n");

    // create thread 1
    pthread_t threadPID;
    pthread_create(
        &threadPID,      // PID (by pointer)
        NULL,            // attributes  
        receiveThread, // functions
        "This is the new arg\n" // attributes passed to the function (i.e. slowPrintThread parameters)
    );

    // create thread 2
    pthread_t threadPID2;
    pthread_create(&threadPID2, NULL, receiveThread, "Yo, thread 2");

    // wait for the threads to finish before exiting
    pthread_join(
        threadPID,  // PID (w/o pointer)
        NULL        // whatever is returned by function (i.e. slowPrintThread return value) is returned here
    ); 
    pthread_join(threadPID2, NULL); 
    
    return 0;
}
