
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"
#include "sign_log.h"
#include "note.h"

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
			printf("�α��� ����!\n");
		}
		else if (success == -1) {
			//�α��� ���� �̸� Ʋ��	[-1]
			printf("E:%d\n", success);	//��ȣ ����
			fflush(stdout);
			printf("�̸��� ��ġ���� �ʽ��ϴ�.\n");
		}
		else if (success == -2) {
			//�α��� ���� ��й�ȣ Ʋ��	[-2]
			printf("E:%d\n", success);	//��ȣ ����
			fflush(stdout);
			printf("��й�ȣ�� ��ġ ���� �ʽ��ϴ�.\n");

		}
	}
	else {
		printf("E:%d\n", 0);	//�ߴ� ���� ��ȣ	[0]
		fflush(stdout);
		printf("���� �����ϴ�.\n");
		exit(1);
	}
}