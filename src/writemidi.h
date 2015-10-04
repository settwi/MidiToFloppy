#ifndef ___WRITEMIDI_H
#define ___WRITEMIDI_H

//#include <regex.h>
#include <stdio.h>
#include <stddef.h>
#include "die.h"
#include "midiinfo.h"
#include "notelist.h"

void writeMidi(MidiInfo *, const char *);

#endif
