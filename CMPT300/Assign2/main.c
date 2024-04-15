#include "helpers.h"
#include <stdlib.h>

int main(int argc, char* argv[]){
    Helpers_validateArgs(argc, argv);

    int myPort;
    char* remoteMachineName;
    int remotePort;
    Helpers_getPortAndMachineName(&myPort, &remoteMachineName, &remotePort, argv);

    char remote_ip[100];
    Helpers_getRemoteIp(remoteMachineName, remote_ip);

    Helpers_initListAndThreads(myPort, remotePort, remote_ip);

    exit(0);
}

/* 
*Create sockets that can communicate with each other using the following arguments
========================================================================================
./main [my port number] [remote machine ip] [remote port number]
Example:
     User 1: ./s-talk 22110 127.0.0.1 22111
     User 2: ./s-talk 22111 127.0.0.1 22110
     (127.0.0.1 is the ip address of the local machine)
Once connected, the users should be able to send eachother messages
thorugh the terminal, and the messages should be printed to terminal
Example:  (once enter is pressed, the message is sent to other user)
     User 1: Hello, User 2
     User 2: Hello, User 1
- The remote machine ips, should be gotten using the getaddrinfo() function
- the message should be received using the recvfrom() function
- the message should be sent using the sendto() function
*/