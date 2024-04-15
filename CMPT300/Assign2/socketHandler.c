#include "socketHandler.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_MESSAGE_LEN 1024

// converts hostname to an ip, result stored in ip
int SocketHandler_getIpFromHostname(const char *hostname, char *ip){
    // Check if ip is NULL
    if (ip == NULL) {
        perror("NULL IP address pointer");
        return -1;
    }

    // hints specifys what kind of socket addresses we want
    // res and p are pointers to addrinfo that are used to go 
    // through list of addresses given by getaddrinfo. 
    // status holds the return value of getaddrinfo. 
    // ipString will hold the IP address in string format
    struct addrinfo hints, *res, *p;
    int status;
    char ipString[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; 
    hints.ai_socktype = SOCK_DGRAM; 

    // getaddrinfo returns 0 on success
    if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return -1;
    }

    // loop through the results and connect to the first one
    for(p = res;p != NULL; p = p->ai_next) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, &(ipv4->sin_addr), ipString, sizeof ipString);
    }

    strncpy(ip, ipString, INET_ADDRSTRLEN);
    freeaddrinfo(res); // free the linked list

    return 0;
}


// sends messages to specified ip and port
int SocketHandler_socketSend(const char* destinationIP, int destinationPort, const char* message){
    int sendSocket;
    struct sockaddr_in serverAddress;
    
    // Create socket
    const int PROTOCOL = 0; // avoid magic numbers
    sendSocket = socket(AF_INET, SOCK_DGRAM, PROTOCOL);
    if (sendSocket < 0){
        perror("Error creating socket");
        return -1;
    }

    // socket setup
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(destinationPort); 
    serverAddress.sin_addr.s_addr = inet_addr(destinationIP);

    // Check if inet_addr failed
    if (serverAddress.sin_addr.s_addr == INADDR_NONE) {
        perror("Error with destination IP address");
        close(sendSocket);
        return -1;
    }

    // Send data
    int sendMessageStatus = sendto(sendSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Close the socket in all cases
    int closeSocketStatus = close(sendSocket);
    if (closeSocketStatus < 0){
        perror("Error closing socket");
        return -1;
    }

    // Check if sendto failed
    if (sendMessageStatus < 0){
        perror("Error sending message");
        return -1;
    }

    return 0;
}

// opens receive socket on host port and returns the message received
char* SocketHandler_socketReceive(int hostPort){
    struct sockaddr_in socketAddress; 
    memset(&socketAddress, 0, sizeof(socketAddress));

    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(hostPort); 
    socketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0) {
        perror("Error creating socket");
        return NULL;
    }

    if (bind(socketDescriptor, (struct sockaddr*) &socketAddress, sizeof(socketAddress)) < 0) {
        perror("Error binding socket");
        close(socketDescriptor);
        return NULL;
    }

    struct sockaddr_in sinRemote;
    unsigned int sin_len = sizeof(sinRemote);
    char messageRx[MAX_MESSAGE_LEN]; 

    int bytesRx = recvfrom(socketDescriptor, messageRx, MAX_MESSAGE_LEN, 0, (struct sockaddr*) &sinRemote, &sin_len);
    if (bytesRx < 0) {
        perror("Error receiving message");
        return NULL;
    }

    close(socketDescriptor); // socket closed once message is received

    // make it null terminated (so string functions work)
    int terminateIdx = (bytesRx < MAX_MESSAGE_LEN) ? bytesRx : MAX_MESSAGE_LEN - 1;
    messageRx[terminateIdx] = 0;

    // allocate memory for return message to return it
    char* returnMsg = malloc(terminateIdx + 1);
    if (returnMsg == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    // copy received message to memory
    strncpy(returnMsg, messageRx, terminateIdx + 1); 
    
    return returnMsg;
}
