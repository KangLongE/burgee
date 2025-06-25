#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"
#include "sign_log.h"
#include "note.h"

int main(void) {

    char yn;

    int i = 0;
    char buffer[MAX_INDEX];

    FILE* fp;
    fp = fopen("UserData.txt", "r");


    if (fp == NULL) {

        printf("로그인이 되어있지 않습니다.\n회원가입 하시겠습니까? : Y / N\n: ");
        scanf("%c", &yn, 1);
        while ((getchar()) != '\n' && !feof(stdin));


        if (yn == 'Y' || yn == 'y')
        {
            signup();
        }
        else if (yn == 'N' || yn == 'n') {
            printf("\n프로그램을 종료합니다.\n");
            return 0;
        }
        else {
            printf("\n잘못된 입력입니다.\n");
        }


    }
    else {

        fseek(fp, 0, SEEK_END);  
        long size = ftell(fp);   
        rewind(fp);              

        if (size == 0) {
            while (1) {
                printf("로그인이 되어있지 않습니다.\n회원가입 하시겠습니까? : Y / N\n: ");
                scanf("%c", &yn, 1);
                while ((getchar()) != '\n' && !feof(stdin));


                if (yn == 'Y' || yn == 'y')
                {
                    signup();
                    break;
                }
                else if (yn == 'N' || yn == 'n') {
                    printf("\n프로그램을 종료합니다.\n");
                    return 0;
                }
                else {
                    printf("\n잘못된 입력입니다.\n");
                }
            }
        }
        else {
            while (1) {

                login();

                if (success) {
                    break;
                }
                else {

                    i++;

                    if (i < 3) {
                        while (1) {
                            printf("\n로그인 실패. 다시 시도하시겠습니까? (Y/N): ");
                            scanf_s(" %c", &yn, 1);
                            while ((getchar()) != '\n' && !feof(stdin));

                            if (yn == 'Y' || yn == 'y') {
                                break;
                            }
                            else if (yn == 'N' || yn == 'n') {
                                printf("\n프로그램을 종료합니다.\n");
                                fclose(fp);
                                return 0;
                            }
                            else {
                                printf("\n잘못된 입력입니다.\n");
                            }
                        }
                    }


                    if (i >= 3) {

                        printf("\n로그인 시도 횟수를 초과했습니다.\n프로그렘 종료 : Y\n회원가입 : N\n: ");
                        scanf_s(" %c", &yn, 1);
                        while ((getchar()) != '\n' && !feof(stdin));

                        if (yn == 'Y' || yn == 'y') {
                            printf("\n프로그램을 종료합니다.\n");
                            fclose(fp);
                            return 0;
                        }
                        else if (yn == 'N' || yn == 'n') {
                            signup();
                            printf("\n회원가입이 완료되었습니다.\n다시 접속하여 로그인 해주세요.\n");
                            return 0;
                        }
                        else {
                            printf("\n잘못된 입력입니다. 프로그렘을 종료 합니다.\n");
                            return 0;
                        }

                    }
                }
            }


        }

    }


    fclose(fp);

    int choice;

    N1* carry = NULL;

    while (1) {
        printf("\n1. 문제 10개 풀기\n2. 문제 20개 풀기\n3. 문제 30개 풀기\n");
		printf("4. 포인트 내역 보기\n5. 랭킹 보기\n6. 끝마치기\n");
        printf("선택지를 입력해 주세요 : ");
        scanf("%d", &choice);
        // 몇개의 문제를 풀지 선택

        int* user_answer = (int*)malloc(sizeof(int) * (choice * 10));

        if (choice >= 1 && choice <= 3) {
            printf("%d개 문제 풀기에 들어갑니다.\n\n", choice * 10);

            carry = question_print(choice * 10);


            for (int i = 0; i < choice * 10; i++) {

                printf("\n문제 %d: \n%s%s", i + 1, carry[i].question[0], carry[i].question[1]);
                // 문제 출력 (문제 번호, 문제 내용)

                for (int k = 0; k < 5; k++) {
                    printf("%d. %s", k + 1, carry[i].options[carry[i].indices[k]]);
                    // 섞인 보기 출력 (1~5로 번호 매기기)
                }

                // 사용자 입력 받기
                int answer;
                while (1) {
                    printf("1 ~ 5까지의 문항 중 정답을 입력해 주세요 : ");
                    scanf("%d", &answer);
                    if (answer >= 1 && answer <= 5) {
                        user_answer[i] = answer;
                        break;
                    }
                    else {
                        printf("잘못된 입력입니다.\n");
                        continue;
                    }
                }
            }


            correct_if(carry, user_answer, choice * 10);
            save_point(point);
			point = 0; // 문제 풀이 후 점수 초기화
			ranking();
        }
        else if(choice == 4) {
            printf("\n포인트 내역을 확인합니다.\n");
            
            pl c4;
            int i = 0;

			FILE* file = fopen("UserData.txt", "r");
            if (file == NULL) {
                printf("포인트 내역 파일을 열 수 없습니다.\n");
                return 1;
            }
            
            char line[ML];
            while (fgets(line, sizeof(line), file)) {
				if (i > 1) printf("%s", line);
                i++;
            }

			fclose(file);
            
        }
        else if(choice == 5) {
            printf("\n랭킹을 확인합니다.\n");
            
			FILE* file = fopen("ranking.txt", "r");
            if (file == NULL) {
                printf("랭킹 파일을 열 수 없습니다.\n");
                return 1;
            }
            char line[ML];
            int i = 0;
            while (fgets(line, sizeof(line), file)) {
                    printf("%s", line);
                    i++;
            }
			fclose(file);

        }
        else if(choice == 6) {
            printf("\n프로그램을 종료합니다.\n");
            free(user_answer);
            return 0;
		}
        else {
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
            continue;
        }
    }
}