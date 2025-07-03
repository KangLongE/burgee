#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"

//���� ��� ����
//������ ����Ϸ��� �� ������ ����
//����Ʈ ����, ��ŷ ���, ��� ��±��� �� ���� ����

void main(int argc, char ** argv) {
// argc: ���� ����, argv: ���� �迭

    int num = atoi(argv[1]);
	// ���� ���� (1 ~ 3)

    N1* carry = NULL;
	// ������ ���� ����ü ������


    if (argc == 2) {
// ���ڰ����� 1�̸� ���� ��� ���

        carry = question_suffle(num * 10);
        // question_logic.c (question_data.h)
        // ������ ���� carry����ü �����ͷ� ����Ŵ

            if (num >= 1 && num <= 3) {

                for (int i = 0; i < num * 10; i++) {

                    printf("Q:%s\nQ:%s\n", carry[i].question[0], carry[i].question[1]);
					fflush(stdout);
                    // ���� ��� (���� ��ȣ, ���� ����)

                    for (int k = 0; k < 5; k++) {
                        printf("A:%s\n", carry[i].options[carry[i].indices[k]]);
                        fflush(stdout);
                        // ���� ���� ��� (1~5�� ��ȣ �ű��)
                    }

                }

                FILE* fp;
                fp = fopen("correct.txt", "w");

                if (fp == NULL) {
                    printf("E:%d\n", 0);  //���� ��ȣ [0]
                    fflush(stdout);
                    perror("���� ���� ���� ����\n");
                    exit(1);
                }

                for (int i = 0; i < num * 10; i++) {
                    fprintf(fp, "%d ", carry[i].correct_answer);
                }
                fclose(fp);
            }

            free(carry);

    }
    else {
// ���ڰ����� ������ �̻��̸� ���� Ȯ�� ���

        int* user_answer = (int*)malloc(sizeof(int) * (num * 10));

        // ����ڰ� �Է��� ������ ������ �迭
        

        if (argc < num * 10 + 2) {
            printf("E:%d\n", 0);  //���� ��ȣ [0]
            fflush(stdout);
            printf("���� ���� ����\n");
            free(user_answer);
            free(carry);
            exit(1);
        }

        for (int i = 0; i < num * 10; i++) {
			user_answer[i] = atoi(argv[2 + i]);
            // ���� ��ȣ 1�� ���� ����
			// 2�����ʹ� ����ڰ� �Է��� ����
        }

        correct_if(user_answer, num * 10);
		// question_logic.c     (question_data.h)
		// ���� Ȯ�� �Լ� ȣ��
        
        save_point(point);
        // point.c      (question_data.h)
        // ���� Ȯ�� �� ����Ʈ ����
		

        point = 0;
        // ���� Ǯ�� �� ���� �ʱ�ȭ

        ranking();
		// ranking.c    (question_data.h)
		// ��ŷ ������Ʈ


        free(user_answer);
    }

}

        
    