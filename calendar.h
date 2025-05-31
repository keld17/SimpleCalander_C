#ifndef CALENDAR_H
#define CALENDAR_H

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


void initCalendar(Calendar* cal);                           // 달력 초기화
int isLeapYear(int year);                                   // 윤년 판별
int getFirstDayOfTheYear(int year);                         // 해당 연도 1월 1일의 요일 계산
void adjustLeapYear(Calendar* cal);                         // 윤년일 때 2월 일수 조정
void printCalendar(const Calendar* cal);                    // 달력 출력
void prevMonth(Calendar* cal);                              // 이전 달로 이동
void nextMonth(Calendar* cal);                              // 다음 달로 이동

#endif