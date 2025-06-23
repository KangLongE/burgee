// point.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ML 256
#define MAX_LOG 10

typedef struct Log {
    char id[50];
    int point;
    char date[20];
} log;

void save_point(log);

int main(void)
{
    log c;
    

    save_point(c);
}

void save_point(log c1) {
    FILE* file = fopen("C:\\Users\\user\\Desktop\\project\\UserData.txt", "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        exit(1);
    }

    char header1[ML] = { 0 }; // name
    char header2[ML] = { 0 }; // password
    char logs[MAX_LOG][ML] = { 0 }; // point 내역
    int log_count = 0;

    // 헤더 두 줄 읽기
    fgets(header1, ML, file);
    fgets(header2, ML, file);

    // 기존 포인트 내역 읽기 (최대 10개)
    while (log_count < MAX_LOG&& fgets(logs[log_count], ML, file) != NULL) {
        log_count++;
    }
    fclose(file);

    // ID 추출 (header1에서)
    // 예: "name: eum\n"
    sscanf(header1, "name: %s", c1.id);

    // 날짜 생성
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(c1.date, sizeof(c1.date), "%Y-%m-%d %H:%M", tm_info);

    // 새 로그 만들기
    char new_log[ML];
    snprintf(new_log, ML, "%s/%s : %d\n", c1.date, c1.id, c1.point);

    // logs 배열 한 칸씩 아래로 밀기 (맨 아래 내역은 사라짐)
    for (int i = MAX_LOG - 1; i > 0; i--) {
        strcpy(logs[i], logs[i - 1]);
    }
    strcpy(logs[0], new_log); // 새 로그를 맨 위에 추가

    // 파일 다시 쓰기
    file = fopen("C:\\Users\\user\\Desktop\\project\\UserData.txt", "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        exit(1);
    }

    fputs(header1, file);
    fputs(header2, file);

    // 최대 10개 내역만 기록
    for (int i = 0; i < MAX_LOG; i++) {
        if (logs[i][0] != '\0')
            fputs(logs[i], file);
    }

    fclose(file);
    printf("점수 저장 완료\n");
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
