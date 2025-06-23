#pragma once
#define MAX_INDEX 1024

#ifndef QR_LIB_H
#define QR_LIB_H

typedef struct question {

    char question[2][MAX_INDEX];
    // ���� 2��

    char options[5][MAX_INDEX];
    // ���� 5��

    int indices[5] = { 0, 1, 2, 3, 4 };
    // ���� ���� index

    int correct_answer;
    // �� ���� ����


} N1;

void shuffle(int* arr, int size);
N1* question_print(int n);
int* correct_if(N1*, int*, int);

#endif