

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


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
        char question[MAX_INDEX];
        int line_num = 0;

        while (fgets(question, sizeof(question), fp)) {
            if (line_num >= number[i] * 8 && line_num < number[i] * 8 + 7) {
                printf("%s", question); // 질문과 보기 출력
            }
            else if (line_num == number[i] * 8 + 7) {
                strcpy(correct_answer, question); // 정답 저장
                break;
            }
            line_num++;
        }

        int answer;
        while (1) {
            printf("1 ~ 5까지의 문항 중 정답을 입력해 주세요 : ");
            scanf_s("%d", &answer);

            if (answer < 1 || answer > 5) {
                printf("잘못된 입력입니다. 다시 입력해주세요.\n");
                continue;
            }
            else {
                break;
            }
        }
        // 응답 선택지 출력


        if (answer == atoi(correct_answer)) {
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
    
    
}


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


//#define _CRT_SECURE_NO_WARNINGS
//#define MAX_INDEX 1024
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//
//void random_quiz(int n) {
//    FILE* fp = fopen("question.txt", "r");
//    if (fp == NULL) {
//        printf("파일을 열 수 없습니다.\n");
//        return;
//    }
//
//    int number[MAX_INDEX], i = 0;
//    srand(time(NULL));
//
//    // 중복 없는 랜덤 번호 생성
//    while (i < n) {
//        int rand_num = rand() % 10; 
//        int duplicate = 0;
//        for (int j = 0; j < i; j++) {
//            if (number[j] == rand_num) {
//                duplicate = 1;
//                break;
//            }
//        }
//        if (!duplicate) {
//            number[i++] = rand_num;
//        }
//    }
//
//
//    int useranswer[MAX_INDEX];
//    char line[MAX_INDEX];
//    for (int i = 0; i < n; i++) {
//        int line_start = number[i] * 8;
//        rewind(fp); // 파일 처음부터 다시 읽음
//        int current = 0;
//        int answer;
//        char correct[MAX_INDEX] = "";
//
//        while (fgets(line, sizeof(line), fp)) {
//            if (current >= line_start && current < line_start + 7) {
//                printf("%s", line); // 질문 출력
//            }
//            if (current == line_start + 7) {
//                strcpy(correct, line);
//                break;
//            }
//            current++;
//        }
//
//        // 사용자 입력
//        while (1) {
//            printf("정답(1~5): ");
//            if (scanf("%d", &answer) != 1 || answer < 1 || answer > 5) {
//                printf("잘못된 입력입니다. 다시 입력하세요.\n");
//                while (getchar() != '\n'); // 입력 버퍼 비우기
//            }
//            else {
//                break;
//            }
//        }
//
//        if (answer == atoi(correct)) {
//            useranswer[i] = 1;
//        }
//        else {
//            useranswer[i] = 0;
//        }
//    }
//
//    for (int i = 0; i < n; i++) {
//        printf("%d번 문제 : %s\n", i + 1, useranswer[i] ? "정답!" : "틀림..");
//    }
//
//    fclose(fp);
//}
//
//int main() {
//    int count = 1;
//    random_quiz(count);
//    return 0;
//}

