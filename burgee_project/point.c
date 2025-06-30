

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "question_data.h"

#define ML 256
#define MAX_LOG 10


void save_point(double point) {
//question_print.c���� ȣ��  [question_data.h]
//point�� question_logic.c���� correct_if���� ��ȯ

    log c1;     //[question_data.h]
    //id[50]
    //point
    //date[20]

    pl c2;      //[question_data.h]
    //header1[ML]       name
    //header2[ML]       password
    //all_p[ML]         �� ����Ʈ ������ ���� ��
    //logs[MAX_LOG][ML] ����Ʈ ����
    //log_count         �α� ī��Ʈ

	double total_p = 0;
    // �� ����Ʈ ������ ���� ����

    for (int i = 0; i < MAX_LOG; i++) {
        c2.logs[i][0] = '\0';
    }
	// logs �迭 �ʱ�ȭ

    FILE* file = fopen("UserData.txt", "r");
    //���� �б�

    if (file == NULL) {
        perror("���� ���� ����");
		exit(1);
    }

    c2.log_count = 0;
    // ī��Ʈ �ʱ�ȭ

    // ��� �� �� �б�
    fgets(c2.header1, ML, file);    //name
    fgets(c2.header2, ML, file);    //password
    fgets(c2.all_p, ML, file);      //�� ����Ʈ

    if(c2.all_p[0] == '\0') {
        strcpy(c2.all_p, "��ü ����Ʈ: 0\n");
        // ��ü ����Ʈ�� ��������� �ʱ�ȭ
	}
    else {
        
		total_p = atoi(c2.all_p + strcspn(c2.all_p, ":") + 1);
        // �� ����Ʈ ���� ���� �а�
        //��ü ����Ʈ ���� ����
        c2.all_p[strcspn(c2.all_p, "\n")] = '\0'; // ���� ���� ����
	}

	
    while (c2.log_count < MAX_LOG&& fgets(c2.logs[c2.log_count], ML, file) != NULL) {
        c2.log_count++;
    }
    // ���� ����Ʈ ���� �б� (�ִ� 10��)

    fclose(file);
    //�б� ���� �ݱ�


    // ID ���� (header1����)
    // ��: "name: eum\n"
    sscanf(c2.header1, "name: %s", c1.id);

	// ��ü ����Ʈ ����
	total_p += point;
	sprintf(c2.all_p, "��ü ����Ʈ: %.4f\n", total_p);

    // ��¥ ����
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(c1.date, sizeof(c1.date), "%Y-%m-%d-%H:%M", tm_info);

    // �� �α� �����
    char new_log[ML];
    snprintf(new_log, ML, "%s/%s : %.4f\n", c1.date, c1.id, c1.point);
    //�� : 2025-06-05-12:30/eum 12.2222


    // logs �迭 �� ĭ�� �Ʒ��� �б� (�� �Ʒ� ������ �����)
    for (int i = MAX_LOG - 1; i > 0; i--) {
        strcpy(c2.logs[i], c2.logs[i - 1]);
    }
    strcpy(c2.logs[0], new_log); // �� �α׸� �� ���� �߰�

    file = fopen("UserData.txt", "w");
    //���� ����� ����
    //���� �ٽ� ����

    if (file == NULL) {
        perror("���� ���� ����");
		exit(1);
    }

	// ��� �� �ٰ� ��ü ����Ʈ ����
    fputs(c2.header1, file);
    fputs(c2.header2, file);
	fputs(c2.all_p, file);
	
    for (int i = 0; i < MAX_LOG; i++) {
        if (c2.logs[i][0] != '\0')
            fputs(c2.logs[i], file);
    }
    // �ִ� 10�� ������ ���

    fclose(file);
    //���� �ݱ�
}

