#define _CRT_SECURE_NO_WARNINGS
#include "input.h"
#include <stdio.h>

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

        if (result == 2 && month >= 1 && month <= 12) {
            *outYear = year;
            *outMonth = month;
            return 1;
        } else {
            printf("입력이 올바르지 않습니다. 연도와 월(1~12)을 정확히 입력하세요.\n");
        }
    }
}