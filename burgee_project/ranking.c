
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
		perror("파일 열기 실패");
		exit(1);
	}
	printf("랭킹을 불러오는 중...\n");

	char line[12][ML];

	char name[ML];

	while (fgets(line, ML, file) != NULL) {

		if (c3.log_count >= 2) {
			if (strchr(line, '/') && strrchr(line, ':')) {
				// 예: "2025.06.05.12:00/eum : 10"
				char* slash = strchr(line, '/');
				// /eum 이름 읽을 준비
				char* colon = strrchr(line, ':');
				// : 10 포인트 읽을 준비
				if (colon != NULL) {
					double score = atoi(colon + 1);  
					// ':' 다음 위치부터 숫자 추출
				}

				if (slash && colon) {
					// 닉네임 추출
					slash++;  // '/' 다음 문자부터
					char* end = strchr(slash, ' ');  // 공백 전까지가 닉네임
					if (!end) continue;
					int name_len = end - slash;
					strncpy(name, slash, name_len);
					name[name_len] = '\0';

					// 점수 추출
					int score = atoi(colon + 1);

					// logs와 점수 저장
					sprintf(c3.logs[c3.log_count - 2], "%s", name);  // 닉네임만 저장
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
					//가장 높은 포인트를 가진 사용자 데이터를 위로 올림

					bemp = rank_p[i];
					rank_p[i] = rank_p[j];
					rank_p[j] = bemp;
					//가장 높은 포인트를 위로 올림


				}
			}
		}

		file = fopen("ranking.txt", "w");
		if (file == NULL) {
			perror("파일 열기 실패");
			exit(1);
		}

		for (int i = 0; i < MAX_LOG; i++) {
			if (c3.logs[i][0] != '\0') {
				fprintf(file, "%d) %s : %.4f\n", i + 1, c3.logs[i], rank_p[i]);
				// 랭킹 파일에 기록
			}

		}
		printf("랭킹을 ranking.txt에 저장했습니다.\n");
		fclose(file);



}

