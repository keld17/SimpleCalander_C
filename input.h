#ifndef INPUT_H
#define INPUT_H

#include "calendar.h"

int getValidYearMonth(int* outYear, Month* outMonth);       // 연도/월 입력 및 유효성 검사
char getCommandFromUser();                                  // 명령 입력 받기

#endif