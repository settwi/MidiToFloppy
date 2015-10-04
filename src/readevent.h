#ifndef ___READEVENT_H
#define ___READEVENT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include "die.h"
#include "midiinfo.h"
#include "readints.h"
#include "notelist.h"

// For information on these magic numbers,
// consult the official MIDI specifications.

// Meta
#define CHANNEL 0x20
#define TIMESIG 0x58
#define TICKTIME 0x51
#define KEYSIG 0x59

// Other MIDI messages
#define NOTEOFF 0x80
#define NOTEON 0x90
#define SYSEXBEG 0xF0
#define SYSEXEND 0xF7

uint8_t *readEvent(uint8_t, uint8_t *, bool, MidiInfo *);
int8_t driveActivate(NoteList *);
int8_t driveFree(NoteList *);

#endif
