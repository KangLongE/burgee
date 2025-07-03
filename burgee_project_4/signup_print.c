
#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int success = 0;

typedef struct User {
    char name[MAX_INDEX];
    int password[4];
} User;

int signup(char* name, int* password);
int login(char* name, int* password);


//signup ����
//ȸ�� ���� �Ϸ��� �� ������ ����

int main(int argc, char** argv) {
// argc: ���� ����, argv: ���� �迭
    // ���ڰ��� 1�� ���� ������ ����
	// ���ڰ��� 2�� ���� �Ѱ� ��������

    int i = 0;

    FILE* fp;
    fp = fopen("UserData.txt", "r, ccs=UTF-8");
	// UserData.txt ���� ����
    
    if (fp == NULL) {
        perror("���� ���� ����\n");
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

            printf("E:%d\n", 0);    //�α����� �������� �ʴٴ� ��ȣ�� ����    [0]
			fflush(stdout);
            perror("�α����� �Ǿ����� �ʽ��ϴ�.");

        }
        else {
        // ������ �����ϰ� ������� ������

			printf("E:%d\n", 1);    //�α��� ���� ��ȣ ����    [1]
            fflush(stdout);
        }
    }


    if (argc >= 2) {
	// ���� ������ 2�̸� ȸ����� �� �α��� ���� Ȯ��
	//ȸ������ �ϰڴ�   [1]
	// ���α׷� ����    [0]

        if (argv[1]) {
        //ȸ������ �ϰڴ�   [1]


        int success = 0;

        User u1;
            
        strcpy(u1.name, argv[2]);

            for (int i = 0; i < 4; i++) {

                char* endptr;
                long val = strtol(argv[3 + i], &endptr, 10);
                //argv�� ���� 10������ �������� val�� ��ȯ�� ���� ����
                //��ȯ�� �� �Ǹ� endptr�� 0�� ��ȯ

                if (*endptr != '\0' || val < 0 || val > 9) {
                    printf("E:%d\n", 0);	//�ߴ� ��ȣ		[0]
                    fflush(stdout);
                    printf("EC:%s\n", argv[3 + i]);		//�ߴ��� ���� ���
                    fflush(stdout);
                    exit(1);
                }
                else {
                    u1.password[i] = val;
                }

            }

            success = signup(u1.name, u1.password);
            // signup.c     [sign_log.h]
            // ȸ������ �Լ� ȣ��

            if (success) {
                printf("E:%d\n", 1);  //���� ��ȣ [1]
                fflush(stdout);
                perror("%����!\n");
            }
            else {
                printf("E:%d\n", 0);    //���� ��ȣ [0]
                fflush(stdout);
                perror("����!\n");
            }

        }
        else {
        //���α׷� ����   [0]

            printf("E:%d\n", 0); //���� ��ȣ�� ����    [0]
            fflush(stdout);
            perror("���α׷��� �����մϴ�.\n");
        }
    }

}


int signup(char* name, int* password)
{

    FILE* fp;
    fp = fopen("UserData.txt", "w, ccs=UTF-8");
    // UserData.txt ���� ����

    if (fp == NULL) {
        perror("���� ���� ����\n");
        return 0;
    }

    // UserData.txt ���Ͽ� �̸� �Է�
    fprintf(fp, "name: %s", name);

    fprintf(fp, "password: ");
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d", password[i]);
        if (i < 3) {
            fprintf(fp, "-");
        }
    }
    fprintf(fp, "\n");
    // UserData.txt ���Ͽ� ��й�ȣ �Է�



    fclose(fp);

    perror("���Ͽ� ���� �Ϸ�");
    return 1;
}