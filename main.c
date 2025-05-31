#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "input.h"
#include "calendar.h"
#include <stdio.h>


int main() {
    Calendar cal;

    // 달력 초기화(연도/월 입력 및 월별 일수 설정)
    initCalendar(&cal);

    // 메인 루프: 달력 출력 및 명령 처리 반복
    while (1) {
        printCalendar(&cal); // 달력 출력
        if (!handleCommand(getCommandFromUser(), &cal)) { // 명령 처리
            break; // 'q' 명령 시 루프 종료
        }
        adjustLeapYear(&cal); // 연도/월 변경 후 윤년 반영
    }

    return 0;
}
