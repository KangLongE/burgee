#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void shuffle(int* arr, int size);
void question(int n);


int main(void)
{
    
    int choice;

    while (1) {
        printf("1. 문제 10개 풀기\n2. 문제 20개 풀기\n3. 문제 30개 풀기\n");
        printf("선택지를 입력해 주세요 : ");
        scanf_s("%d", &choice);
        // 몇개의 문제를 풀지 선택

        if (choice >= 1 && choice <= 3) {
            printf("%d개 문제 풀기에 들어갑니다.\n\n", choice * 10);
            question(choice * 10);
            break;
        }
        else {
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
            continue;
        }
    }



}

void shuffle(int* arr, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // 0부터 i까지 중 랜덤 인덱스
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void question(int n) {

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

        int random = rand() % 30 + 1; // 파일에 있는 총 문제 수 입력
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

	

    int* useranswer = (int*)malloc(sizeof(int) * n);
    int* correct_answer = (int*)malloc(sizeof(int) * n);
	// 사용자 답안과 정답 저장용 배열

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
        char question[2][MAX_INDEX];
        // 문제 2줄
        char options[5][MAX_INDEX];
        // 보기 5줄
        int correct_idx = -1;
        // 정답 인덱스 번호

        // 질문, 보기, 정답 읽기
        while (fgets(line, sizeof(line), fp)) {
            if (curr_line == start_line) strcpy(question[0], line);
            // 문제 읽기 1
            else if (curr_line == start_line + 1) strcpy(question[1], line);
            // 문제 읽기 2
            else if (curr_line >= start_line + 2 && curr_line < start_line + 7) {
				// 보기 범위 2~6줄 읽기
                strcpy(options[curr_line - start_line - 2], line);
            }
            else if (curr_line == start_line + 7) {
                correct_idx = atoi(line) - 1;
                // 정답 인덱스 읽기
                break;
            }
            curr_line++;
        }


        // 보기 섞기
        int indices[5] = { 0, 1, 2, 3, 4 };
        shuffle(indices, 5);

        int new_correct = -1;
		// 새로운 정답 인덱스
        for (int k = 0; k < 5; k++) {
            if (indices[k] == correct_idx) {
				// 섞인 보기에서 정답 인덱스 찾기
                new_correct = k + 1;
                correct_answer[i] = new_correct;
				// 해당 문제에 정답 저장 (사용자 보기 1~5로 번호 매기기)
                break;
            }
        }

        // 문제 출력
        printf("\n문제 %d: \n%s%s", i + 1, question[0], question[1]);
		// 문제 출력 (문제 번호, 문제 내용)
        for (int k = 0; k < 5; k++) {
            printf("%d. %s", k + 1, options[indices[k]]);
			// 섞인 보기 출력 (1~5로 번호 매기기)
        }

        // 사용자 입력 받기
        int answer;
        while (1) {
            printf("1 ~ 5까지의 문항 중 정답을 입력해 주세요 : ");
            scanf_s("%d", &answer);
            if (answer >= 1 && answer <= 5) break;
            printf("잘못된 입력입니다.\n");
        }

        if (answer == new_correct) {

            useranswer[i] = 1;
        }
        else {
            useranswer[i] = 0;
        }
		// 정답 비교 (정답이면 1, 틀리면 0 저장)


    }

    free(number);

    int point = 0;
    for (int i = 0; i < n; i++) {
        if (useranswer[i]) {

            printf("문제%d : 정답!\n", i + 1);
            point++;
        }
        else
            printf("문제%d : 틀림.. (답 : %d)\n", i + 1, correct_answer[i]);
    }
    //정답 확인


	printf("\n총 %d문제 중 %d문제 맞췄습니다.\n", n, point);
	printf("점수 : %.2f%%\n", (float)point / n * 100);
	// 점수 출력 (맞춘 문제 수, 총 문제 수, 백분율)

    free(useranswer);
    free(correct_answer);

    fclose(fp);

}