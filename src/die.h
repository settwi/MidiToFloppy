#ifndef ___DIE_H
#define ___DIE_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "midiinfo.h"

void die(MidiInfo *mi, const char *msg);

#endif
