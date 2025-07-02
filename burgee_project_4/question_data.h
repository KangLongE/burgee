

#define MAX_INDEX 1024
#define ML 256
#define MAX_LOG 10
#ifndef QR_LIB_H
#define QR_LIB_H

extern double point;

typedef struct question {

    char question[2][MAX_INDEX];
    // 문제 2줄

    char options[5][MAX_INDEX];
    // 보기 5줄

    int indices[5];
    // 섞인 보기 index

    int correct_answer;
    // 각 문제 정답


} N1;

typedef struct Log {
    char id[50];
	// 포인트 기록 ID & 랭킹용
    // 그냥 이름

    double point;
	// 포인트 기록

    char date[20];
	// 포인트 기록 날짜
} log;

typedef struct pline {
    char header1[ML]; // name
    char header2[ML]; // password
	char all_p[ML]; // 전체 포인트
    char logs[MAX_LOG][ML]; // point 내역 10출
    int log_count;
} pl;

void shuffle(int* arr, int size);
N1* question_suffle(int n);
int* correct_if(int* un, int n);
void save_point(double point);
void ranking();
#endif