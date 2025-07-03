

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "sign_log.h"


int signup(char * name, int * password)
{

    FILE* fp;
    fp = fopen("UserData.txt", "w, ccs=UTF-8");
    // UserData.txt 파일 열기

    if (fp == NULL) {
        perror("파일 열기 실패\n");
        return 0;
    }

    // UserData.txt 파일에 이름 입력
    fprintf(fp, "name: %s", name);

    fprintf(fp, "password: ");
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d", password[i]);
        if (i < 3) {
            fprintf(fp, "-");
        }
    }
    fprintf(fp, "\n");
    // UserData.txt 파일에 비밀번호 입력



    fclose(fp);

    printf("파일에 저장 완료");
    return 1;
}
