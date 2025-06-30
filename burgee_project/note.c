
#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#define MAX_NOTE 124

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "note.h"
#include <Windows.h>


nl * check_note() {

    nl n[MAX_NOTE];

    n->num = 0;

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("C:\\note_file\\*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("디렉토리를 열 수 없습니다.\n");
        return 1;
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            strcpy(n[n->num].note_name, findFileData.dwFileAttributes);
            n->num++;
        }

    } while (FindNextFile(hFind, &findFileData) != 0);

    return n;

}


int create_note(char * name) {

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("C:\\note_file\\*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("디렉토리를 열 수 없습니다.\n");
        return 0;
    }


    char note_name[MAX_INDEX];

    strcpy(note_name, name);
    // 노트 이름을 작성

    FILE* fp;

    fp = fopen(".\\note_file\\%s.txt", "r", note_name);
    // 파일이 이미 존재하는지 확인

    if (fp == NULL) {
        fclose(fp);
    }
    else {
        return 0;
    }

    fp = fopen("%s.txt", "a", note_name);
    // 파일 생성

    fclose(fp);
    return 1;
}


