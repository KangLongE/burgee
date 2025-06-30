#ifndef NOTE_H
#define NOTE_H

typedef struct note_list {
    char note_name[MAX_INDEX];
    int num;
}nl;

nl* check_note();
int create_note(char* name);
#endif
