

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "sign_log.h"


int signup(char * name, int * password)
{

    FILE* fp;
    fp = fopen("UserData.txt", "w, ccs=UTF-8");
    // UserData.txt ���� ����

    if (fp == NULL) {
        perror("���� ���� ����\n");
        return 0;
    }

    // UserData.txt ���Ͽ� �̸� �Է�
    fprintf(fp, "name: %s", name);

    fprintf(fp, "password: ");
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d", password[i]);
        if (i < 3) {
            fprintf(fp, "-");
        }
    }
    fprintf(fp, "\n");
    // UserData.txt ���Ͽ� ��й�ȣ �Է�



    fclose(fp);

    printf("���Ͽ� ���� �Ϸ�");
    return 1;
}
