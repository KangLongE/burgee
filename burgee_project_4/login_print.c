
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


//login ����
//�α��� �Ϸ��� �� ���� ȣ�� �ϸ� ��


void main(int argc, char**argv) {
//�ڹ� ��ũ��Ʈ���� �α��� ���� ��ȣ�� �Ǵ��ϰ�
//login_print.c ����

//argv[1]�� �̸�
//argv[2]���� ���� argv[5]���� �� �� �� �� ȣ

	int success = 0;
	//�α��� ���� ���θ� ����

	User u2;
	// ���� ������	[sign_log.h]
	// name[MAX_INDEX]
	// password[4]

	if (argc > 1) {
		//���� ������ ����

		strcpy(u2.name, argv[1]);
		//  �̸� ����
		for (int i = 0; i < 4; i++) {

			char* endptr;
			long val = strtol(argv[2 + i], &endptr, 10);
			//10������ �������� endptr�� ��ȯ�� ���� ����
			//��ȯ�� �� �Ǹ� 0�� ��ȯ

			if (*endptr != '\0' || val < 0 || val > 9) {
				printf("E:%d\n", 0);	//�ߴ� ��ȣ		[0]
				fflush(stdout);
				printf("EC:%d\n", val);		//�ߴ��� ���� ���
				fflush(stdout);
				exit(1);
			}
			else {
				u2.password[i] = val;
				//��й�ȣ ����
			}

		}

		success = login(u2.name, u2.password);
		// �α��� �Լ� ȣ��		[login.c] [sign_log.h]

		if (success == 1) {
			// �α��� ����	[1]
			printf("E:%d\n", success);	//��ȣ ����
			fflush(stdout);
			perror("�α��� ����!\n");
		}
		else if (success == -1) {
			//�α��� ���� �̸� Ʋ��	[-1]
			printf("E:%d\n", success);	//��ȣ ����
			fflush(stdout);
			perror("�̸��� ��ġ���� �ʽ��ϴ�.\n");
		}
		else if (success == -2) {
			//�α��� ���� ��й�ȣ Ʋ��	[-2]
			printf("E:%d\n", success);	//��ȣ ����
			fflush(stdout);
			perror("��й�ȣ�� ��ġ ���� �ʽ��ϴ�.\n");

		}
	}
	else {
		printf("E:%d\n", 0);	//�ߴ� ���� ��ȣ	[0]
		fflush(stdout);
		perror("���� �����ϴ�.\n");
		exit(1);
	}
}


int login(char* name, int* password) {
	//login_print.c �κ��� ȣ��  [sign_log.h]

	//name[MAX_INDEX]
	//password[4]

	struct User user;
	//�Է� ���� ���� ������ ����ü  [sign_log.h]

	strcpy(user.name, name);
	//�Է� ���� ���� �� �ֱ�

	for (int i = 0; i < 4; i++) {
		user.password[i] = password[i];
	}
	// �Է� ���� �н����� �� �ֱ�


	struct User readuser;
	//���Ͽ��� ���� ���� ������ ����ü    [sign_log.h]

	FILE* fp = fopen("UserData.txt", "r");
	// ���� ����

	if (fp == NULL) {
		perror("���� ���� ����\n");
		exit(1);
	}


	// ���Ͽ��� ������ �б�

	char nameLine[MAX_INDEX];
	//���� �̸� ���� ��
	char passwordLine[MAX_INDEX];
	//���� ��й�ȣ ���� �� 

	fgets(nameLine, sizeof(nameLine), fp); // name �� �б�
	fgets(passwordLine, sizeof(passwordLine), fp); // password �� �б�

	sscanf(nameLine, "name: %1024[^\n]", readuser.name); // ���Ͽ��� �̸� ����
	sscanf(passwordLine, "password: %d-%d-%d-%d",
		&readuser.password[0], &readuser.password[1],
		&readuser.password[2], &readuser.password[3]);
	// ���Ͽ��� ��й�ȣ ����

	// ��
	int match = 0;
	if (strcmp(user.name, readuser.name) == 0) {
		match = 1;
		for (int i = 0; i < 4; i++) {
			if (user.password[i] != readuser.password[i]) {
				match = 0;
				break;
			}
		}

		if (match) {
			return 1;
		}
		else {
			return -2;
		}
	}
	else {
		return -1;
	}
	// ���Ͽ� ����� ����� �̸��� ��й�ȣ�� ���Ͽ� �α��� ���� ���� ���

	fclose(fp);
}