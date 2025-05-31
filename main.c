#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "input.h"
#include "calendar.h"
#include <stdio.h>


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
