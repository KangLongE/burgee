

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void shuffle(int* arr, int size);
void random(int n);


int main()
{

    int choice;


	
   while (1) {
        printf("1. 문제 10개 풀기\n2. 문제 20개 풀기\n3. 문제 30개 풀기\n");
        printf("선택지를 입력해 주세요 : ");
        scanf_s("%d", &choice);
        // 몇개의 문제를 풀지 선택

        if (choice >= 1 && choice <= 3) {
            printf("%d개 문제 풀기에 들어갑니다.\n\n", choice * 10);
            random(choice * 10);
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

void random(int n) {

    srand(time(NULL));

    FILE* fp;
    fp = fopen("question.txt", "r");

    int i = 0;
    int number[MAX_INDEX];

    while (i < n) {

        int random = rand() % 2 + 1; // 총 문제 수 입력
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

    int useranswer[MAX_INDEX] = { 1 };
    char correct_answer[MAX_INDEX] = { 0 };

    for (int i = 0; i < n; i++) {


        rewind(fp);
        int line_num = 0;


        char line[MAX_INDEX];
        int target = number[i];
        int start_line = target * 8;
        int curr_line = 0;

        char question[2][MAX_INDEX];
        // 문제 2줄
        char options[5][MAX_INDEX];
        // 보기 5줄
        int correct_idx = -1;
        // 정답 인덱스 번호

        // 질문, 보기, 정답 읽기
        while (fgets(line, sizeof(line), fp)) {
            if (curr_line == start_line) strcpy(question[0], line);
            // 문제 첫 줄 읽기
            else if (curr_line == start_line + 1) strcpy(question[1], line);
            // 문제 두번째 줄 읽기
            else if (curr_line >= start_line + 2 && curr_line < start_line + 7) {
                strcpy(options[curr_line - start_line - 2], line);
                // 보기 5줄 읽기
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

        // 정답이 섞인 보기에선 몇 번째인지 찾기
        int new_correct = -1;
        for (int k = 0; k < 5; k++) {
            if (indices[k] == correct_idx) {
                new_correct = k + 1;
                // 사용자 기준 보기 1~5
                break;
            }
        }

        // 문제 출력
        printf("\n문제 %d: \n%s%s", i + 1, question[0], question[1]);
        for (int k = 0; k < 5; k++) {
            printf("%d. %s", k + 1, options[indices[k]]);
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
        // 정답 비교


    }

    for (int i = 0; i < n; i++) {
        if (useranswer[i])
            printf("문제%d : 정답!\n", i + 1);
        else
            printf("문제%d : 틀림..\n", i + 1);
    }
    //정답 확인

    fclose(fp);

}

