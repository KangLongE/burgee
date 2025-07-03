
#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"
#include "sign_log.h"
#include "note.h"

//login ����
//�α��� �Ϸ��� �� ���� ȣ�� �ϸ� ��


void main(int argc, char* argv[]) {
//�ڹ� ��ũ��Ʈ���� �α��� ���� ��ȣ�� �Ǵ��ϰ�
//login_print.c ����

//argv[1]�� �̸�
//argv[2]���� ���� argv[5]���� �� �� �� �� ȣ


	User u;
	// ���� ������	[sign_log.h]
	// name[MAX_INDEX]
	// password[4]

	if (argc > 1) {
		//���� ������ ����

		strcpy(u.name, argv[1]);
		//  �̸� ����
		for (int i = 0; i < 4; i++) {
			u.password[i] = atoi(argv[2 + i]);
			//�н����� ����
			//2���� ���� 5���� ����
			if (u.password[i] < 0 || u.password[i] > 9) {
				// �н����尡 0~9 ���̰� �ƴϸ� ����

				printf("%d", 0); //�ߴ� ���� ��ȣ	[0]
				fflush(stdout);
				printf("0 ~ 9������ �Է� �����մϴ�.");
				fflush(stdout);
				exit(1);
			}
		}

		login(u.name, u.password);
		// �α��� �Լ� ȣ��		[login.c] [sign_log.h]

		if (success == 1) {
			// �α��� ����	[1]
			printf("%d", success);	//��ȣ ����
			fflush(stdout);
			printf("�α��� ����!");
		}
		else if (success == -1) {
			//�α��� ���� �̸� Ʋ��	[-1]
			printf("%d", success);	//��ȣ ����
			fflush(stdout);
			printf("�̸��� ��ġ���� �ʽ��ϴ�.");
		}
		else if (success == -2) {
			//�α��� ���� ��й�ȣ Ʋ��	[-2]
			printf("%d", success);	//��ȣ ����
			fflush(stdout);
			printf("��й�ȣ�� ��ġ ���� �ʽ��ϴ�.");

		}
	}
	else {
		printf("%d", 0);	//�ߴ� ���� ��ȣ	[0]
		fflush(stdout);
		printf("���� �����ϴ�.");
		exit(1);
	}
}