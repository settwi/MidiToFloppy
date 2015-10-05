#include "writemidi.h"

void writeMidi(MidiInfo *mi, const char *name)
{
    if (!name)
        die(mi, "Supply a valid name");
    if (!mi->nl)
        die(mi, "No nl to print");

    uint8_t maxChannel = NoteList_maxChannel(mi->nl);

    const char *notes[] = {
        "C", "CS", "D", "DS", "E",
        "F", "FS", "G", "GS", "A",
        "AS", "B"
    };

    fprintf(mi->out, "// Format is: note, length, channel\n\n");
    
    for (uint8_t drive = 0; drive < maxChannel + 1; ++drive) {
        fprintf(mi->out,
                "struct MidiNote %s%" PRIu8 "[] = {",
                name, drive);

        size_t i = 0;
        NoteList *nl = mi->nl;

        do {
            if (i % 2 == 0) fprintf(mi->out, "\n\t");

            if (nl->channel == drive)
                fprintf(mi->out, "{ %s%" PRIu8 ", %zu, %" PRIu8 " }, ",
                        notes[nl->note % 12],
                        (uint8_t)(nl->note / 12 - 1),   // Suppress those warnings!
                        nl->length * mi->tickTime, nl->channel);
            
            else if (drive != 0)
                fprintf(mi->out, "{ REST, %zu, REST }, ",
                        nl->length * mi->tickTime);
            else
                continue;

        } while(++i, (nl = nl->next));
        
        fprintf(mi->out, "\n\t{ DONE, (size_t)-1, (uint8_t)-1 }");
        fprintf(mi->out, "\n}\n");
    }
}
