#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"

//���� ��� ����
//������ ����Ϸ��� �� ������ ����
//����Ʈ ����, ��ŷ ���, ��� ��±��� �� ���� ����

void main(int argc, char * argv) {
// argc: ���� ����, argv: ���� �迭

    int num = atoi(argv[1]);
	// ���� ���� (1 ~ 3)

    N1* carry = NULL;
	// ������ ���� ����ü ������

    int* user_answer = (int*)malloc(sizeof(int) * (num * 10));
	// ����ڰ� �Է��� ������ ������ �迭

    carry = question_suffle(num * 10);
	// question_logic.c (question_data.h)
	// ������ ���� carry����ü �����ͷ� ����Ŵ

    if (argc == 1) {
// ���ڰ����� 1�̸� ���� ��� ���
        while (1) {
			// ���� ��ȣ 1�� ���� ���� 1 ~ 3

            if (num >= 1 && num <= 3) {

                for (int i = 0; i < num * 10; i++) {

                    printf("%s\n%s\n", carry[i].question[0], carry[i].question[1]);
					fflush(stdout);
                    // ���� ��� (���� ��ȣ, ���� ����)

                    for (int k = 0; k < 5; k++) {
                        printf("%s\n", carry[i].options[carry[i].indices[k]]);
                        fflush(stdout);
                        // ���� ���� ��� (1~5�� ��ȣ �ű��)
                    }

                }

            }
        }
    }
    else {
// ���ڰ����� ������ �̻��̸� ���� Ȯ�� ���

        for (int i = 0; i < num * 10; i++) {
			user_answer[i] = atoi(argv[2 + i]);
            // ���� ��ȣ 1�� ���� ����
			// 2�����ʹ� ����ڰ� �Է��� ����
        }

        correct_if(carry, user_answer, num * 10);
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
    }
}

        
    