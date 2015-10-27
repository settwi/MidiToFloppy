#ifndef ___NOTE_H
#define ___NOTE_H

#include <Arduino.h>
#include <stdint.h>


typedef struct Note {
  uint16_t freq;
  float beats;
} Note;

typedef struct MidiNote {
  uint32_t freq;
  uint32_t len;
} MidiNote;

#endif
