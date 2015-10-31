#ifndef ___NOTELIST_H
#define ___NOTELIST_H

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NUMDRIVES 4

typedef struct NoteList {
    bool accessed;
    uint8_t note;
    uint8_t channel;
    size_t DT;
    size_t length;
    struct NoteList *next;
} NoteList;

NoteList *NoteList_add(NoteList *, uint8_t, size_t);
NoteList *NoteList_insert(NoteList *, uint8_t, size_t, uint8_t);
NoteList *NoteList_insertBefore(NoteList *, uint8_t, size_t, uint8_t);
NoteList *NoteList_find(NoteList *, uint8_t);
NoteList *NoteList_last(NoteList *);
uint8_t NoteList_maxChannel(NoteList *);
void NoteList_print(NoteList *, FILE *);
void NoteList_destroy(NoteList **);

#endif
