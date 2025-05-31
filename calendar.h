#ifndef CALENDAR_H
#define CALENDAR_H

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


void initCalendar(Calendar* cal);                           // �޷� �ʱ�ȭ
int isLeapYear(int year);                                   // ���� �Ǻ�
int getFirstDayOfTheYear(int year);                         // �ش� ���� 1�� 1���� ���� ���
void adjustLeapYear(Calendar* cal);                         // ������ �� 2�� �ϼ� ����
void printCalendar(const Calendar* cal);                    // �޷� ���
void prevMonth(Calendar* cal);                              // ���� �޷� �̵�
void nextMonth(Calendar* cal);                              // ���� �޷� �̵�

#endif