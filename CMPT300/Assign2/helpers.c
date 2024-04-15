#include "helpers.h"
#include "list.h"
#include "socketHandler.h"
#include "threadHandler.h"
#include <stdlib.h>
#include <stdio.h>

void Helpers_freeItem(void* pItem){
    if(pItem != NULL){
        free(pItem);
    }
}

void Helpers_validateArgs(int argc, char* argv[]){
    if (argc != 4) {
        printf("Usage: %s [my port number] [remote machine name] [remote port number]\n", argv[0]);
        exit(1);
    }
}

void Helpers_getPortAndMachineName(int* myPort, char** remoteMachineName, int* remotePort, char* argv[]){
    *myPort = atoi(argv[1]);
    *remoteMachineName = argv[2];
    *remotePort = atoi(argv[3]);
}

void Helpers_getRemoteIp(char* remoteMachineName, char* remote_ip){
    SocketHandler_getIpFromHostname(remoteMachineName, remote_ip);
}

void Helpers_initListAndThreads(int myPort, int remotePort, char* remote_ip){
    List* inputList = List_create();
    List* outputList = List_create();

    ThreadHandler_init(myPort, remotePort, remote_ip, inputList, outputList);

    List_free(outputList, &Helpers_freeItem);
    List_free(inputList, &Helpers_freeItem);
}