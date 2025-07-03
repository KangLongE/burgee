#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"

//문제 출력 파일
//문제를 출력하려면 이 파일을 실행
//포인트 저장, 랭킹 등록, 결과 출력까지 한 번에 다함

void main(int argc, char * argv) {
// argc: 인자 개수, argv: 인자 배열

    int num = atoi(argv[1]);
	// 문제 개수 (1 ~ 3)

    N1* carry = NULL;
	// 문제를 담을 구조체 포인터

    int* user_answer = (int*)malloc(sizeof(int) * (num * 10));
	// 사용자가 입력한 정답을 저장할 배열

    carry = question_suffle(num * 10);
	// question_logic.c (question_data.h)
	// 문제를 섞고 carry구조체 포인터로 가리킴

    if (argc == 1) {
// 인자개수가 1이면 문제 출력 모드
        while (1) {
			// 인자 번호 1은 문제 개수 1 ~ 3

            if (num >= 1 && num <= 3) {

                for (int i = 0; i < num * 10; i++) {

                    printf("%s\n%s\n", carry[i].question[0], carry[i].question[1]);
					fflush(stdout);
                    // 문제 출력 (문제 번호, 문제 내용)

                    for (int k = 0; k < 5; k++) {
                        printf("%s\n", carry[i].options[carry[i].indices[k]]);
                        fflush(stdout);
                        // 섞인 보기 출력 (1~5로 번호 매기기)
                    }

                }

            }
        }
    }
    else {
// 인자개수가 여려개 이상이면 정답 확인 모드

        for (int i = 0; i < num * 10; i++) {
			user_answer[i] = atoi(argv[2 + i]);
            // 안자 번호 1은 문제 개수
			// 2번부터는 사용자가 입력한 정답
        }

        correct_if(carry, user_answer, num * 10);
		// question_logic.c     (question_data.h)
		// 정답 확인 함수 호출
        save_point(point);
		// point.c      (question_data.h)
		// 정답 확인 및 포인트 저장

        point = 0;
        // 문제 풀이 후 점수 초기화
        ranking();
		// ranking.c    (question_data.h)
		// 랭킹 업데이트
    }
}

        
    