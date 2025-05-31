#ifndef COMMAND_H
#define COMMAND_H

#include "calendar.h"

int handleCommand(char cmd, int* year, Month* month);
void printExitMessage();

#endif