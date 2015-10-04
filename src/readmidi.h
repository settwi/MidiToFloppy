#ifndef ___MIDIREAD_H
#define ___MIDIREAD_H

#include <stdint.h>
#include <stdio.h>
#include "die.h"
#include "midiinfo.h"
#include "readticks.h"


// Combine 2 byte vals into one uint16_t.
#define bytesTo16(msb, lsb) ((uint16_t)(msb) << 8) | ((uint16_t)(lsb) & 0xFF)

MidiInfo *readMidi(FILE *, FILE *, FILE *);


#endif
