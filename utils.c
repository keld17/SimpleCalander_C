#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include <stdio.h>

// ���� �Է� �Լ� (���ڰ� �ƴϸ� -1 ��ȯ)
int getIntInput() {
    int input;
    char buffer[100];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (sscanf(buffer, "%d", &input) != 1) {
            input = -1;
        }
    } else {
        input = -1;
    }

    return input;
}

// ���� �޽��� ���
void printExitMessage() {
    printf("\n");
    printf("\n");
    printf("���α׷��� �����մϴ�.");
    printf("\n");
    printf("\n");
}