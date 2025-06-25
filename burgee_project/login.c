

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024

#include <stdio.h>
#include <string.h>
#include "sign_log.h"

int success = 0; // 로그인 성공 여부를 나타내는 전역 변수

void login(void){

    struct User user;
    struct User readuser;

    FILE* fp = fopen("UserData.txt", "r");

    if (fp == NULL) {
        printf("파일 열기 실패\n");
        exit(1);
    }

    printf("login\n\n");
    // 사용자 입력
    printf("이름을 입력하세요: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';
    // 사용자가 이름 입력

    printf("비밀번호를 4자리 숫자로 입력하세요 (각 숫자 입력 후 Enter): ");
    for (int i = 0; i < 4; i++) {
        scanf_s("%d", &user.password[i]);

        if (user.password[i] < 0 || user.password[i] > 9) {
            printf("잘못된 입력입니다. 0에서 9 사이의 숫자를 입력하세요.\n");
            i--;
        }
        // 사용자가 비밀번호 입력
    }


    // 파일에서 데이터 읽기
    char nameLine[MAX_INDEX];
    char passwordLine[MAX_INDEX];

    fgets(nameLine, sizeof(nameLine), fp); // name 줄 읽기
    fgets(passwordLine, sizeof(passwordLine), fp); // password 줄 읽기

    sscanf_s(nameLine, "name: %[^\n]", readuser.name, MAX_INDEX); // 파일에서 이름 추출
    sscanf_s(passwordLine, "password: %d-%d-%d-%d",
        &readuser.password[0], &readuser.password[1],
        &readuser.password[2], &readuser.password[3]);
    // 파일에서 비밀번호 추출

    // 비교
    int match = 0;
    if (strcmp(user.name, readuser.name) == 0) {
        match = 1;
        for (int i = 0; i < 4; i++) {
            if (user.password[i] != readuser.password[i]) {
                match = 0;
                break;
            }
        }

        if (match) {
            printf("로그인 성공!\n");
            success = 1;
        }
        else {
            printf("비밀번호가 일치하지 않습니다.\n");
            success = 0;
        }
    }
    else {
        printf("이름이 일치하지 않습니다.\n");
        success = 0;
    }
    // 파일에 저장된 사용자 이름과 비밀번호와 비교하여 로그인 성공 여부 출력

    fclose(fp);
}