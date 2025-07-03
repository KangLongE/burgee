

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "question_data.h"

#define ML 256
#define MAX_LOG 10


void save_point(double point) {
//question_print.c에서 호출  [question_data.h]
//point는 question_logic.c에서 correct_if에서 반환

    log c1;     //[question_data.h]
    //id[50]
    //point
    //date[20]

    pl c2;      //[question_data.h]
    //header1[ML]       name
    //header2[ML]       password
    //all_p[ML]         총 포인트 점수를 읽을 줄
    //logs[MAX_LOG][ML] 포인트 내역
    //log_count         로그 카운트

	double total_p = 0;
    // 총 포인트 점수를 받을 변수

    for (int i = 0; i < MAX_LOG; i++) {
        c2.logs[i][0] = '\0';
    }
	// logs 배열 초기화

    FILE* file = fopen("UserData.txt", "r");
    //파일 읽기

    if (file == NULL) {
        perror("파일 열기 실패");
		exit(1);
    }

    c2.log_count = 0;
    // 카운트 초기화

    // 헤더 세 줄 읽기
    fgets(c2.header1, ML, file);    //name
    fgets(c2.header2, ML, file);    //password
    fgets(c2.all_p, ML, file);      //총 포인트

    if(c2.all_p[0] == '\0') {
        strcpy(c2.all_p, "전체 포인트: 0\n");
        // 전체 포인트가 비어있으면 초기화
	}
    else {
        
		total_p = atoi(c2.all_p + strcspn(c2.all_p, ":") + 1);
        // 총 포인트 점수 줄을 읽고
        //전체 포인트 숫자 추출
        c2.all_p[strcspn(c2.all_p, "\n")] = '\0'; // 개행 문자 제거
	}

	
    while (c2.log_count < MAX_LOG&& fgets(c2.logs[c2.log_count], ML, file) != NULL) {
        c2.log_count++;
    }
    // 기존 포인트 내역 읽기 (최대 10개)

    fclose(file);
    //읽기 파일 닫기


    // ID 추출 (header1에서)
    // 예: "name: eum\n"
    sscanf(c2.header1, "name: %s", c1.id);

	// 전체 포인트 갱신
	total_p += point;
	sprintf(c2.all_p, "전체 포인트: %.4f\n", total_p);

    // 날짜 생성
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(c1.date, sizeof(c1.date), "%Y-%m-%d-%H:%M", tm_info);

    // 새 로그 만들기
    char new_log[ML];
    snprintf(new_log, ML, "%s/%s : %.4f\n", c1.date, c1.id, c1.point);
    //예 : 2025-06-05-12:30/eum 12.2222


    // logs 배열 한 칸씩 아래로 밀기 (맨 아래 내역은 사라짐)
    for (int i = MAX_LOG - 1; i > 0; i--) {
        strcpy(c2.logs[i], c2.logs[i - 1]);
    }
    strcpy(c2.logs[0], new_log); // 새 로그를 맨 위에 추가

    file = fopen("UserData.txt", "w");
    //파일 쓰기로 열기
    //파일 다시 쓰기

    if (file == NULL) {
        perror("파일 열기 실패");
		exit(1);
    }

	// 헤더 두 줄과 전체 포인트 쓰기
    fputs(c2.header1, file);
    fputs(c2.header2, file);
	fputs(c2.all_p, file);
	
    for (int i = 0; i < MAX_LOG; i++) {
        if (c2.logs[i][0] != '\0')
            fputs(c2.logs[i], file);
    }
    // 최대 10개 내역만 기록

    fclose(file);
    //파일 닫기
}

