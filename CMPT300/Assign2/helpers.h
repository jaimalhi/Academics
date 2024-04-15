#ifndef HELPERS_H
#define HELPERS_H

void Helpers_freeItem(void* pItem);

void Helpers_validateArgs(int argc, char* argv[]);

void Helpers_getPortAndMachineName(int* myPort, char** remoteMachineName, int* remotePort, char* argv[]);

void Helpers_getRemoteIp(char* remoteMachineName, char* remote_ip);

void Helpers_initListAndThreads(int myPort, int remotePort, char* remote_ip);

#endif