#ifndef _RECIEVER_H
#define _RECIEVER_H

// Start background receive thread
void Receiver_init(char* rxMessage);
// void Receiver_init(char* rxMessage, pthread_mutex_t sharedMutex);

void Receiver_changeDynamicMessage(char* rxMessage);

// Shutdown background receive thread & cleanup
void Receiver_shutdown(void);

#endif