#define _CRT_SECURE_NO_WARNINGS
#include "calendar.h"
#include <stdio.h>

// �޷� ����ü�� �ʱ�ȭ�ϰ�, ����/���� �Է¹޾� ���� �ϼ� ����
void initCalendar(Calendar* cal) {
    getValidYearMonth(&cal->year, &cal->month);
    int defaultDays[MONTHS_PER_YEAR + 1] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    for (Month m = JANUARY; m <= DECEMBER; m++) {
        cal->daysInMonth[m] = defaultDays[m];
    }
    adjustLeapYear(cal);
}

// ���� �Ǻ� �Լ�
int isLeapYear(int year) {
    return ((year % LEAP_DIV4 == 0 && year % LEAP_DIV100 != 0) || (year % LEAP_DIV400 == 0));
}

// �ش� ���� 1�� 1���� ����(�Ͽ���=0) ���
int getFirstDayOfTheYear(int year) {
    int day = (year * 365 + ((year - 1) / LEAP_DIV4) - ((year - 1) / LEAP_DIV100) + ((year - 1) / LEAP_DIV400)) % 7;
    return day;
}

// ������ ��� 2���� �ϼ��� 29�Ϸ�, �ƴϸ� 28�Ϸ� ����
void adjustLeapYear(Calendar* cal) {
    if (isLeapYear(cal->year)) {
        cal->daysInMonth[FEBRUARY] = 29;
    } else {
        cal->daysInMonth[FEBRUARY] = 28;
    }
}

// �޷� ��� �Լ�
void printCalendar(const Calendar* cal) {
    int weekDays = getFirstDayOfTheYear(cal->year);
    int totalDays = cal->daysInMonth[cal->month];

    for (Month m = JANUARY; m < cal->month; m++) {
        weekDays = (weekDays + cal->daysInMonth[m]) % 7;
    }
    printf("\n");
    printf("    %d�� %d��\n", cal->year, cal->month);
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

// ���� �޷� �̵�
void prevMonth(Calendar* cal) {
    if (cal->month > JANUARY) {
        cal->month--;
    } else {
        cal->year--;
        cal->month = DECEMBER;
    }
}

// ���� �޷� �̵�
void nextMonth(Calendar* cal) {
    if (cal->month < DECEMBER) {
        cal->month++;
    } else {
        cal->year++;
        cal->month = JANUARY;
    }
}

// ��ɾ ���� �޷� ���¸� �����ϰų� ����
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
        printf("�߸��� ����Դϴ�. �ٽ� �����ϼ���.\n");
    }
    return 1;
}