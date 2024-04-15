#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "main.h"
#include "pcb.h"
#include "semaphore.h"

void menu_startUp();

char menu_response();

void menu_handleUserInput(char response, bool *runState);

#endif 