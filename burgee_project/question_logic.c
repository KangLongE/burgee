#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"

double point = 0;
// 전역 변수로 점수 저장

int* correct_if(N1* c, int* un, int n) {
	// c: 문제 구조체 포인터
    // un: 사용자가 입력한 정답 배열
    // n: 문제 개수

    int* true_answer = (int*)malloc(sizeof(int) * n);
	// true_answer: 정답 여부를 저장할 배열 (1: 맞음, 0: 틀림)

    if (true_answer == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
    // 문제 개수만큼 반복
        
        if (un[i] == c[i].correct_answer) {
            
            true_answer[i] = 1;
            printf("%d\n", 1);  //맟히면 [1]
            fflush(stdout);
            point++;
        }
        else {
            true_answer[i] = 0;
            printf("%d\n", 0);  //못 맞히면 [0]
            fflush(stdout);
        }
        // 정답 비교 (정답이면 1, 틀리면 0 저장)

    }


    printf("%d\n", (int)point);   //    [맞힌 총 점수]
    fflush(stdout);
	printf("%.4f%%\n", (float)point / n * 100); //  [점수 백분율]
    fflush(stdout);
    // 점수 출력 (맞춘 문제 수, 총 문제 수, 백분율)

    point = (point / n) * 100;
    // 포인트 저장

    return true_answer;
}


N1* question_suffle(int n) {
// n: 문제 개수 (10 ~ 30)

    N1* q = (N1*)malloc(sizeof(N1) * n);
	// 문제 구조체 배열 동적 할당  [메모리 공간 아끼기 위해]


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            q[i].indices[j] = j;
        }
    }
	// 보기 배열 초기화

    srand((unsigned int)time(NULL));

    FILE* fp;
    fp = fopen("question.txt", "r");
    // 문제가 저장된 파일 열기

    if (fp == NULL) {
		perror("파일 열기 실패");
		exit(1);
    }

    int i = 0;
    int* number = (int*)malloc(sizeof(int) * n);
	// 랜덤 번호 저장 배열 동적 할당    [메모리 공간 아끼기 위해]

    while (i < n) {

        int random = rand() % 30; // 파일에 있는 총 문제 수 입력
        int nk = 1;

        for (int j = 0; j < i; j++) {
            if (number[j] == random) {
                nk = 0;
                break;
            }
        }
		// 중복 체크


        if (nk) {
            number[i] = random;
            i++;
        }
        // 중복되지 않는 랜덤 번호 생성
    }

    for (int i = 0; i < n; i++) {
        // 문제 수 만큼 출력 반복

        rewind(fp);
		// 파일 포인터를 처음으로 되돌림

        char line[MAX_INDEX];
        // 한 줄씩 읽기 위한 변수

        int target = number[i];
		// 랜덤으로 선택된 읽을 문제 번호

        int start_line = target * 8;
        // 문제 번호에 해당하는 줄 번호 계산
        // 해당 문제 시작 줄 (문제당 8줄)

        int curr_line = 0;
        // 현재 줄 번호
        int correct_idx = -1;
        // 정답 인덱스 번호

        // 질문, 보기, 정답 읽기
        while (fgets(line, sizeof(line), fp)) {
			// 한 줄씩 읽고 line에 저장

            line[strcspn(line, "\n")] = '\0';
			// 개행 문자 제거

            if (curr_line == start_line) strcpy(q[i].question[0], line);
            // line과 start_line이 같으면
            // 질문 읽기 1
            else if (curr_line == start_line + 1) strcpy(q[i].question[1], line);
			// line과 start_line + 1이 같으면    [두번째 줄]
            // 질문 읽기 2
            else if (curr_line >= start_line + 2 && curr_line < start_line + 7) {
				// line이 질문 두개를 읽고 정답읽기 전까지     [3포함 ~ 7포함 줄]
                // 보기 범위 2~6줄 읽기    [총 다섯 줄]
                strcpy(q[i].options[curr_line - start_line - 2], line);
            }
            else if (curr_line == start_line + 7) {
				// 질문, 보기 읽고 마지막 줄 읽기   [8번째 줄]
                correct_idx = atoi(line) - 1;
                // 정답 인덱스 읽기
                break;
            }
            curr_line++;
			// 현재 줄 번호 증가
        }

        shuffle(q[i].indices, 5);
        // 보기 섞기

        int new_correct = -1;
        // 새로운 정답 인덱스

        for (int k = 0; k < 5; k++) {
            if (q[i].indices[k] == correct_idx) {
                // 섞인 보기에서 정답 인덱스 찾기
                new_correct = k + 1;
                q[i].correct_answer = new_correct;
                // 해당 문제에 정답 저장 (사용자 보기 1~5로 번호 매기기)
                break;
            }
        }

    }

    free(number);
	// 동적 할당된 번호 배열 해제

    fclose(fp);
	// 파일 닫기

    return q;
	// 섞인 문제 구조체 배열 반환 [carry 구조체 포인터로 받음]

}


void shuffle(int* arr, int size) {
    //보기 섞음
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // 0부터 i까지 중 랜덤 인덱스
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}