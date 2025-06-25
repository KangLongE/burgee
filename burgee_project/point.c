

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "question_data.h"

#define ML 256
#define MAX_LOG 10


void save_point(double point) {

    log c1;
    pl c2;
	double total_p = 0;

    for (int i = 0; i < MAX_LOG; i++) {
        c2.logs[i][0] = '\0';
    }
	// logs 배열 초기화

    FILE* file = fopen("UserData.txt", "r");
    if (file == NULL) {
        perror("파일 열기 실패");
		exit(1);
    }

    c2.log_count = 0;

    // 헤더 두 줄 읽기
    fgets(c2.header1, ML, file);
    fgets(c2.header2, ML, file);
    fgets(c2.all_p, ML, file);

    if(c2.all_p[0] == '\0') {
        // 전체 포인트가 비어있으면 초기화
        strcpy(c2.all_p, "전체 포인트: 0\n");
	}else {
        
		total_p = atoi(c2.all_p + strcspn(c2.all_p, ":") + 1); // 전체 포인트 숫자 추출
        c2.all_p[strcspn(c2.all_p, "\n")] = '\0'; // 개행 문자 제거
	}

	 
    // 기존 포인트 내역 읽기 (최대 10개)
    while (c2.log_count < MAX_LOG&& fgets(c2.logs[c2.log_count], ML, file) != NULL) {
        c2.log_count++;
    }
    fclose(file);


    // ID 추출 (header1에서)
    // 예: "name: eum\n"
    sscanf(c2.header1, "name: %s", c1.id);

    // 함수 인자로 받은 point를 사용
    c1.point = point;

	// 전체 포인트 갱신
	total_p += c1.point;
	sprintf(c2.all_p, "전체 포인트: %.4f\n", total_p);

    // 날짜 생성
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(c1.date, sizeof(c1.date), "%Y-%m-%d-%H:%M", tm_info);

    // 새 로그 만들기
    char new_log[ML];
    snprintf(new_log, ML, "%s/%s : %.4f\n", c1.date, c1.id, c1.point);

    // logs 배열 한 칸씩 아래로 밀기 (맨 아래 내역은 사라짐)
    for (int i = MAX_LOG - 1; i > 0; i--) {
        strcpy(c2.logs[i], c2.logs[i - 1]);
    }
    strcpy(c2.logs[0], new_log); // 새 로그를 맨 위에 추가

    // 파일 다시 쓰기
    file = fopen("UserData.txt", "w");
    if (file == NULL) {
        perror("파일 열기 실패");
		exit(1);
    }

	// 헤더 두 줄과 전체 포인트 쓰기
    fputs(c2.header1, file);
    fputs(c2.header2, file);
	fputs(c2.all_p, file);
	
    // 최대 10개 내역만 기록
    for (int i = 0; i < MAX_LOG; i++) {
        if (c2.logs[i][0] != '\0')
            fputs(c2.logs[i], file);
    }

    fclose(file);
    printf("점수 저장 완료\n");
}

