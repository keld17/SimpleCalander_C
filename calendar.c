#define _CRT_SECURE_NO_WARNINGS
#include "calendar.h"
#include <stdio.h>

// 달력 구조체를 초기화하고, 연도/월을 입력받아 월별 일수 설정
void initCalendar(Calendar* cal) {
    getValidYearMonth(&cal->year, &cal->month);
    int defaultDays[MONTHS_PER_YEAR + 1] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    for (Month m = JANUARY; m <= DECEMBER; m++) {
        cal->daysInMonth[m] = defaultDays[m];
    }
    adjustLeapYear(cal);
}

// 윤년 판별 함수
int isLeapYear(int year) {
    return ((year % LEAP_DIV4 == 0 && year % LEAP_DIV100 != 0) || (year % LEAP_DIV400 == 0));
}

// 해당 연도 1월 1일의 요일(일요일=0) 계산
int getFirstDayOfTheYear(int year) {
    int day = (year * 365 + ((year - 1) / LEAP_DIV4) - ((year - 1) / LEAP_DIV100) + ((year - 1) / LEAP_DIV400)) % 7;
    return day;
}

// 윤년일 경우 2월의 일수를 29일로, 아니면 28일로 조정
void adjustLeapYear(Calendar* cal) {
    if (isLeapYear(cal->year)) {
        cal->daysInMonth[FEBRUARY] = 29;
    } else {
        cal->daysInMonth[FEBRUARY] = 28;
    }
}

// 달력 출력 함수
void printCalendar(const Calendar* cal) {
    int weekDays = getFirstDayOfTheYear(cal->year);
    int totalDays = cal->daysInMonth[cal->month];

    for (Month m = JANUARY; m < cal->month; m++) {
        weekDays = (weekDays + cal->daysInMonth[m]) % 7;
    }
    printf("\n");
    printf("    %d년 %d월\n", cal->year, cal->month);
    printf("Su Mo Tu We Th Fr Sa\n");

    for (int i = 0; i < weekDays; i++) {
        printf("   ");
    }

    for (int day = 1; day <= totalDays; day++) {
        printf("%2d", day);
        if ((weekDays + day) % 7 == 0) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

// 이전 달로 이동
void prevMonth(Calendar* cal) {
    if (cal->month > JANUARY) {
        cal->month--;
    } else {
        cal->year--;
        cal->month = DECEMBER;
    }
}

// 다음 달로 이동
void nextMonth(Calendar* cal) {
    if (cal->month < DECEMBER) {
        cal->month++;
    } else {
        cal->year++;
        cal->month = JANUARY;
    }
}

// 명령어에 따라 달력 상태를 변경하거나 종료
int handleCommand(char cmd, Calendar* cal) {
    if (cmd == 'p') {
        prevMonth(cal);
    } else if (cmd == 'n') {
        nextMonth(cal);
    } else if (cmd == 'c') {
        getValidYearMonth(&cal->year, &cal->month);
    } else if (cmd == 'q') {
        printExitMessage();
        return 0;
    } else {
        printf("\n");
        printf("잘못된 명령입니다. 다시 선택하세요.\n");
    }
    return 1;
}