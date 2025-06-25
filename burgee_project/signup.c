

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024

#include <stdio.h>
#include "sign_log.h"


void signup(void)
{
    struct User user;

    FILE* fp;
    fp = fopen("UserData.txt", "w");
    // UserData.txt ���� ����

    if (fp == NULL) {
        printf("���� ���� ����\n");
        return 1;
    }


    printf("�̸��� �Է��ϼ���: ");

    fgets(user.name, sizeof(user.name), stdin);
    // UserData.txt ���Ͽ� �̸� �Է�
    fprintf(fp, "name: %s", user.name);

    printf("\n��й�ȣ�� 4�ڸ� ���ڷ� �Է��ϼ���: ");
    for (int i = 0; i < 4; i++) {

        scanf_s("%d", &user.password[i]);

        if (user.password[i] < 0 || user.password[i] > 9) {
            printf("�߸��� �Է��Դϴ�. 0���� 9 ������ ���ڸ� �Է��ϼ���.\n");
            i--;
        }
    }


    fprintf(fp, "password: ");
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d", user.password[i]);
        if (i < 3) {
            fprintf(fp, "-");
        }
    }
    fprintf(fp, "\n");
    // UserData.txt ���Ͽ� ��й�ȣ �Է�



    fclose(fp);

    printf("���Ͽ� ���� �Ϸ�\n");
    return 0;
}
