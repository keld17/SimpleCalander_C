#ifndef CALENDAR_H
#define CALENDAR_H

#define MONTHS_PER_YEAR 12
#define LEAP_DIV4 4
#define LEAP_DIV100 100
#define LEAP_DIV400 400

typedef enum { JANUARY = 1, /* ... */ DECEMBER } Month;

typedef struct {
    int year;
    Month month;
    int daysInMonth[13];
} Calendar;

void initCalendar(Calendar* cal);
int isLeapYear(int year);
int getFirstDayOfTheYear(int year);
void adjustLeapYear(Calendar* cal);
void printCalendar(const Calendar* cal);
void prevMonth(int year, Month month, int* outYear, Month* outMonth);
void nextMonth(int year, Month month, int* outYear, Month* outMonth);

#endif