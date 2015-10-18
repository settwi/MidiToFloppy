#include "notelist.h"

NoteList *NoteList_add(NoteList *nl, uint8_t note, size_t dt)
{
    // Get to the last allocated element
    while (nl && nl->next && (nl = nl->next))
        ;

    if (nl) {
        nl->next = malloc(sizeof(NoteList));
        if (!nl->next) return NULL;
        nl = nl->next;
    }
    else
        nl = malloc(sizeof(NoteList));
    
    if (!nl) return NULL;

    nl->note = note;
    nl->channel = (uint8_t)-1;
    nl->DT = dt;
    nl->length = 0;
    nl->accessed = false;
    nl->next = NULL;

    return nl;
}

NoteList *NoteList_insert(NoteList *b, uint8_t note, size_t length, uint8_t channel)
{
    if (!b) return NULL;
    NoteList *after = b->next;
    NoteList *toAdd = malloc(sizeof(NoteList));
    if (!toAdd) return NULL;

    toAdd->note = note;
    toAdd->length = length;
    toAdd->channel = channel;

    b->next = toAdd;
    toAdd->next = after;
    return toAdd;
}

NoteList *NoteList_insertBefore(NoteList *b, uint8_t note, size_t length, uint8_t channel)
{
    if (!b) return NULL;
    NoteList *before = malloc(sizeof(NoteList));
    
    before->note = note;
    before->channel = channel;
    before->length = length;
    before->next = b;
    
    return before;
}

NoteList *NoteList_find(NoteList *nl, uint8_t note)
{
    if (!nl) return NULL;
    do {
        if (nl->note == note && !nl->accessed) {
            nl->accessed = true;
            return nl;
        }
    } while ((nl = nl->next));

    return NULL;
}

NoteList *NoteList_last(NoteList *nl)
{
    while (nl && nl->next && (nl = nl->next))
        ;
    return nl;
}

uint8_t NoteList_maxChannel(NoteList *nl)
{
    if (!nl) return (uint8_t)-1;
    uint8_t max = 0;
    do {
        if (nl->channel > max)
            max = nl->channel;
    } while ((nl = nl->next));

    return max;
}

void NoteList_print(NoteList *nl, FILE *f)
{
    fprintf(f, "\n*Printing NoteList:\n");
    size_t i = 0;
    if (!nl) return;
    do {
        fprintf(f,
               "Note %zu: %" PRIu8 "\n"
               "Length: %zu\n"
               "Channel / drive: %" PRIu8 "\n",
               i, nl->note, nl->length, nl->channel);
    } while(i++, (nl = nl->next));
    printf("\n");
}

void NoteList_destroy(NoteList **nl)
{
    if (!*nl) return;
    NoteList *toDel;
    // Dereference double-pointer;
    // makes it easier to do operations
    NoteList *cur = *nl;
    while (cur) {
        toDel = cur;
        cur = cur->next;
        free(toDel);
    }
    *nl = NULL;
}
