#ifndef COMMAND_H
#define COMMAND_H

#include "calendar.h"

int handleCommand(char cmd, Calendar* cal);                 // 명령 처리
void printExitMessage();                                    // 종료 메시지 출력

#endif