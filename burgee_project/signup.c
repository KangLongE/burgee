

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024

#include <stdio.h>
#include "sign_log.h"


void signup(void)
{
    struct User user;

    FILE* fp;
    fp = fopen("UserData.txt", "w");
    // UserData.txt 파일 열기

    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return 1;
    }


    printf("이름을 입력하세요: ");

    fgets(user.name, sizeof(user.name), stdin);
    // UserData.txt 파일에 이름 입력
    fprintf(fp, "name: %s", user.name);

    printf("\n비밀번호를 4자리 숫자로 입력하세요: ");
    for (int i = 0; i < 4; i++) {

        scanf_s("%d", &user.password[i]);

        if (user.password[i] < 0 || user.password[i] > 9) {
            printf("잘못된 입력입니다. 0에서 9 사이의 숫자를 입력하세요.\n");
            i--;
        }
    }


    fprintf(fp, "password: ");
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d", user.password[i]);
        if (i < 3) {
            fprintf(fp, "-");
        }
    }
    fprintf(fp, "\n");
    // UserData.txt 파일에 비밀번호 입력



    fclose(fp);

    printf("파일에 저장 완료\n");
    return 0;
}
