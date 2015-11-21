#ifndef ___NOTE_H
#define ___NOTE_H

#include <Arduino.h>
#include <stdint.h>

struct MidiNote {
  uint32_t freq;
  uint32_t len;
};

#endif
