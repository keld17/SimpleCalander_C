#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include "utils.h"
//#include "input.h"
//#include "calendar.h" // 상수 사용을 위해 반드시 포함

// 달력 관련 상수 정의
#define MONTHS_PER_YEAR 12
#define LEAP_DIV4 4
#define LEAP_DIV100 100
#define LEAP_DIV400 400

// 월 정보를 위한 enum 정의 (1월~12월)
typedef enum {
    JANUARY = 1,  // 1월
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

// 달력 정보를 저장하는 구조체
typedef struct {
    int year;                                 // 연도
    Month month;                              // 월
    int daysInMonth[MONTHS_PER_YEAR + 1];     // 각 월의 일수 ([1]~[12] 사용, [0]은 사용하지 않음)
} Calendar;

// 함수 선언부
void initCalendar(Calendar* cal);                         // 달력 초기화
int isLeapYear(int year);                                 // 윤년 판별
int getFirstDayOfTheYear(int year);                       // 해당 연도 1월 1일의 요일 계산
void adjustLeapYear(Calendar* cal);                       // 윤년일 때 2월 일수 조정
void printCalendar(const Calendar* cal);                  // 달력 출력
void prevMonth(Calendar* cal);                            // 이전 달로 이동
void nextMonth(Calendar* cal);                            // 다음 달로 이동
int handleCommand(char cmd, Calendar* cal);               // 명령 처리
char getCommandFromUser();                                // 명령 입력 받기
int getValidYearMonth(int* outYear, Month* outMonth);     // 연도/월 입력 및 유효성 검사
void printExitMessage();                                  // 종료 메시지 출력

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

// 달력 구조체를 초기화하고, 연도/월을 입력받아 월별 일수 설정
void initCalendar(Calendar* cal) {
    getValidYearMonth(&cal->year, &cal->month); // 연도/월 입력 및 유효성 검사
    int defaultDays[MONTHS_PER_YEAR + 1] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    for (Month m = JANUARY; m <= DECEMBER; m++) {
        cal->daysInMonth[m] = defaultDays[m];
    }
    adjustLeapYear(cal); // 윤년 반영
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
    }
    else {
        cal->daysInMonth[FEBRUARY] = 28;
    }
}

// 달력 출력 함수
void printCalendar(const Calendar* cal) {
    int weekDays = getFirstDayOfTheYear(cal->year); // 1월 1일의 요일
    int totalDays = cal->daysInMonth[cal->month];   // 해당 월의 일수

    // 해당 월의 1일이 무슨 요일인지 계산
    for (Month m = JANUARY; m < cal->month; m++) {
        weekDays = (weekDays + cal->daysInMonth[m]) % 7;
    }
    printf("\n");
    printf("    %d년 %d월\n", cal->year, cal->month);
    printf("Su Mo Tu We Th Fr Sa\n");

    // 1일 전까지 공백 출력
    for (int i = 0; i < weekDays; i++) {
        printf("   ");
    }

    // 날짜 출력
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

// 이전 달로 이동
void prevMonth(Calendar* cal) {
    if (cal->month > JANUARY) {
        cal->month--;
    }
    else {
        cal->year--;
        cal->month = DECEMBER;
    }
}

// 다음 달로 이동
void nextMonth(Calendar* cal) {
    if (cal->month < DECEMBER) {
        cal->month++;
    }
    else {
        cal->year++;
        cal->month = JANUARY;
    }
}

// 명령어에 따라 달력 상태를 변경하거나 종료
int handleCommand(char cmd, Calendar* cal) {
    if (cmd == 'p') {
        prevMonth(cal); // 이전 달
    }
    else if (cmd == 'n') {
        nextMonth(cal); // 다음 달
    }
    else if (cmd == 'c') {
        getValidYearMonth(&cal->year, &cal->month); // 연도/월 변경
    }
    else if (cmd == 'q') {
        printExitMessage(); // 종료 메시지 출력
        return 0; // 종료
    }
    else {
        printf("\n");
        printf("잘못된 명령입니다. 다시 선택하세요.\n");
    }

    return 1;   // 계속
}

// 명령어 입력 및 유효성 검사
char getCommandFromUser() {
    char cmd;

    printf("\n");
    printf("\n");
    printf("[p]이전달 [n]다음달 [c]연도/월 변경 [q]종료 : ");
    scanf("%c", &cmd);

    // 입력 버퍼 비우기
    while (getchar() != '\n');

    return cmd;
}

// 연도와 월을 입력받고 유효성 검사
int getValidYearMonth(int* outYear, Month* outMonth) {
    int year, month;
    int result;
    while (1) {
        printf("연도와 월을 입력하세요 (예: 2023 5): ");
        result = scanf("%d %d", &year, &month);

        // 입력 버퍼 비우기
        while (getchar() != '\n');

        // 입력값이 유효하면 반환
        if (result == 2 && month >= 1 && month <= 12) {
            *outYear = year;
            *outMonth = month;
            return 1;
        } else {
            printf("입력이 올바르지 않습니다. 연도와 월(1~12)을 정확히 입력하세요.\n");
        }
    }
}

// 종료 메시지 출력
void printExitMessage() {
    printf("\n");
    printf("\n");
    printf("프로그램을 종료합니다.");
    printf("\n");
    printf("\n");
}