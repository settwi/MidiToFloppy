#include "notes.h"       // delay constants
#include "Note.h"        // struct Note
#include "stillalive.h"  // creates song
#define create(s) create##s()
const byte stepPins[] =  { 2, 4, 6, 8 };
const byte directionPins[] = { 3, 5, 7, 9 };
byte dir = HIGH;
const uint16_t beat = 250;  // ms per note

Note *lamb;
Note *testScale;

void createScale()
{
  // Need room for ending note
  testScale = (Note *)(malloc(sizeof(Note) * 16));
  uint16_t scale_freq[] = {
  MID_C, MID_D, MID_E,
  MID_F, MID_G, HIGH_A,
  HIGH_B, HIGH_C, HIGH_B,
  HIGH_A, MID_G, MID_F,
  MID_E, MID_D, MID_C
  };
  for (byte i = 0; i < 16; ++i)
    testScale[i] = { scale_freq[i], 1 };
  testScale[15] = { 0, 0 };
}

void createLamb()
{
  // Room for ending note
  lamb = (Note *)malloc(sizeof(Note) * 27);
  // index 6, 9, 12 are half-notes
  uint16_t lambFreq[] = {
  MID_E, MID_D, MID_C, MID_D,
  MID_E, MID_E, MID_E,
  MID_D, MID_D, MID_D,
  MID_E, MID_G, MID_G,
  MID_E, MID_D, MID_C, MID_D,
  MID_E, MID_E, MID_E, MID_E,
  MID_D, MID_D, MID_E, MID_D
  };

  for (byte i = 0; i < 25; ++i) {
    if (i == 6 || i == 9 || i == 12)
      lamb[i] = { lambFreq[i], 2 };
    else
      lamb[i] = { lambFreq[i], 1 };
  }
  lamb[25] = { MID_C, 4 };
  lamb[26] = { 0, 0 };
}

void pulse(byte i)
{
  digitalWrite(stepPins[i], HIGH);
  digitalWrite(stepPins[i], LOW);
}

// Can't accept typedef'd Note...?
void playSong(struct Note *song)
{
  for(size_t i = 0;
      song[i].freq != song[i].beats;
      ++i)
  {
    // Rest?
    if (song[i].freq == (unsigned int)~0) {
      delayMicroseconds(song[i].beats * beat);
      continue;
    } else {
      for (size_t j = 0;
      // Make every note the same length
      j < (beat / (song[i].freq / 1000) * song[i].beats);
      ++j)
      {
        digitalWrite(directionPins[i%4], dir);
        dir ^= HIGH; 
        pulse(i%4);
        delayMicroseconds(song[i].freq);
      }
      // Rest between every note.
      // Like lifting a finger.
      delay(10);
    }
  }
}

void playNote(byte i, uint16_t frequency)
{
  digitalWrite(directionPins[i], dir);
  dir ^= HIGH;
  pulse(i);
  delayMicroseconds(frequency);
}

void reset(bool half)
{
  // Pulse the pins until we're back at the beginning
  for (byte i = 0; i < 4; ++i) {
    digitalWrite(directionPins[i], LOW);
    for (byte j = 0; j < 80; ++j) {
      delay(5);
      pulse(i);
    }
    digitalWrite(directionPins[i], HIGH);
    
    // Do we want to sit in the middle
    // and vibrate?
    if (half)
      for (byte j = 0; j < 40; ++j) {
        delay(5);
        pulse(i);
      }
  }
  for (byte i = 0; i < 4; ++i)
    digitalWrite(directionPins[i], dir);
}

void setup()
{
  for (byte pin = 2; pin < 10; ++pin)
    pinMode(pin, OUTPUT);
  reset(true);
  create(Scale);
  playSong(testScale);
}

void loop()
{
  //playNote(3, MID_CS);
}
