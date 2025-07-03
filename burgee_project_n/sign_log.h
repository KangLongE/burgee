
#define MAX_INDEX 1024
#ifndef SLOG_H
#define SLOG_H

extern int success;

typedef struct User {
    char name[MAX_INDEX];
    int password[4];
} User;

int signup(char * name, int * password);
int login(char* name, int* password);
#endif
