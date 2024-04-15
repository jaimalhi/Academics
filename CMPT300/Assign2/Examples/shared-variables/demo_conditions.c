#include "general.h"
#include "signaller.h"
#include "printer.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>  
#include <stdbool.h>
#include <unistd.h> 
#include <netdb.h>

// static const char* MESSAGE = "Hello, World in Sync!";

// return true if it computes the average OK
// average written into pAvgOut
static bool getAverage(double *ptrData, int size, double *pAvgOut){
    if(size <= 0){
        return false;
    }

    double sum = 0;
    for(int i = 0; i < size; i++){
        sum += *(ptrData + i);
    }
    // store value into output parameter
    *pAvgOut = sum / size;
    return true;
}

int main(int argc, char *argv[]){
    printf("\n===== START =====\n");

    //* IO/Pointer Parameters Demo
    double data[] = {1.0, 2.0};
    double avg = 0;
    if(getAverage(data, 2, &avg)){
        printf("Average: %f\n", avg);
    } else {
        printf("Error: invalid data\n");
    }

    //* Condition Variable Demo
    // Initialize
    Printer_init();
    Signaller_init();

    // Cleanup
    Printer_waitForShutdown();
    Signaller_waitForShutdown();

    printf("\n===== DONE =====\n");
    return 0;
}

/*
* IMPORTANT INFO & NOTES
- Signals sent with no listener are lost
- we have encapsulated the condition variable and mutex in the printer module
*/