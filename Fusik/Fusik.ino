#include <Arduino.h>
#include "midinote.h"   // struct MidiNote
#include "playsong.h"   // function for playing songs!

#include "songs.mid.h"

#define msdelay 5

void reset()
{   
  // For some help understanding what's going on here,
  // look up "PortManipulation Arduino"
  PORTL ^= 0b01010101;
    for (byte j = 0; j < 80; ++j) {
      PORTL |= 0b10101010;
      PORTL &= ~0b10101010;
      delay(msdelay);
    }
    PORTL ^= 0b01010101;
    for (byte j = 0; j < 40; ++j) {
      PORTL |= 0b10101010;
      PORTL &= ~0b10101010;
      delay(msdelay);
    }
}

void setup()
{
  pinMode(13, OUTPUT);
  // Configures all PORTL pins
  // (digital pins 42 - 49 on MEGA)
  // for output
  DDRL |= 0xff;
  // Starts all pins in HIGH state
  PORTL |= 0xff;
  reset();

  // After inclusion, insert song name HERE
  playSong(pirate);
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
}
