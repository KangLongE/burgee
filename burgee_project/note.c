
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
    int save = 0;

    while (1) {
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'a') save = 1;
        if (save) break;
        // HTML에서 저장 신호를 받으면 종료
        fputs(input, fp);
    }

    fclose(fp);
    printf("메모 저장 완료!\n");
}

void fix_note() {

    int save = 1;
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


