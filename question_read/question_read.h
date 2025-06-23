#pragma once
#define MAX_INDEX 1024

#ifndef QR_LIB_H
#define QR_LIB_H

typedef struct question {

    char question[2][MAX_INDEX];
    // 문제 2줄

    char options[5][MAX_INDEX];
    // 보기 5줄

    int indices[5] = { 0, 1, 2, 3, 4 };
    // 섞인 보기 index

    int correct_answer;
    // 각 문제 정답


} N1;

void shuffle(int* arr, int size);
N1* question_print(int n);
int* correct_if(N1*, int*, int);

#endif