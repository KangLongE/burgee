// note.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_note() {

	char note_name[MAX_INDEX];

	printf("메모의 이름을 적어주세요.\n");
	scanf("%s", note_name);
    getchar();
    // 노트 이름을 작성

    sprintf(note_name, "%s.txt", note_name);
	// 파일 이름에 .txt 확장자를 추가

    FILE* fp;

    fp = fopen(note_name, "r");
	// 파일이 이미 존재하는지 확인
    if (fp != NULL) {
        fclose(fp);
        printf("이미 존재하는 메모입니다. 덮어쓰시겠습니까? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        getchar();
        // 선택
        if (choice != 'y' && choice != 'Y') {
            return;
			// 덮어쓰지 않으면 함수 종료
		}
    }

        printf("메모를 생성합니다.\n");
		// 메모 생성

    fp = fopen(note_name, "a");
    // 파일 생성 그리고 작성

	printf("메모를 작성하세요. 'a'를 입력하면 저장합니다.\n");
    char input[MAX_INDEX];
    bool save = false;

    while (1) {
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'a') save = true;
        if (save) break;
        // HTML에서 저장 신호를 받으면 종료
        fputs(input, fp);
    }

    fclose(fp);
    printf("메모 저장 완료!\n");
}

void fix_note() {

    bool save = true;
    char note_name[MAX_INDEX] = { 0 };
    char note_nametxt[MAX_INDEX] = { 0 };

    printf("파일 이름 입력: ");
	scanf("%s", note_name);
	// 파일 이름 입력

    sprintf(note_nametxt, "%s.txt", note_name);
	// 파일 이름에 .txt 확장자를 추가

    FILE* fp;
    fp = fopen(note_nametxt, "r+");
	// 파일 열기

    if (fp == NULL) {
        printf("파일 없음\n");
		printf("메모를 먼저 생성해주세요.\n");
		return;
    }

	printf("메모를 수정합니다.\n");
    char line[MAX_INDEX];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
	// HTML로 작성된 메모를 출력 및 수정

    if (save) {
        printf("파일을 저장합니다.\n");
        fclose(fp);
    }
	// 저장 버튼을 클릭하면 save로 받음 true면 저장
}

int main() {

    int choice;

    while (1) {
        scanf_s("%d", &choice);
        getchar();
        // HTML에서 선택

        switch (choice) {
        case 1: create_note(); break;
        // 생성 버튼 클릭
        case 2: fix_note(); break;
        // 기존에 있는 메모 버튼 클릭
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
