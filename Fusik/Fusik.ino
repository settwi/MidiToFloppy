#include "notes.h"       // delay constants
#include "Note.h"        // struct Note
#include "stillalive.h"  // creates song

#define create(s) create##s()

const byte stepPins[] =  { 2, 4, 6, 8 };
const byte directionPins[] = { 3, 5, 7, 9 };
byte dir = HIGH;
const unsigned int beat = 250;  // ms per note

Note *lamb;
Note *testScale;

void createScale()
{
  uint8_t notes = 15;
  
  testScale = (Note *)malloc(sizeof(Note) * (notes + 1));

  uint16_t scale_freq[] = {
  C_4, D_4, E_4, F_4, G_4, A_5, B_5, C_5,
  B_5, A_5, G_4, F_4, E_4, D_4, C_4
  };
/*
  uint16_t scale_freq[] = {
    LOW_E, LOW_F, LOW_G,
    LOW_G, LOW_F, LOW_E, 
  };
  */
  for (byte i = 0; i < notes; ++i)
    testScale[i] = { scale_freq[i], 5 };
  //testScale[0].beats = 20;
  testScale[notes] = { 0, 0 };
}

inline void pulse(byte i)
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

void reset(bool half = true)
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
  reset();
  create(Scale);
  playSong(testScale);
}

void loop()
{
  //playNote(3, G_5);
}
