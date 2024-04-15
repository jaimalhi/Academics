#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>  
#include <stdbool.h>


// return true if it computes the average OK
// average written into pAvgOut
static bool getAverage(double data[], int size, double *pAvgOut){
    if(size <= 0){
        return false;
    }

    double sum = 0;
    for(int i = 0; i < size; i++){
        sum += data[i];
    }
    // store value into output parameter
    *pAvgOut = sum / size;
    return true;
}

int main(int argc, char *argv[]){
    printf("\n===== START =====\n");

    double data[] = {1.0, 2.0};
    double avg = 0;

    // if we give invalid size, we get an error
    if(getAverage(data, 2, &avg)){
        printf("Average: %f\n", avg);
    } else {
        printf("Error: invalid data\n");
    }

    printf("\n===== DONE =====\n");
    return 0;
}
