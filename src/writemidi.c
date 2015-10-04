#include "writemidi.h"

// Maybe we should just print "C3" instead of stupid macros
void writeMidi(MidiInfo *mi, const char *name)
{
    if (!name)
        die(mi, "Supply a valid name");
    if (!mi->nl)
        die(mi, "No nl to print");
    // NoteList_print(mi->nl, stdout);

    const char *notes[] = {
        "C", "CS", "D", "DS", "E",
        "F", "FS", "G", "GS", "A",
        "AS", "B"
    };

	fprintf(mi->out, "// Format is: note, length, channel\n\n");
	fprintf(mi->out, "struct MidiNote %s[] = {", name);
	size_t i = 0;
	NoteList *nl = mi->nl;
	if (!nl) die(mi, "Invalid notelist");
	do {
		if (i % 2 == 0) fprintf(mi->out, "\n\t");

		fprintf(mi->out, "{ %s%d, %zu, %" PRIu8 " }, ",
			    notes[nl->note % 12], nl->note / 12 - 1,
                nl->length * mi->tickTime, nl->channel);
	} while(++i, (nl = nl->next));
	fprintf(mi->out, "\n\t{ DONE, (size_t)-1, (uint8_t)-1 }");
	fprintf(mi->out, "\n}\n");
}
