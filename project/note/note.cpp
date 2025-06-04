// note.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_note() {

    FILE* fp;
    fp = fopen("note.txt", "a");

    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return;
    }

    char input[MAX_INDEX];
    printf("메모를 입력하세요 (끝내려면 빈 줄 입력):\n");

    while (1) {
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "\n") == 0) break; // 빈 줄로 종료
        fputs(input, fp);
    }

    fclose(fp);
    printf("메모 저장 완료!\n");
}

void read_note() {

    FILE* fp = fopen("note.txt", "a");
    if (fp == NULL) {
        printf("파일 없음\n");
        return;
    }

    char line[MAX_INDEX];
    printf("저장된 메모:\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

int main() {

    int choice;

    while (1) {
        printf("\n--- 메모장 ---\n");
        printf("1. 메모 쓰기\n");
        printf("2. 메모 읽기\n");
        printf("3. 종료\n");
        printf("선택: ");
        scanf_s("%d", &choice);
        getchar(); // 개행 문자 제거

        switch (choice) {
        case 1: write_note(); break;
        case 2: read_note(); break;
        case 3: exit(0);
        default: printf("잘못된 선택\n");
        }
    }

    return 0;
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
