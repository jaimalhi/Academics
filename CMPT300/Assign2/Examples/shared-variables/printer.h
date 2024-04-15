#ifndef _PRINTER_H_
#define _PRINTER_H_

#include <pthread.h>

// void Printer_init(pthread_mutex_t *ptrSyncOkToPrintMutex, pthread_cond_t *ptrSyncOkToPrintCondVar);

void Printer_init();

void Printer_signalNextChar();

void Printer_waitForShutdown();

#endif