

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024

#include <stdio.h>
#include <string.h>
#include "sign_log.h"

// 로그인 기능 파일

int success = 0;
// 로그인 성공 여부를 나타내는 전역 변수



void login(char * name, int * password){
//login_print.c 로부터 호출  [sign_log.h]

//name[MAX_INDEX]
//password[4]

    struct User user;
    //입력 받은 값을 저장할 구조체  [sign_log.h]

	strcpy(user.name, name);
    //입력 받은 네임 값 넣기

    for (int i = 0; i < 4; i++) {
        user.password[i] = password[i];
	}
    // 입력 받은 패스워드 값 넣기


    struct User readuser;
    //파일에서 읽을 값을 저장할 구조체    [sign_log.h]

    FILE* fp = fopen("UserData.txt", "r");
	// 파일 열기

    if (fp == NULL) {
        printf("파일 열기 실패\n");
        exit(1);
    }

    
    // 파일에서 데이터 읽기

    char nameLine[MAX_INDEX];
    //파일 이름 읽을 줄
    char passwordLine[MAX_INDEX];
    //파일 비밀번호 읽을 줄 

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
            success = 1;
        }
        else {
            success = -2;
        }
    }
    else {
        success = -1;
    }
    // 파일에 저장된 사용자 이름과 비밀번호와 비교하여 로그인 성공 여부 출력

    fclose(fp);
}