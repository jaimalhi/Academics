#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>        
#include <sys/socket.h>
#include <netdb.h>

//* Address Structure
#define MAX_LEN 256
#define PORT 22110

int main() {
    // Demp Intro
    printf("UDP Server listening on port %d\n", PORT);
    printf("Connect using: \n");
    printf("    netcat -u 127.0.0.1 %d\n", PORT);

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin)); // clear memory for sin
    sin.sin_family = AF_INET; // connection may be from network
    sin.sin_addr.s_addr = htonl(INADDR_ANY); // Host to Network Long
    sin.sin_port = htons(PORT); // Host to Network Short

    //* Create and bind to socket
    int socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);
    // bind socket to specified port & open socket
    bind(socketDescriptor, (struct sockaddr*)&sin, sizeof(sin));

    while(1){
        //* Receive Data (blocking call)
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char messageRx[MAX_LEN]; // buffer Rx

        // clients data written into messageRx string
        // sinRemote is output parameter
        // sinLen is input/output parameter (passed as pointers)
        int bytesRx = recvfrom(socketDescriptor, messageRx, MAX_LEN, 0, (struct sockaddr*) &sinRemote, &sin_len);

        // make it null terminated (so string functions work)
        int terminatedx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        messageRx[terminatedx] = 0;
        
        long remotePort = ntohs(sinRemote.sin_port);
        printf("(Port %ld) %s\n", remotePort, messageRx);
        // printf("Message received (%d bytes): %s\n", bytesRx, messageRx);

        // extract the value form message:
        // (process the message any way yor application requires)
        int incMe = atoi(messageRx); // atoi = ascii to integer

        //* Create the reply message (watch for buffer overflow)
        char messageTx[MAX_LEN];
        sprintf(messageTx, "Math: %d + 1 = %d\n", incMe, incMe + 1);

        //* Send Reply
        sin_len = sizeof(sinRemote);
        // sinRemote is the address of the client
        sendto(socketDescriptor, messageTx, strlen(messageTx), 0, (struct sockaddr*) &sinRemote, sin_len);
    }

    //* Close Socket
    close(socketDescriptor);

    return 0;
}
