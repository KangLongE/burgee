
#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_note() {

    char note_name[MAX_INDEX];

    printf("�޸��� �̸��� �����ּ���.\n");
    scanf("%s", note_name);
    getchar();
    // ��Ʈ �̸��� �ۼ�

    sprintf(note_name, "%s.txt", note_name);
    // ���� �̸��� .txt Ȯ���ڸ� �߰�

    FILE* fp;

    fp = fopen(note_name, "r");
    // ������ �̹� �����ϴ��� Ȯ��
    if (fp != NULL) {
        fclose(fp);
        printf("�̹� �����ϴ� �޸��Դϴ�. ����ðڽ��ϱ�? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        getchar();
        // ����
        if (choice != 'y' && choice != 'Y') {
            return;
            // ����� ������ �Լ� ����
        }
    }

    printf("�޸� �����մϴ�.\n");
    // �޸� ����

    fp = fopen(note_name, "a");
    // ���� ���� �׸��� �ۼ�

    printf("�޸� �ۼ��ϼ���. 'a'�� �Է��ϸ� �����մϴ�.\n");
    char input[MAX_INDEX];
    int save = 0;

    while (1) {
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'a') save = 1;
        if (save) break;
        // HTML���� ���� ��ȣ�� ������ ����
        fputs(input, fp);
    }

    fclose(fp);
    printf("�޸� ���� �Ϸ�!\n");
}

void fix_note() {

    int save = 1;
    char note_name[MAX_INDEX] = { 0 };
    char note_nametxt[MAX_INDEX] = { 0 };

    printf("���� �̸� �Է�: ");
    scanf("%s", note_name);
    // ���� �̸� �Է�

    sprintf(note_nametxt, "%s.txt", note_name);
    // ���� �̸��� .txt Ȯ���ڸ� �߰�

    FILE* fp;
    fp = fopen(note_nametxt, "r+");
    // ���� ����

    if (fp == NULL) {
        printf("���� ����\n");
        printf("�޸� ���� �������ּ���.\n");
        return;
    }

    printf("�޸� �����մϴ�.\n");
    char line[MAX_INDEX];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    // HTML�� �ۼ��� �޸� ��� �� ����

    if (save) {
        printf("������ �����մϴ�.\n");
        fclose(fp);
    }
    // ���� ��ư�� Ŭ���ϸ� save�� ���� true�� ����
}


