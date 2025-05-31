#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include "utils.h"
//#include "input.h"
//#include "calendar.h" // ��� ����� ���� �ݵ�� ����

// �޷� ���� ��� ����
#define MONTHS_PER_YEAR 12
#define LEAP_DIV4 4
#define LEAP_DIV100 100
#define LEAP_DIV400 400

// �� ������ ���� enum ���� (1��~12��)
typedef enum {
    JANUARY = 1,  // 1��
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
} Month;

// �޷� ������ �����ϴ� ����ü
typedef struct {
    int year;                                 // ����
    Month month;                              // ��
    int daysInMonth[MONTHS_PER_YEAR + 1];     // �� ���� �ϼ� ([1]~[12] ���, [0]�� ������� ����)
} Calendar;

// �Լ� �����
void initCalendar(Calendar* cal);                         // �޷� �ʱ�ȭ
int isLeapYear(int year);                                 // ���� �Ǻ�
int getFirstDayOfTheYear(int year);                       // �ش� ���� 1�� 1���� ���� ���
void adjustLeapYear(Calendar* cal);                       // ������ �� 2�� �ϼ� ����
void printCalendar(const Calendar* cal);                  // �޷� ���
void prevMonth(Calendar* cal);                            // ���� �޷� �̵�
void nextMonth(Calendar* cal);                            // ���� �޷� �̵�
int handleCommand(char cmd, Calendar* cal);               // ��� ó��
char getCommandFromUser();                                // ��� �Է� �ޱ�
int getValidYearMonth(int* outYear, Month* outMonth);     // ����/�� �Է� �� ��ȿ�� �˻�
void printExitMessage();                                  // ���� �޽��� ���

int main() {
    Calendar cal;

    // �޷� �ʱ�ȭ(����/�� �Է� �� ���� �ϼ� ����)
    initCalendar(&cal);

    // ���� ����: �޷� ��� �� ��� ó�� �ݺ�
    while (1) {
        printCalendar(&cal); // �޷� ���
        if (!handleCommand(getCommandFromUser(), &cal)) { // ��� ó��
            break; // 'q' ��� �� ���� ����
        }
        adjustLeapYear(&cal); // ����/�� ���� �� ���� �ݿ�
    }

    return 0;
}

// �޷� ����ü�� �ʱ�ȭ�ϰ�, ����/���� �Է¹޾� ���� �ϼ� ����
void initCalendar(Calendar* cal) {
    getValidYearMonth(&cal->year, &cal->month); // ����/�� �Է� �� ��ȿ�� �˻�
    int defaultDays[MONTHS_PER_YEAR + 1] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    for (Month m = JANUARY; m <= DECEMBER; m++) {
        cal->daysInMonth[m] = defaultDays[m];
    }
    adjustLeapYear(cal); // ���� �ݿ�
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
    }
    else {
        cal->daysInMonth[FEBRUARY] = 28;
    }
}

// �޷� ��� �Լ�
void printCalendar(const Calendar* cal) {
    int weekDays = getFirstDayOfTheYear(cal->year); // 1�� 1���� ����
    int totalDays = cal->daysInMonth[cal->month];   // �ش� ���� �ϼ�

    // �ش� ���� 1���� ���� �������� ���
    for (Month m = JANUARY; m < cal->month; m++) {
        weekDays = (weekDays + cal->daysInMonth[m]) % 7;
    }
    printf("\n");
    printf("    %d�� %d��\n", cal->year, cal->month);
    printf("Su Mo Tu We Th Fr Sa\n");

    // 1�� ������ ���� ���
    for (int i = 0; i < weekDays; i++) {
        printf("   ");
    }

    // ��¥ ���
    for (int day = 1; day <= totalDays; day++) {
        printf("%2d", day);
        if ((weekDays + day) % 7 == 0) {
            printf("\n");
        }
        else {
            printf(" ");
        }
    }
    printf("\n");
}

// ���� �޷� �̵�
void prevMonth(Calendar* cal) {
    if (cal->month > JANUARY) {
        cal->month--;
    }
    else {
        cal->year--;
        cal->month = DECEMBER;
    }
}

// ���� �޷� �̵�
void nextMonth(Calendar* cal) {
    if (cal->month < DECEMBER) {
        cal->month++;
    }
    else {
        cal->year++;
        cal->month = JANUARY;
    }
}

// ��ɾ ���� �޷� ���¸� �����ϰų� ����
int handleCommand(char cmd, Calendar* cal) {
    if (cmd == 'p') {
        prevMonth(cal); // ���� ��
    }
    else if (cmd == 'n') {
        nextMonth(cal); // ���� ��
    }
    else if (cmd == 'c') {
        getValidYearMonth(&cal->year, &cal->month); // ����/�� ����
    }
    else if (cmd == 'q') {
        printExitMessage(); // ���� �޽��� ���
        return 0; // ����
    }
    else {
        printf("\n");
        printf("�߸��� ����Դϴ�. �ٽ� �����ϼ���.\n");
    }

    return 1;   // ���
}

// ��ɾ� �Է� �� ��ȿ�� �˻�
char getCommandFromUser() {
    char cmd;

    printf("\n");
    printf("\n");
    printf("[p]������ [n]������ [c]����/�� ���� [q]���� : ");
    scanf("%c", &cmd);

    // �Է� ���� ����
    while (getchar() != '\n');

    return cmd;
}

// ������ ���� �Է¹ް� ��ȿ�� �˻�
int getValidYearMonth(int* outYear, Month* outMonth) {
    int year, month;
    int result;
    while (1) {
        printf("������ ���� �Է��ϼ��� (��: 2023 5): ");
        result = scanf("%d %d", &year, &month);

        // �Է� ���� ����
        while (getchar() != '\n');

        // �Է°��� ��ȿ�ϸ� ��ȯ
        if (result == 2 && month >= 1 && month <= 12) {
            *outYear = year;
            *outMonth = month;
            return 1;
        } else {
            printf("�Է��� �ùٸ��� �ʽ��ϴ�. ������ ��(1~12)�� ��Ȯ�� �Է��ϼ���.\n");
        }
    }
}

// ���� �޽��� ���
void printExitMessage() {
    printf("\n");
    printf("\n");
    printf("���α׷��� �����մϴ�.");
    printf("\n");
    printf("\n");
}