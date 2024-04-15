#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

// Returns 0 on success, and -1 on failure.
int SocketHandler_getIpFromHostname(const char *hostname , char *ip);

// Returns 0 on success, and -1 on failure.
int SocketHandler_socketSend(const char* ip_address, int port, const char* message);

// Returns 0 on success, and -1 on failure.
char* SocketHandler_socketReceive(int port);

#endif 