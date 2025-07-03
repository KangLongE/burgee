#ifndef NOTE_H
#define NOTE_H

#define MAX_INDEX 1024
#define MAX_NOTE 124

typedef struct note_list {
    char note_name[MAX_INDEX];
    int num;
}nl;

nl* check_note();
int create_note(char* name);
#endif
