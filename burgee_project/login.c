

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024

#include <stdio.h>
#include <string.h>
#include "sign_log.h"

// �α��� ��� ����

int success = 0;
// �α��� ���� ���θ� ��Ÿ���� ���� ����



void login(char * name, int * password){
//login_print.c �κ��� ȣ��  [sign_log.h]

//name[MAX_INDEX]
//password[4]

    struct User user;
    //�Է� ���� ���� ������ ����ü  [sign_log.h]

	strcpy(user.name, name);
    //�Է� ���� ���� �� �ֱ�

    for (int i = 0; i < 4; i++) {
        user.password[i] = password[i];
	}
    // �Է� ���� �н����� �� �ֱ�


    struct User readuser;
    //���Ͽ��� ���� ���� ������ ����ü    [sign_log.h]

    FILE* fp = fopen("UserData.txt", "r");
	// ���� ����

    if (fp == NULL) {
        printf("���� ���� ����\n");
        exit(1);
    }

    
    // ���Ͽ��� ������ �б�

    char nameLine[MAX_INDEX];
    //���� �̸� ���� ��
    char passwordLine[MAX_INDEX];
    //���� ��й�ȣ ���� �� 

    fgets(nameLine, sizeof(nameLine), fp); // name �� �б�
    fgets(passwordLine, sizeof(passwordLine), fp); // password �� �б�

    sscanf_s(nameLine, "name: %[^\n]", readuser.name, MAX_INDEX); // ���Ͽ��� �̸� ����
    sscanf_s(passwordLine, "password: %d-%d-%d-%d",
        &readuser.password[0], &readuser.password[1],
        &readuser.password[2], &readuser.password[3]);
    // ���Ͽ��� ��й�ȣ ����

    // ��
    int match = 0;
    if (strcmp(user.name, readuser.name) == 0) {
        match = 1;
        for (int i = 0; i < 4; i++) {
            if (user.password[i] != readuser.password[i]) {
                match = 0;
                break;
            }
        }

        if (match) {
            success = 1;
        }
        else {
            success = -2;
        }
    }
    else {
        success = -1;
    }
    // ���Ͽ� ����� ����� �̸��� ��й�ȣ�� ���Ͽ� �α��� ���� ���� ���

    fclose(fp);
}