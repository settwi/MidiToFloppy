#include "writemidi.h"

NoteList *isolateDrive(NoteList *nl, uint8_t drive)
{
    if (!nl)
        die(NULL, "Cannot isolate drive (no notelist)");

    NoteList *t = nl,
             *base = NULL,
             *cur = NULL;

    // March through the list and make a SEPARATE list containing
    // only the notes with channel == drive
    do {
        if (t->channel == drive) {
            if (!base) {
                base = NoteList_add(base, 0, 0);
                cur = base;
            }
            else
                cur = NoteList_add(base, 0, 0);
            if (!cur)
                return NULL;
            *cur = *t;
            cur->next = NULL;
        }
    } while ((t = t->next));
    t = base;
    bool first = true;
    size_t restTime = 0;
    do {
        restTime = 0;
        if (t->next) {
            if (first) {
                first = false;
                if (t->DT != 0)
                    restTime = t->DT;
                base = NoteList_insertBefore(base, 0, restTime, drive);
            }
            else {
                restTime = t->next->DT - (t->DT + t->length);
                if (restTime)
                    t = NoteList_insert(t, 0, restTime, drive);
            }
        }
    } while ((t = t->next));

    return base;
}

void writeMidi(MidiInfo *mi, const char *name)
{
    if (!name)
        die(mi, "Supply a valid name (writeMidi)");
    if (!mi->nl)
        die(mi, "No nl to print (writeMidi)");

    uint8_t maxChannel = NoteList_maxChannel(mi->nl);
    const char *notes[] = {
        "C", "CS", "D", "DS", "E",
        "F", "FS", "G", "GS", "A",
        "AS", "B"
    };

    fprintf(mi->out,
            "#ifndef ___%s_H\n"
            "#define ___%s_H\n\n"
            "#include <stdint.h>\n"
            "#include \"midinote.h\"\n\n"
            "// Format is: note, length\n\n"
            "const uint8_t maxChannel = %" PRIu8 ";\n\n",
            name, name, maxChannel);

    for (uint8_t drive = 0; drive < maxChannel + 1; ++drive) {
        fprintf(mi->out,
                "const uint32_t PROGMEM %s%" PRIu8 "[] = {",
                name, drive);

        NoteList *nl = isolateDrive(mi->nl, drive);
        if (!nl) die(mi, "Cannot isolate drive");

        size_t i = 0;

        do {
            if (i % 2 == 0) fprintf(mi->out, "\n\t");

            if (nl->note)
                fprintf(mi->out, "%s_%" PRIu8 ", %zu,\t",
                        notes[nl->note % 12],
                        (uint8_t)(nl->note / 12 - 1),   // Suppress those warnings!
                        nl->length * mi->tickTime);
            else
                fprintf(mi->out, "REST, %zu,\t\t",
                        nl->length * mi->tickTime);

        } while(++i, (nl = nl->next));
        
        NoteList_destroy(&nl);

        fprintf(mi->out, "\n\tDONE, DONE");
        fprintf(mi->out, "\n};\n");
    }

    // Make final array. E.g., MidiNote **
    fprintf(mi->out,
            "\nconst uint32_t PROGMEM *const %s[] = { ", name);

    for (uint8_t drive = 0; drive < maxChannel + 1; ++drive)
        fprintf(mi->out, "%s%" PRIu8 ", ", name, drive);

    // Fill remaining spot(s) with NULL so array is
    // NULL-terminated and 4 in length.
    for (uint8_t drive = 0; drive < 3 - maxChannel; ++drive)
        fprintf(mi->out, "nullptr, ");

    fprintf(mi->out,
            "};\n\n"
            "#endif");
}
