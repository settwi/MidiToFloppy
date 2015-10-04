#include "die.h"

void die(MidiInfo *mi, const char *msg)
{
    if (errno)
        perror(msg);
    else
        fprintf(stderr, "%s\n", msg);
    fprintf(mi->lf, "Fatal error: %s\n", msg);
    if (mi->mf) fclose(mi->mf);
    if (mi->out) fclose(mi->out);
    if (mi->lf) fclose(mi->lf);
    if (mi) free(mi);
    exit(EXIT_FAILURE);
}
