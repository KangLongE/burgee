
#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"
#include "sign_log.h"
#include "note.h"

//signup ����
//ȸ�� ���� �Ϸ��� �� ������ ����

int main(int argc, char* argv[]) {
// argc: ���� ����, argv: ���� �迭
    // ���ڰ��� 1�� ���� ������ ����
	// ���ڰ��� 2�� ���� �Ѱ� ��������

    char yn;
	// yn: ȸ������ ���� Ȯ�� ����

    int i = 0;

    char buffer[MAX_INDEX];
	// buffer: ���Ͽ��� ���� �����͸� ������ ����

    FILE* fp;
    fp = fopen("UserData.txt", "r");
	// UserData.txt ���� ����
    
    if (fp == NULL) {
        printf("���� ���� ����\n");
        exit(1);
	}

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
	// ���� ũ�� Ȯ��


    if (argc == 1) {
//���ڰ����� 1   [���� ������ ����]
// ���� ������ ������ �α��� ���� Ȯ��

        if (fp == NULL || size == 0) {
	    // ������ ����ְų� �������� ������

            printf("%d", 0);    //�α����� �������� �ʴٴ� ��ȣ�� ����    [0]
			fflush(stdout);
            printf("�α����� �Ǿ����� �ʽ��ϴ�.\nȸ������ �Ͻðڽ��ϱ�? : Y / N\n: ");
            fflush(stdout);

        }
        else {
        // ������ �����ϰ� ������� ������

			printf("%d", 1);    //�α��� ���� ��ȣ ����    [1]
            fflush(stdout);
        }
    }


    if (argc == 2) {
	// ���� ������ 2�̸� ȸ����� �� �α��� ���� Ȯ��
	//ȸ������ �ϰڴ�   [1]
	// ���α׷� ����    [0]

        if (argv[1]) {
        //ȸ������ �ϰڴ�   [1]

            signup();
            // signup.c     [sign_log.h]
            // ȸ������ �Լ� ȣ��

        }
        else {
        //���α׷� ����   [0]

            printf("%d", 1); //���� ��ȣ�� ����    [1]
            fflush(stdout);
            printf("���α׷��� �����մϴ�.\n");
        }
    }

}
