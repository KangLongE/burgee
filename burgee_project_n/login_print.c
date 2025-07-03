
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"
#include "sign_log.h"
#include "note.h"

//login 파일
//로그인 하려면 이 파일 호출 하면 됨


void main(int argc, char**argv) {
//자바 스크립트에서 로그인 가능 신호를 판단하고
//login_print.c 실행

//argv[1]은 이름
//argv[2]포함 부터 argv[5]포함 은 비 밀 번 호

	int success = 0;
	//로그인 성공 여부를 비교함

	User u2;
	// 유저 데이터	[sign_log.h]
	// name[MAX_INDEX]
	// password[4]

	if (argc > 1) {
		//값을 보내야 실행

		strcpy(u2.name, argv[1]);
		//  이름 저장
		for (int i = 0; i < 4; i++) {

			char* endptr;
			long val = strtol(argv[2 + i], &endptr, 10);
			//10진법의 형식으로 endptr에 변환된 값을 넣음
			//변환이 안 되면 0을 반환

			if (*endptr != '\0' || val < 0 || val > 9) {
				printf("E:%d\n", 0);	//중단 신호		[0]
				fflush(stdout);
				printf("EC:%d\n", val);		//중단의 원인 출력
				fflush(stdout);
				exit(1);
			}
			else {
				u2.password[i] = val;
				//비밀번호 저장
			}

		}

		success = login(u2.name, u2.password);
		// 로그인 함수 호출		[login.c] [sign_log.h]

		if (success == 1) {
			// 로그인 성공	[1]
			printf("E:%d\n", success);	//신호 보냄
			fflush(stdout);
			printf("로그인 성공!\n");
		}
		else if (success == -1) {
			//로그인 실패 이름 틀림	[-1]
			printf("E:%d\n", success);	//신호 보냄
			fflush(stdout);
			printf("이름이 일치하지 않습니다.\n");
		}
		else if (success == -2) {
			//로그인 실패 비밀번호 틀림	[-2]
			printf("E:%d\n", success);	//신호 보냄
			fflush(stdout);
			printf("비밀번호가 일치 하지 않습니다.\n");

		}
	}
	else {
		printf("E:%d\n", 0);	//중단 오류 신호	[0]
		fflush(stdout);
		printf("값이 없습니다.\n");
		exit(1);
	}
}