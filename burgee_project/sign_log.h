
#define _MAX_INDEX 1024
#ifndef SLOG_H
#define SLOG_H

extern int success;

typedef struct User {
    char name[MAX_INDEX];
    int password[4];
} User;

void signup(void);
void login(char* name, int* password);
#endif
