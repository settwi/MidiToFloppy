#ifndef ___MIDIINFO_H
#define ___MIDIINFO_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "notelist.h"

/*
 * This struct, logically, holds information
 * pertaining to the MIDI file being read,
 * including the files the program manipulates for 
 * logging, and outputting the floppy-readable
 * information.
 */

typedef struct MidiInfo MidiInfo;

void MidiInfo_init(FILE *, FILE *, FILE *, MidiInfo *);

struct MidiInfo {

    uint8_t fileMode;
    uint8_t channel;

    uint16_t divisions;
    uint16_t numTracks;
    uint16_t PPQN;

    uint32_t bpm;
    uint32_t currentDT;
    uint32_t usecsPerQN;
    uint32_t tickTime;

    size_t totalDeltaTime;

    float beatMultiplier;

    NoteList *nl;
    FILE *mf;
    FILE *lf;
    FILE *out;
};

#endif
