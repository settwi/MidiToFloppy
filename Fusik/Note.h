#ifndef ___NOTE_H
#define ___NOTE_H

#include <Arduino.h>
#include <stdint.h>


typedef struct Note {
  unsigned int freq;
  float beats;
} Note;

typedef struct MidiNote {
  uint16_t freq;
  uint64_t length;
} MidiNote;

#endif
