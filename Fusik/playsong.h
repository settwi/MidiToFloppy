#ifndef ___PLAYSONG_H
#define ___PLAYSONG_H

#include <Arduino.h>
//#include <avr/pgmspace.h>
#include "midinote.h"
#include "notes.h"
//#include "notes.higher.h"

const uint8_t directionPins[] = { 42, 44, 46, 48 };
const uint8_t stepPins[] = { 43, 45, 47, 49 };

extern byte dir;

#define getElement(p, i) (pgm_read_dword_far((p) + i))

#define isDone(freq, len) (freq == DONE && len == DONE)

#define pulse(i) do { \
  /* This switch statement changes the 
   *  direction of the drives,
   *  so they all stay in the middle.
   */ \
  switch ((i)) { \
    /* Pin 42 */ \
    case 0: PORTL ^= 0b00000001; break; \
    /* Pin 44 */ \
    case 1: PORTL ^= 0b00000100; break; \
    /* Pin 46 */ \
    case 2: PORTL ^= 0b00010000; break; \
    /* Pin 48 */ \
    case 3: PORTL ^= 0b01000000; break; \
  } \
  PORTL |= _BV((i)*2 + 1); \
  PORTL &= ~_BV((i)*2 + 1); \
} while(0);

struct WaitTime {
  uint64_t nextStep;
  uint64_t stopTime;
  WaitTime() : nextStep(0), stopTime(0) { };
};

void playSong(const uint32_t *const *);

#endif
