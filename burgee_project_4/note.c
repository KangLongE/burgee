
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "note.h"
#include <Windows.h>


nl * check_note() {

    nl *n = (nl*)malloc(sizeof(nl));
    if (n == NULL) {
        return NULL;
    }

    n[0].num = 0;

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(".\\note_file\\*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("E:%d\n", 0);
        fflush(stdout);
        free(n);
        return NULL;
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            strcpy(n[n[0].num].note_name, findFileData.cFileName);
            n[0].num++;
        }

    } while (FindNextFile(hFind, &findFileData) != 0);

    return n;

}


int create_note(char * name) {

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(".\\note_file\\*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        perror("디렉토리를 열 수 없습니다.\n");
        return 0;
    }


    char note_name[MAX_INDEX];

    sprintf(note_name, ".\\note_file\\%s.txt", name);
    // 노트 이름을 작성

    FILE* fp;
    
    fp = fopen(note_name, "r");
    // 파일이 이미 존재하는지 확인

    if (fp != NULL) {
        fclose(fp);
    }
    else {
        return 0;
    }

    fp = fopen(note_name, "a, ccs=UTF-8");
    // 파일 생성

    if (fp == NULL) {
        return 0;
    }

    fclose(fp);
    return 1;
}


