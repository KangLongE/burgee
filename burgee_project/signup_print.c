
#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"
#include "sign_log.h"
#include "note.h"

//signup 파일
//회원 가입 하려면 이 파일을 실행

int main(int argc, char* argv[]) {
// argc: 인자 개수, argv: 인자 배열
    // 인자개수 1은 값을 보내지 않음
	// 인자개수 2는 값을 한개 보낸거임

    char yn;
	// yn: 회원가입 여부 확인 변수

    int i = 0;

    char buffer[MAX_INDEX];
	// buffer: 파일에서 읽은 데이터를 저장할 버퍼

    FILE* fp;
    fp = fopen("UserData.txt", "r");
	// UserData.txt 파일 열기
    
    if (fp == NULL) {
        printf("파일 열기 실패\n");
        exit(1);
	}

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
	// 파일 크기 확인


    if (argc == 1) {
//인자개수가 1   [값을 보내지 않음]
// 값을 보내지 않으면 로그인 상태 확인

        if (fp == NULL || size == 0) {
	    // 파일이 비어있거나 존재하지 않으면

            printf("%d", 0);    //로그인이 가능하지 않다는 신호를 보냄    [0]
			fflush(stdout);
            printf("로그인이 되어있지 않습니다.\n회원가입 하시겠습니까? : Y / N\n: ");
            fflush(stdout);

        }
        else {
        // 파일이 존재하고 비어있지 않으면

			printf("%d", 1);    //로그인 가능 신호 보냄    [1]
            fflush(stdout);
        }
    }


    if (argc == 2) {
	// 인자 개수가 2이면 회원기압 및 로그인 여부 확인
	//회원가입 하겠다   [1]
	// 프로그램 종료    [0]

        if (argv[1]) {
        //회원가입 하겠다   [1]

            signup();
            // signup.c     [sign_log.h]
            // 회원가입 함수 호출

        }
        else {
        //프로그렘 종료   [0]

            printf("%d", 1); //종료 신호를 보냄    [1]
            fflush(stdout);
            printf("프로그렘을 종료합니다.\n");
        }
    }

}
