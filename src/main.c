#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "die.h"
#include "midiinfo.h"
#include "notelist.h"
#include "readmidi.h"
#include "readints.h"
#include "readticks.h"
#include "writemidi.h"

// This program may work incorrectly on a big-endian computer.

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stdout, "USAGE: ./mtof <path to midi> <name of output array>\n");
        exit(EXIT_FAILURE);
    }

    char *logName = malloc(sizeof(char) * (strlen(argv[1]) + 5));
    char *outName = malloc(sizeof(char) * (strlen(argv[1]) + 3));
    strcpy(logName, argv[1]);
    strcpy(outName, argv[1]);
    strcpy(logName + strlen(argv[1]), ".log");
    strcpy(outName + strlen(argv[1]), ".h");

    FILE *lf = fopen(logName, "wb");
    if (!lf)
        die(NULL, "Died creating logfile");
    
    fprintf(lf, "MIDI to Floppy Decode Log for %s\n", argv[1]);
    FILE *mf = fopen(argv[1], "rb");
    if (!mf)
        die(NULL, "Died creating midifile"); 
    
    FILE *out = fopen(outName, "wb");
    if (!out)
        die(NULL, "Died creating outfile");
    
    uint8_t buf[4] = { 0 };
    fread(buf, 4, 1, mf);   
    
    if (strncmp((char*)buf, "MThd", 4))
        die(NULL, "Not a MIDI file");

    MidiInfo *mi = readMidi(mf, out, lf);
    if (!mi)
        die(mi, "Creating MidiInfo");
    
    writeMidi(mi, argv[2]);
    NoteList_destroy(&mi->nl);

    if (mi) free(mi);
    if (logName) free(logName);
    if (outName) free(outName);
    if (lf) fclose(lf);
    if (mf) fclose(mf);
    if (out) fclose(out);

    return 0;
}
