#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H

#include "list.h"

// Struct to share lists between threads
typedef struct ThreadInfo_s ListShare;
struct ThreadInfo_s{
    List* sharedList;
    const char* ip_address;
    int port;
};

void ThreadHandler_init(int listenPort, int targetPort, char* targetIP, List* sendQueue, List* receiveQueue);

void ThreadHandler_shutdown();

#endif