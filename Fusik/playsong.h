#ifndef ___PLAYSONG_H
#define ___PLAYSONG_H

#include <Arduino.h>
#include "floppypin.h"
#include "midinote.h"
// Include one of these depending on the song's notes...
// There are two files because of the physical restrictions of
// the floppy drives.
#include "notes.h"
//#include "notes.higher.h"

// In main file; needs to be accessed there
extern FloppyPin pins[];

#define getElement(p, i) \
  ((p) ? pgm_read_dword_far((p) + i) : DONE)
#define isDone(freq, len) ((freq) == DONE && (len) == DONE)

struct FloppyTime {
  uint32_t nextStep;
  uint32_t stopTime;
  FloppyTime() : nextStep(0), stopTime(0) { };
};

#define pulse(i) do { \
  digitalWrite(pins[i].dir, \
               !digitalRead(pins[i].dir)); \
  digitalWrite(pins[i].step, HIGH); \
  digitalWrite(pins[i].step, LOW); \
} while(0)

void playSong(const uint32_t *const *);

#endif
