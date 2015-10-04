#include "readmidi.h"

MidiInfo *readMidi(FILE *mf, FILE *out, FILE *lf)
{
    MidiInfo *mi = malloc(sizeof(MidiInfo));

    // Can't exactly die, because struct hasn't been initialized...
    if (!mi) exit(EXIT_FAILURE);

    MidiInfo_init(mf, lf, out, mi);

    uint8_t buf[4] = { 0 };

    // read header length (6 bytes)
    fread(buf, 4, 1, mi->mf);

    // Read filemode
    fread(buf, 2, 1, mi->mf);
    mi->fileMode = buf[1];
    if (mi->fileMode == 2)
        die(mi, "Cannot work with format 2 MIDI files.");

    // Read number of tracks
    fread(buf, 2, 1, mi->mf);
    mi->numTracks = bytesTo16(buf[0], buf[1]);
    // Contains info on delta-times.
    
    // Pulses per QN
    fread(buf, 1, 2, mi->mf);
    mi->PPQN = bytesTo16(buf[0], buf[1]);    
    mi->tickTime = mi->usecsPerQN / mi->PPQN;

  /*if (mi->PPQN & 0x8000)
        fprintf(stderr, "Cannot currently read SMPTE format files.");
        readSMPTE(mi)
    else */
    readTicks(mi);

    return mi;
}
