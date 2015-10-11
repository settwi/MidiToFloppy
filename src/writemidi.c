#include "writemidi.h"

NoteList *isolateDrive(NoteList *nl, uint8_t drive)
{
    if (!nl)
        die(NULL, "Cannot isolate drive");

    size_t previousDT = 0;
    NoteList *base = NULL,
             *cur = NULL,
             *last = NULL;

    do {
        if (nl->channel == drive) {

            /* This is the "rest" value.
             * E.g., "rest for x microseconds before the note,
             * unless the note is playing at the same time as another.
             */
            if (nl->DT != previousDT && drive != 0) {
                cur = NoteList_add(
                    base, 0, 0);
                if (!cur)
                    die(NULL, "Allocating a note (isolateDrive)");

                cur->length = previousDT - (last ? last->DT : 0);
                cur->channel = drive;

                // Point to first element, e.g. the rest one.
                if (!base)
                    base = cur;

                // Allocate actual note.
                cur = NoteList_add(base, nl->note, 0);
            }
            // More than one note playing at the same immediate time,
            // so allocate base by itself.
            else if (!base) {
                base = malloc(sizeof(NoteList));
                if (!base)
                    return NULL;
                cur = base;
            }
            else
                cur = NoteList_add(cur, 0, 0);

            // Copy values and point to NULL for next element
            *cur = *nl;
            cur->next = NULL;
            last = cur;
        }
        previousDT = nl->DT;

    } while ((nl = nl->next) != NULL);

    return base;
}

void writeMidi(MidiInfo *mi, const char *name)
{
    if (!name)
        die(mi, "Supply a valid name");
    if (!mi->nl)
        die(mi, "No nl to print");

    uint8_t maxChannel = NoteList_maxChannel(mi->nl);
    NoteList *nl = NULL;

    const char *notes[] = {
        "C", "CS", "D", "DS", "E",
        "F", "FS", "G", "GS", "A",
        "AS", "B"
    };

    fprintf(mi->out,
            "#include <stdint.h>\n\n"
            "// Format is: note, length\n\n"
            "const uint8_t maxChannel = %" PRIu8 "\n\n",
            maxChannel);

    for (uint8_t drive = 0; drive < maxChannel + 1; ++drive) {
        fprintf(mi->out,
                "struct MidiNote %s%" PRIu8 "[] = {",
                name, drive);

        size_t i = 0;

        nl = isolateDrive(mi->nl, drive);
        if (!nl)
            die(mi, "Cannot isolate drive (return)");

        do {
            if (i % 2 == 0) fprintf(mi->out, "\n\t");

            if (nl->note)
                fprintf(mi->out, "{ %s_%" PRIu8 ", %zu }, ",
                        notes[nl->note % 12],
                        (uint8_t)(nl->note / 12 - 1),   // Suppress those warnings!
                        nl->length * mi->tickTime);
            else
                fprintf(mi->out, "{ REST, %zu }, ",
                        nl->length * mi->tickTime);

        } while(++i, (nl = nl->next));
        
        fprintf(mi->out, "\n\t{ DONE, 0 }");
        fprintf(mi->out, "\n}\n");
        if (nl)
            NoteList_destroy(&nl);
    }
}
