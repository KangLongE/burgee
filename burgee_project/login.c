

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024

#include <stdio.h>
#include <string.h>
#include "sign_log.h"

int success = 0; // �α��� ���� ���θ� ��Ÿ���� ���� ����

void login(void){

    struct User user;
    struct User readuser;

    FILE* fp = fopen("UserData.txt", "r");

    if (fp == NULL) {
        printf("���� ���� ����\n");
        exit(1);
    }

    printf("login\n\n");
    // ����� �Է�
    printf("�̸��� �Է��ϼ���: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';
    // ����ڰ� �̸� �Է�

    printf("��й�ȣ�� 4�ڸ� ���ڷ� �Է��ϼ��� (�� ���� �Է� �� Enter): ");
    for (int i = 0; i < 4; i++) {
        scanf_s("%d", &user.password[i]);

        if (user.password[i] < 0 || user.password[i] > 9) {
            printf("�߸��� �Է��Դϴ�. 0���� 9 ������ ���ڸ� �Է��ϼ���.\n");
            i--;
        }
        // ����ڰ� ��й�ȣ �Է�
    }


    // ���Ͽ��� ������ �б�
    char nameLine[MAX_INDEX];
    char passwordLine[MAX_INDEX];

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
            printf("�α��� ����!\n");
            success = 1;
        }
        else {
            printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n");
            success = 0;
        }
    }
    else {
        printf("�̸��� ��ġ���� �ʽ��ϴ�.\n");
        success = 0;
    }
    // ���Ͽ� ����� ����� �̸��� ��й�ȣ�� ���Ͽ� �α��� ���� ���� ���

    fclose(fp);
}