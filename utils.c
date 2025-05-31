#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include <stdio.h>

// 정수 입력 함수 (숫자가 아니면 -1 반환)
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

// 종료 메시지 출력
void printExitMessage() {
    printf("\n");
    printf("\n");
    printf("프로그램을 종료합니다.");
    printf("\n");
    printf("\n");
}