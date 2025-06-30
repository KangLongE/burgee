
#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"
#include "sign_log.h"
#include "note.h"

//login 파일
//로그인 하려면 이 파일 호출 하면 됨


void main(int argc, char* argv[]) {
//자바 스크립트에서 로그인 가능 신호를 판단하고
//login_print.c 실행

//argv[1]은 이름
//argv[2]포함 부터 argv[5]포함 은 비 밀 번 호


	User u;
	// 유저 데이터	[sign_log.h]
	// name[MAX_INDEX]
	// password[4]

	if (argc > 1) {
		//값을 보내야 실행

		strcpy(u.name, argv[1]);
		//  이름 저장
		for (int i = 0; i < 4; i++) {
			u.password[i] = atoi(argv[2 + i]);
			//패스워드 저장
			//2포함 부터 5포함 까지
			if (u.password[i] < 0 || u.password[i] > 9) {
				// 패스워드가 0~9 사이가 아니면 오류

				printf("%d", 0); //중단 오류 신호	[0]
				fflush(stdout);
				printf("0 ~ 9까지만 입력 가능합니다.");
				fflush(stdout);
				exit(1);
			}
		}

		login(u.name, u.password);
		// 로그인 함수 호출		[login.c] [sign_log.h]

		if (success == 1) {
			// 로그인 성공	[1]
			printf("%d", success);	//신호 보냄
			fflush(stdout);
			printf("로그인 성공!");
		}
		else if (success == -1) {
			//로그인 실패 이름 틀림	[-1]
			printf("%d", success);	//신호 보냄
			fflush(stdout);
			printf("이름이 일치하지 않습니다.");
		}
		else if (success == -2) {
			//로그인 실패 비밀번호 틀림	[-2]
			printf("%d", success);	//신호 보냄
			fflush(stdout);
			printf("비밀번호가 일치 하지 않습니다.");

		}
	}
	else {
		printf("%d", 0);	//중단 오류 신호	[0]
		fflush(stdout);
		printf("값이 없습니다.");
		exit(1);
	}
}