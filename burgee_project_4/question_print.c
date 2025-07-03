#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#define ML 256
#define MAX_LOG 10
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


double point = 0;

typedef struct question {

    char question[2][MAX_INDEX];
    // ���� 2��

    char options[5][MAX_INDEX];
    // ���� 5��

    int indices[5];
    // ���� ���� index

    int correct_answer;
    // �� ���� ����


} N1;

typedef struct Log {
    char id[50];
    // ����Ʈ ��� ID & ��ŷ��
    // �׳� �̸�

    double point;
    // ����Ʈ ���

    char date[20];
    // ����Ʈ ��� ��¥
} log;

typedef struct pline {
    char header1[ML]; // name
    char header2[ML]; // password
    char all_p[ML]; // ��ü ����Ʈ
    char logs[MAX_LOG][ML]; // point ���� 10��
    int log_count;
} pl;

void shuffle(int* arr, int size);
N1* question_suffle(int n);
int* correct_if(int* un, int n);
void save_point(double point);
void ranking();


//���� ��� ����
//������ ����Ϸ��� �� ������ ����
//����Ʈ ����, ��ŷ ���, ��� ��±��� �� ���� ����

void main(int argc, char ** argv) {
// argc: ���� ����, argv: ���� �迭

    int num = atoi(argv[1]);
	// ���� ���� (1 ~ 3)

    N1* carry = NULL;
	// ������ ���� ����ü ������


    if (argc == 2) {
// ���ڰ����� 1�̸� ���� ��� ���

        carry = question_suffle(num * 10);
        // question_logic.c (question_data.h)
        // ������ ���� carry����ü �����ͷ� ����Ŵ

            if (num >= 1 && num <= 3) {

                for (int i = 0; i < num * 10; i++) {

                    printf("Q:%s\nQ:%s\n", carry[i].question[0], carry[i].question[1]);
					fflush(stdout);
                    // ���� ��� (���� ��ȣ, ���� ����)

                    for (int k = 0; k < 5; k++) {
                        printf("A:%s\n", carry[i].options[carry[i].indices[k]]);
                        fflush(stdout);
                        // ���� ���� ��� (1~5�� ��ȣ �ű��)
                    }

                }

                FILE* fp;
                fp = fopen("correct.txt", "w");

                if (fp == NULL) {
                    printf("E:%d\n", 0);  //���� ��ȣ [0]
                    fflush(stdout);
                    perror("���� ���� ���� ����\n");
                    exit(1);
                }

                for (int i = 0; i < num * 10; i++) {
                    fprintf(fp, "%d ", carry[i].correct_answer);
                }
                fclose(fp);
            }

            free(carry);

    }
    else {
// ���ڰ����� ������ �̻��̸� ���� Ȯ�� ���

        int* user_answer = (int*)malloc(sizeof(int) * (num * 10));

        // ����ڰ� �Է��� ������ ������ �迭
        

        if (argc < num * 10 + 2) {
            printf("E:%d\n", 0);  //���� ��ȣ [0]
            fflush(stdout);
            perror("���� ���� ����\n");
            free(user_answer);
            free(carry);
            exit(1);
        }

        for (int i = 0; i < num * 10; i++) {
			user_answer[i] = atoi(argv[2 + i]);
            // ���� ��ȣ 1�� ���� ����
			// 2�����ʹ� ����ڰ� �Է��� ����
        }

        correct_if(user_answer, num * 10);
		// question_logic.c     (question_data.h)
		// ���� Ȯ�� �Լ� ȣ��
        
        save_point(point);
        // point.c      (question_data.h)
        // ���� Ȯ�� �� ����Ʈ ����
		

        point = 0;
        // ���� Ǯ�� �� ���� �ʱ�ȭ

        ranking();
		// ranking.c    (question_data.h)
		// ��ŷ ������Ʈ


        free(user_answer);
    }

}


int* correct_if(int* un, int n) {
    // un: ����ڰ� �Է��� ���� �迭
    // n: ���� ����

    int* true_answer = (int*)malloc(sizeof(int) * n);
    // true_answer: ���� ���θ� ������ �迭 (1: ����, 0: Ʋ��)

    if (true_answer == NULL) {
        printf("E:%d\n", 0);  //���� [0]
        perror("�޸� �Ҵ� ����\n");
        exit(1);
    }

    FILE* fp;
    fp = fopen("correct.txt", "r");

    if (fp == NULL) {
        printf("E:%d\n", 0);   //���� [0]
        fflush(stdout);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        // ���� ������ŭ �ݺ�

        int correct;
        if (fscanf(fp, "%d", &correct) != 1) { // ���Ͽ��� ���� �б�
            printf("E:%d\n", 0); //���� ��ȣ [0]
            perror("���� ���� �б� ����\n");
            exit(1);
        }

        if (un[i] == correct) {

            true_answer[i] = 1;
            printf("R:%d\n", 1);  //������ [1]
            fflush(stdout);
            point++;
        }
        else {
            true_answer[i] = 0;
            printf("R:%d\n", 0);  //�� ������ [0]
            fflush(stdout);
        }
        // ���� �� (�����̸� 1, Ʋ���� 0 ����)

    }


    printf("S:%d\n", (int)point);   //    [���� �� ����]
    fflush(stdout);
    printf("P:%.4f%%\n", (float)point / n * 100); //  [���� �����]
    fflush(stdout);
    // ���� ��� (���� ���� ��, �� ���� ��, �����)

    point = (point / n) * 100;
    // ����Ʈ ����

    return true_answer;
}


N1* question_suffle(int n) {
    // n: ���� ���� (10 ~ 30)

    N1* q = (N1*)malloc(sizeof(N1) * n);
    // ���� ����ü �迭 ���� �Ҵ�  [�޸� ���� �Ƴ��� ����]


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            q[i].indices[j] = j;
        }
    }
    // ���� �迭 �ʱ�ȭ

    srand((unsigned int)time(NULL));

    FILE* fp;
    fp = fopen("question.txt", "r");
    // ������ ����� ���� ����

    if (fp == NULL) {
        perror("���� ���� ����");
        exit(1);
    }

    int i = 0;
    int* number = (int*)malloc(sizeof(int) * n);
    // ���� ��ȣ ���� �迭 ���� �Ҵ�    [�޸� ���� �Ƴ��� ����]

    while (i < n) {

        int random = rand() % 30; // ���Ͽ� �ִ� �� ���� �� �Է�
        int nk = 1;

        for (int j = 0; j < i; j++) {
            if (number[j] == random) {
                nk = 0;
                break;
            }
        }
        // �ߺ� üũ


        if (nk) {
            number[i] = random;
            i++;
        }
        // �ߺ����� �ʴ� ���� ��ȣ ����
    }

    for (int i = 0; i < n; i++) {
        // ���� �� ��ŭ ��� �ݺ�

        rewind(fp);
        // ���� �����͸� ó������ �ǵ���

        char line[MAX_INDEX];
        // �� �پ� �б� ���� ����

        int target = number[i];
        // �������� ���õ� ���� ���� ��ȣ

        int start_line = target * 8;
        // ���� ��ȣ�� �ش��ϴ� �� ��ȣ ���
        // �ش� ���� ���� �� (������ 8��)

        int curr_line = 0;
        // ���� �� ��ȣ
        int correct_idx = -1;
        // ���� �ε��� ��ȣ

        // ����, ����, ���� �б�
        while (fgets(line, sizeof(line), fp)) {
            // �� �پ� �а� line�� ����

            line[strcspn(line, "\n")] = '\0';
            // ���� ���� ����

            if (curr_line == start_line) strcpy(q[i].question[0], line);
            // line�� start_line�� ������
            // ���� �б� 1
            else if (curr_line == start_line + 1) strcpy(q[i].question[1], line);
            // line�� start_line + 1�� ������    [�ι�° ��]
            // ���� �б� 2
            else if (curr_line >= start_line + 2 && curr_line < start_line + 7) {
                // line�� ���� �ΰ��� �а� �����б� ������     [3���� ~ 7���� ��]
                // ���� ���� 2~6�� �б�    [�� �ټ� ��]
                strcpy(q[i].options[curr_line - start_line - 2], line);
            }
            else if (curr_line == start_line + 7) {
                // ����, ���� �а� ������ �� �б�   [8��° ��]
                correct_idx = atoi(line) - 1;
                // ���� �ε��� �б�
                break;
            }
            curr_line++;
            // ���� �� ��ȣ ����
        }

        shuffle(q[i].indices, 5);
        // ���� ����

        int new_correct = -1;
        // ���ο� ���� �ε���

        for (int k = 0; k < 5; k++) {
            if (q[i].indices[k] == correct_idx) {
                // ���� ���⿡�� ���� �ε��� ã��
                new_correct = k + 1;
                q[i].correct_answer = new_correct;
                // �ش� ������ ���� ���� (����� ���� 1~5�� ��ȣ �ű��)
                break;
            }
        }

    }

    free(number);
    // ���� �Ҵ�� ��ȣ �迭 ����

    fclose(fp);
    // ���� �ݱ�

    return q;
    // ���� ���� ����ü �迭 ��ȯ [carry ����ü �����ͷ� ����]

}


void shuffle(int* arr, int size) {
    //���� ����
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // 0���� i���� �� ���� �ε���
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}



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

    if (c2.all_p[0] == '\0') {
        strcpy(c2.all_p, "��ü ����Ʈ: 0\n");
        // ��ü ����Ʈ�� ��������� �ʱ�ȭ
    }
    else {

        total_p = atoi(c2.all_p + strcspn(c2.all_p, ":") + 1);
        // �� ����Ʈ ���� ���� �а�
        //��ü ����Ʈ ���� ����
        c2.all_p[strcspn(c2.all_p, "\n")] = '\0'; // ���� ���� ����
    }


    while (c2.log_count < MAX_LOG && fgets(c2.logs[c2.log_count], ML, file) != NULL) {
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

    //����Ʈ �� �ֱ�
    c1.point = point;

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

    file = fopen("UserData.txt", "w, ccs=UTF-8");
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
        
void ranking() {
    // ��ŷ�� �ҷ��ͼ� �����ϰ� �����ϴ� �Լ�
    // ����Ʈ�� �߰� �� ������ ȣ���

    pl c3;
    // pl ����ü ���� c3 ���� [pl <- pline` ����ü]

    double rank_p[10] = { 0 };
    // ��ŷ ����Ʈ �迭 �ʱ�ȭ

    c3.log_count = 0;
    // �α� ���� �ʱ�ȭ
    // 0 ~ 9���� 10��	[MAX_LOG]

    for (int i = 0; i < MAX_LOG; i++) {
        c3.logs[i][0] = '\0';
    }
    // logs �迭 �ʱ�ȭ

    FILE* file = fopen("UserData.txt", "r");
    // UserData.txt ���� ����

    if (file == NULL) {
        perror("���� ���� ����");
        exit(1);
    }

    printf("��ŷ�� �ҷ����� ��...\n");

    char line[ML];
    // �� �پ� �б� ���� ����	[12�ٱ��� ���� �� �ֵ��� ����]
    // ������ ����� ��� name, password

    // ���� 10���� ��ŷ ��Ͽ�
    // ��: "2025.06.05.12:00/eum : 10\n"

    char name[ML];
    // �г��� ����� ����

    while (fgets(line, ML, file) != NULL && c3.log_count < MAX_LOG + 2) {
        // ���Ͽ��� �� �پ� �б�

        if (c3.log_count >= 2) {
            // ��� �� ���� �����ϰ� ��ŷ ��� �б�

            if (strchr(line, '/') && strrchr(line, ':')) {
                // ��: "2025.06.05.12:00/eum : 10"

                char* slash = strchr(line, '/');
                // /eum �̸� ���� �غ�

                char* colon = strrchr(line, ':');
                // : 10 ����Ʈ ���� �غ�

                if (colon != NULL) {
                    double score = atof(colon + 1);
                    // ':' ���� ��ġ���� ���� ����
                    // : ����
                }

                if (slash && colon) {
                    // �̸� ����
                    slash++;  // '/' ���� ���ں���
                    char* end = strchr(slash, ' ');  // ���� �������� �г���
                    if (!end) continue;
                    int name_len = end - slash;
                    // �̸� ���� ���
                    if (name_len >= ML) name_len = ML - 1;
                    // ������ ũ�Ⱑ name�� ũ�⺸�� Ŭ �� �־
                    strncpy(name, slash, name_len);
                    // �̸� ����
                    name[name_len] = '\0';
                    // ���ڿ� ���� �� ���� �߰�


                    int score = atoi(colon + 1);
                    // :�� ������ ���� �б�	[���ڸ� ����]

                    // logs�� ���� ����
                    sprintf(c3.logs[c3.log_count - 2], "%s", name);
                    // �г��Ӹ� ����
                    rank_p[c3.log_count - 2] = score;
                    // rank_p�� ���� ����


                    if (c3.log_count >= MAX_LOG) break;
                    // �α� ������ �ִ�ġ�� �����ϸ� �ߴ�
                }
            }
        }
        c3.log_count++;
        // �α� ���� ����
    }

    fclose(file);

    char aemp[ML];
    // �ӽ� ���� aemp ����	[����� �ٲٱ� ����]
    double bemp;
    // �ӽ� ���� bemp ����	[����Ʈ �ٲٱ� ����]

    for (int i = 0; i < MAX_LOG; i++) {
        for (int j = i + 1; j < MAX_LOG; j++) {

            if (rank_p[i] < rank_p[j]) {
                // ��ŷ ����Ʈ ��
                // i��° ����Ʈ�� j��° ����Ʈ���� ������

                strcpy(aemp, c3.logs[i]);
                strcpy(c3.logs[i], c3.logs[j]);
                strcpy(c3.logs[j], aemp);
                //���� ���� ����Ʈ�� ���� ����� �����͸� ���� �ø�

                bemp = rank_p[i];
                rank_p[i] = rank_p[j];
                rank_p[j] = bemp;
                //���� ���� ����Ʈ�� ���� �ø�


            }
        }
    }

    file = fopen("ranking.txt", "w");
    // ��ŷ ���� ����

    if (file == NULL) {
        perror("���� ���� ����");
        exit(0);
    }

    for (int i = 0; i < MAX_LOG; i++) {
        if (c3.logs[i][0] != '\0') {
            fprintf(file, "%d) %s : %.4f\n", i + 1, c3.logs[i], rank_p[i]);
            // ��ŷ ���Ͽ� ���
        }

    }
    printf("��ŷ�� ranking.txt�� �����߽��ϴ�.\n");
    fclose(file);


}