#include "notelist.h"

NoteList *NoteList_add(NoteList *nl, uint8_t note, size_t dt)
{
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
/*
NoteList *NoteList_firstOn(NoteList *nl)
{
	if (!nl) return NULL;
	do {
		if (nl->length == 0) return nl;
	} while ((nl = nl->next));
	return NULL;
}
*/
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
	// Dereference double-pointer
	NoteList *c = *nl;
	while (c) {
		toDel = c;
		c = c->next;
		free(toDel);
	}
	*nl = NULL;
}

/* UNUSED.
NoteList *NoteList_del(NoteList *nl, NoteList *elem)
{
	if (!elem) return NULL;
	
	// Go through list until the next one is the
	// one we're looking for
	while (nl->next && nl->next != elem)
		nl = nl->next;

	// Reached end of list and didn't find element
	if (!nl->next) return NULL;

	// Keep a reference to the one we're deleting
	NoteList *toDel = nl->next;
	// Remove element from list
	nl->next = nl->next->next;
	// Deallocate element
	free(toDel);

	// return one before added
	return nl;
}
*/
