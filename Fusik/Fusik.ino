#include <Arduino.h>
#include "floppypin.h"
#include "midinote.h"
#include "playsong.h"
#include "pirate.mid.h"
#include "canon.mid.h"
#include "songs.mid.h"

#define msdelay 5

FloppyPin pins[] = {
  { 48, 49 }, { 46, 47 },
  { 44, 45 }, { 42, 43 }
};

void reset()
{
  for (byte i = 0; i < 4; ++i)
    digitalWrite(pins[i].dir, HIGH);
   
  for (byte i = 0; i < 80; ++i) {
    for (byte j = 0; j < 4; ++j) {
      digitalWrite(pins[j].step, HIGH);
      digitalWrite(pins[j].step, LOW);
    }
    delay(msdelay);
  }
  for (byte i = 0; i < 4; ++i)
    digitalWrite(pins[i].dir, LOW);
   
  for (byte i = 0; i < 40; ++i) {
    for (byte j = 0; j < 4; ++j) {
      digitalWrite(pins[j].step, HIGH);
      digitalWrite(pins[j].step, LOW);
    }
    delay(msdelay);
  }
}

void setup()
{
  pinMode(13, OUTPUT);
  // Configure floppy pins for output
  for (byte pin = 42; pin < 50; ++pin)
    pinMode(pin, OUTPUT);
  
  reset();

  // After inclusion, insert song name HERE
  playSong(pirateFixed);
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
}
