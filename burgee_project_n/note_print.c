#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "note.h"

//note를 생성 및 확인 하려면 이 파일을 실행

int main(int argc, char**argv) {
//argc 인자 개수
//argv 인자

	nl* n1;
//	note_name[MAX_INDEX]
//	num
//	[note.h]

	int success = 0;
	// 성공 여부

	if (argc == 1) {
	//인자를 주지 않으면

		n1 = check_note();
		//check_note 실행 하여 리턴한 값을 n1으로 받음
		// 	[note.c]	[npte.h]

		for (int i = 0; i < n1[0].num; i++) {
			printf("N:%s\n", n1[i].note_name);
			fflush(stdout);
		}
		//디렉토리에 있는 파일 모두 출력

		free(n1);
	}
	else if (argc >= 2) {
	//파일 이름을 인자로 준 경우
		
		success = create_note(argv[2]);
		//create_note 실행
		//[note.c]	[npte.h]

		if (success) {
		//성공
			printf("E:%d\n", success);
			fflush(stdout);
			printf("N:%s\n", argv[2]);
			fflush(stdout);
		}
		else {
		//실패
			printf("E:%d\n", success);
			fflush(stdout);
		}
	}

}