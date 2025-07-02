
#define ML 256
#define MAX_LOG 10
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "question_data.h"

int main(int argc, char ** argv) {
	ranking();
}


void ranking() {
// ��ŷ�� �ҷ��ͼ� �����ϰ� �����ϴ� �Լ�
// ����Ʈ�� �߰� �� ������ ȣ���

	pl c3;
	// pl ����ü ���� c3 ���� [pl <- pline` ����ü]

	double rank_p[10] = {0};
	// ��ŷ ����Ʈ �迭 �ʱ�ȭ

	c3.log_count = 0;
	// �α� ���� �ʱ�ȭ
	// 0 ~ 9���� 10��	[MAX_LOG]

	for(int i = 0; i < MAX_LOG; i++) {
		c3.logs[i][0] = '\0';
	}
	// logs �迭 �ʱ�ȭ

	FILE* file = fopen("UserData.txt", "r");
	// UserData.txt ���� ����

	if (file == NULL) {
		perror("���� ���� ����");
		exit(1);
	}

	printf("��ŷ�� �ҷ����� ��...\n");

	char line[ML];
	// �� �پ� �б� ���� ����	[12�ٱ��� ���� �� �ֵ��� ����]
	// ������ ����� ��� name, password
	
	// ���� 10���� ��ŷ ��Ͽ�
	// ��: "2025.06.05.12:00/eum : 10\n"

	char name[ML];
	// �г��� ����� ����

	while (fgets(line, ML, file) != NULL && c3.log_count < MAX_LOG + 2) {
	// ���Ͽ��� �� �پ� �б�

		if (c3.log_count >= 2) {
		// ��� �� ���� �����ϰ� ��ŷ ��� �б�

			if (strchr(line, '/') && strrchr(line, ':')) {
				// ��: "2025.06.05.12:00/eum : 10"

				char* slash = strchr(line, '/');
				// /eum �̸� ���� �غ�

				char* colon = strrchr(line, ':');
				// : 10 ����Ʈ ���� �غ�
				
				if (colon != NULL) {
					double score = atof(colon + 1);  
					// ':' ���� ��ġ���� ���� ����
					// : ����
				}

				if (slash && colon) {
					// �̸� ����
					slash++;  // '/' ���� ���ں���
					char* end = strchr(slash, ' ');  // ���� �������� �г���
					if (!end) continue;
					int name_len = end - slash;
					// �̸� ���� ���
					if (name_len >= ML) name_len = ML - 1;
					// ������ ũ�Ⱑ name�� ũ�⺸�� Ŭ �� �־
					strncpy(name, slash, name_len);
					// �̸� ����
					name[name_len] = '\0';
					// ���ڿ� ���� �� ���� �߰�

					
					int score = atoi(colon + 1);
					// :�� ������ ���� �б�	[���ڸ� ����]

					// logs�� ���� ����
					sprintf(c3.logs[c3.log_count - 2], "%s", name);
					// �г��Ӹ� ����
					rank_p[c3.log_count - 2] = score;
					// rank_p�� ���� ����

					
					if (c3.log_count >= MAX_LOG) break;
					// �α� ������ �ִ�ġ�� �����ϸ� �ߴ�
				}
			}
		}
		c3.log_count++;
		// �α� ���� ����
	}

	fclose(file);

		char aemp[ML];
		// �ӽ� ���� aemp ����	[����� �ٲٱ� ����]
		double bemp;
		// �ӽ� ���� bemp ����	[����Ʈ �ٲٱ� ����]

		for(int i = 0; i < MAX_LOG; i++) {
			for(int j = i + 1; j < MAX_LOG; j++) {

				if (rank_p[i] < rank_p[j]) {
					// ��ŷ ����Ʈ ��
					// i��° ����Ʈ�� j��° ����Ʈ���� ������
					
					strcpy(aemp, c3.logs[i]);
					strcpy(c3.logs[i], c3.logs[j]);
					strcpy(c3.logs[j], aemp);
					//���� ���� ����Ʈ�� ���� ����� �����͸� ���� �ø�

					bemp = rank_p[i];
					rank_p[i] = rank_p[j];
					rank_p[j] = bemp;
					//���� ���� ����Ʈ�� ���� �ø�


				}
			}
		}

		file = fopen("ranking.txt", "w");
		// ��ŷ ���� ����

		if (file == NULL) {
			perror("���� ���� ����");
			exit(0);
		}

		for (int i = 0; i < MAX_LOG; i++) {
			if (c3.logs[i][0] != '\0') {
				fprintf(file, "%d) %s : %.4f\n", i + 1, c3.logs[i], rank_p[i]);
				// ��ŷ ���Ͽ� ���
			}

		}
		printf("��ŷ�� ranking.txt�� �����߽��ϴ�.\n");
		fclose(file);


}

