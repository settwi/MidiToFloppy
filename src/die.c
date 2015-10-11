#include "die.h"

void die(MidiInfo *mi, const char *msg)
{
    if (errno)
        perror(msg);
    else
        fprintf(stderr, "%s\n", msg);
    if (mi && mi->lf)
        fprintf(mi->lf, "Fatal error: %s\n", msg);

    exit(EXIT_FAILURE);
}
