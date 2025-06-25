

#define MAX_INDEX 1024

#define ML 256
#define MAX_LOG 10
#ifndef QR_LIB_H
#define QR_LIB_H

extern double point;

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
    double point;
    char date[20];
} log;

typedef struct pline {
    char header1[ML]; // name
    char header2[ML]; // password
	char all_p[ML]; // ��ü ����Ʈ
    char logs[MAX_LOG][ML]; // point ����
    int log_count;
} pl;

void shuffle(int* arr, int size);
N1* question_print(int n);
int* correct_if(N1* c, int* un, int n);
void save_point(int point);
void ranking();
#endif