#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//#include "question_read.h"

typedef struct question {

    char question[2][MAX_INDEX];
    // 문제 2줄

    char options[5][MAX_INDEX];
    // 보기 5줄

    int indices[5] = { 0, 1, 2, 3, 4 };
    // 섞인 보기 index

    int correct_answer;
    // 각 문제 정답


} N1;

void shuffle(int* arr, int size);
N1* question_print(int n);


int main(void)
{
    N1* carry = NULL;
    int choice = 1;




    int* user_answer = (int*)malloc(sizeof(int) * (choice * 10));

    carry = question_print(choice * 10);


    for (int i = 0; i < choice * 10; i++) {

        printf("\n%s%s", carry[i].question[0], carry[i].question[1]);
        // 문제 출력 (문제 번호, 문제 내용)

        for (int k = 0; k < 5; k++) {
            printf("%s", carry[i].options[carry[i].indices[k]]);
            // 섞인 보기 출력 (1~5로 번호 매기기)
        }

        

    }

    for(int i = 0; i < choice * 10; i++) {
        printf("%d\n", carry[i].correct_answer);
        // 각 문제의 정답 출력
	}



}


N1 * question_print (int n) {

    N1 * q = (N1 *)malloc(sizeof(N1) * n);
    N1* c = q;


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            q[i].indices[j] = j;
        }
    }

    srand((unsigned int)time(NULL));

    FILE* fp;
    fp = fopen("question.txt", "r");
	// 문제가 저장된 파일 열기

    if (fp == NULL) {
            printf("파일을 열 수 없습니다.\n");
            exit(1);
    }

    int i = 0;
    int* number = (int*)malloc(sizeof(int) * n);

    while (i < n) {

        int random = rand() % 30; // 파일에 있는 총 문제 수 입력
        int nk = 1;

        for (int j = 0; j < i; j++) {
            if (number[j] == random) {
                nk = 0;
                break;
            }
        }


        if (nk) {
            number[i] = random;
            i++;
        }
        // 중복되지 않는 랜덤 번호 생성
    }

    for (int i = 0; i < n; i++) {
        // 문제 수 만큼 출력 반복

        rewind(fp);
        int line_num = 0;


        char line[MAX_INDEX];
		// 한 줄씩 읽기 위한 변수
        int target = number[i];
        int start_line = target * 8;
		// 문제 번호에 해당하는 줄 번호 계산
        // 해당 문제 시작 줄 (문제당 8줄)

        int curr_line = 0;
		// 현재 줄 번호
        int correct_idx = -1;
        // 정답 인덱스 번호

        // 질문, 보기, 정답 읽기
        while (fgets(line, sizeof(line), fp)) {
            if (curr_line == start_line) strcpy(q[i].question[0], line);
            // 문제 읽기 1
            else if (curr_line == start_line + 1) strcpy(q[i].question[1], line);
            // 문제 읽기 2
            else if (curr_line >= start_line + 2 && curr_line < start_line + 7) {
				// 보기 범위 2~6줄 읽기
                strcpy(q[i].options[curr_line - start_line - 2], line);
            }
            else if (curr_line == start_line + 7) {
                correct_idx = atoi(line) - 1;
                // 정답 인덱스 읽기
                break;
            }
            curr_line++;
        }


        // 보기 섞기
        shuffle(q[i].indices, 5);

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

    fclose(fp);

    return q;

}


void shuffle(int* arr, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // 0부터 i까지 중 랜덤 인덱스
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
