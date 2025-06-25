
#define ML 256
#define MAX_LOG 10
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "question_data.h"

void ranking() {

	pl c3;
	double rank_p[10] = {0};
	c3.log_count = 0;

	for(int i = 0; i < MAX_LOG; i++) {
		c3.logs[i][0] = '\0';
	}

	FILE* file = fopen("UserData.txt", "r");

	if (file == NULL) {
		perror("���� ���� ����");
		exit(1);
	}
	printf("��ŷ�� �ҷ����� ��...\n");

	char line[12][ML];

	char name[ML];

	while (fgets(line, ML, file) != NULL) {

		if (c3.log_count >= 2) {
			if (strchr(line, '/') && strrchr(line, ':')) {
				// ��: "2025.06.05.12:00/eum : 10"
				char* slash = strchr(line, '/');
				// /eum �̸� ���� �غ�
				char* colon = strrchr(line, ':');
				// : 10 ����Ʈ ���� �غ�
				if (colon != NULL) {
					double score = atoi(colon + 1);  
					// ':' ���� ��ġ���� ���� ����
				}

				if (slash && colon) {
					// �г��� ����
					slash++;  // '/' ���� ���ں���
					char* end = strchr(slash, ' ');  // ���� �������� �г���
					if (!end) continue;
					int name_len = end - slash;
					strncpy(name, slash, name_len);
					name[name_len] = '\0';

					// ���� ����
					int score = atoi(colon + 1);

					// logs�� ���� ����
					sprintf(c3.logs[c3.log_count - 2], "%s", name);  // �г��Ӹ� ����
					rank_p[c3.log_count - 2] = score;

					
					if (c3.log_count >= MAX_LOG) break;
				}
			}
		}
		c3.log_count++;
	}

	fclose(file);

		char aemp[ML];
		int bemp;
		for(int i = 0; i < MAX_LOG; i++) {
			for(int j = i + 1; j < MAX_LOG; j++) {

				if (rank_p[i] < rank_p[j]) {
					
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
		if (file == NULL) {
			perror("���� ���� ����");
			exit(1);
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

