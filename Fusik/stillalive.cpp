#include "stillalive.h"

Note *stillAlive;

void createStillAlive()
{
  byte songLength = 26;
  stillAlive = (Note *)malloc(sizeof(Note) * songLength);
  uint16_t stillAliveFreq[] = {
    MID_G, MID_FS, MID_E, MID_E, MID_FS,
    MID_A, MID_G, MID_FS, MID_E, MID_E,
    MID_FS, MID_D, MID_E, MID_A, MID_A,
    MID_E, MID_FS, MID_G, MID_E, MID_CS,
    MID_D, MID_E, MID_A, MID_A, MID_FS
  };
  byte i = 0;
  for (; i < 14; ++i)
    stillAlive[i] = { stillAliveFreq[i], 0.5 };
  for (i = 14; i < songLength; ++i)
    stillAlive[i] = { stillAliveFreq[i], 0.5 };
  stillAlive[4].beats = 5;
  stillAlive[9].beats = 1.5;
  stillAlive[11].beats = 1.5;
  stillAlive[13].beats = 3;
  stillAlive[15].beats = 1.5;
  stillAlive[17].beats = 
  stillAlive[19].beats = 
  stillAlive[20].beats = 
  stillAlive[21].beats = 0.75;
  stillAlive[24].beats = 3;
  stillAlive[songLength-1] = { 0, 0 };

}

