
#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int success = 0;

typedef struct User {
	char name[MAX_INDEX];
	int password[4];
} User;

int signup(char* name, int* password);
int login(char* name, int* password);


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
			perror("로그인 성공!\n");
		}
		else if (success == -1) {
			//로그인 실패 이름 틀림	[-1]
			printf("E:%d\n", success);	//신호 보냄
			fflush(stdout);
			perror("이름이 일치하지 않습니다.\n");
		}
		else if (success == -2) {
			//로그인 실패 비밀번호 틀림	[-2]
			printf("E:%d\n", success);	//신호 보냄
			fflush(stdout);
			perror("비밀번호가 일치 하지 않습니다.\n");

		}
	}
	else {
		printf("E:%d\n", 0);	//중단 오류 신호	[0]
		fflush(stdout);
		perror("값이 없습니다.\n");
		exit(1);
	}
}


int login(char* name, int* password) {
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
		perror("파일 열기 실패\n");
		exit(1);
	}


	// 파일에서 데이터 읽기

	char nameLine[MAX_INDEX];
	//파일 이름 읽을 줄
	char passwordLine[MAX_INDEX];
	//파일 비밀번호 읽을 줄 

	fgets(nameLine, sizeof(nameLine), fp); // name 줄 읽기
	fgets(passwordLine, sizeof(passwordLine), fp); // password 줄 읽기

	sscanf(nameLine, "name: %1024[^\n]", readuser.name); // 파일에서 이름 추출
	sscanf(passwordLine, "password: %d-%d-%d-%d",
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
			return 1;
		}
		else {
			return -2;
		}
	}
	else {
		return -1;
	}
	// 파일에 저장된 사용자 이름과 비밀번호와 비교하여 로그인 성공 여부 출력

	fclose(fp);
}