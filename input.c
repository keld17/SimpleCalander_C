#define _CRT_SECURE_NO_WARNINGS
#include "input.h"
#include <stdio.h>

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

        if (result == 2 && month >= 1 && month <= 12) {
            *outYear = year;
            *outMonth = month;
            return 1;
        } else {
            printf("�Է��� �ùٸ��� �ʽ��ϴ�. ������ ��(1~12)�� ��Ȯ�� �Է��ϼ���.\n");
        }
    }
}