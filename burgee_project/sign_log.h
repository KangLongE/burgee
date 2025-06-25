
#define _MAX_INDEX 1024
#ifndef SLOG_H
#define SLOG_H

extern int success;

struct User {
    char name[MAX_INDEX];
    int password[4];
};

void signup(void);
void login(void);

#endif
