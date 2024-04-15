#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "reciever.h"

int main(int argCount, char *argv[]) {  
    printf("***** STARTING PROGRAM *****\n");

    //* if using shared mutex
    // pthread_mutex_t sharedMutex = PTHREAD_MUTEX_INITIALIZER;
    // Receiver_init("Sire! A message!", &sharedMutex);

    Receiver_init("Sire! A message!"); // startup modules

    // wait for user input
    printf("Enter something to kill the receive thread\n");
    char x;
    scanf("%c", &x);
     
    Receiver_shutdown(); // shutdown modules
    printf("***** DONE PROGRAM *****\n");

    return 0;
}
