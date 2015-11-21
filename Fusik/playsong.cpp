#include "playsong.h"
  
void playSong(const uint32_t *const *song)
{
  if (!song || !(*song)) return;
  
  FloppyTime ft[4] = { };

  uint32_t indx[4] = { 0 };

  uint32_t freq[] = {
    getElement(song[0], 0),
    getElement(song[1], 0),
    getElement(song[2], 0),
    getElement(song[3], 0),
  };
  
  uint32_t len[] = {
    getElement(song[0], 1),
    getElement(song[1], 1),
    getElement(song[2], 1),
    getElement(song[3], 1),
  };

  uint32_t currentTime = 0;
  
  while (!(isDone(freq[0], len[0]) && isDone(freq[1], len[1]) &&
           isDone(freq[2], len[2]) && isDone(freq[3], len[3]))) {
    for (byte i = 0; i < 4; ++i) {
      currentTime = micros();

      if (!isDone(freq[i], len[i])) {
        
        if (ft[i].nextStep < currentTime) {
          if (freq[i] != REST)
            pulse(i);
          ft[i].nextStep = currentTime + freq[i];
        }

        if (!ft[i].stopTime)
          ft[i].stopTime = currentTime + (len[i] = getElement(song[i], indx[i] + 1));
        
        if (ft[i].stopTime < currentTime) {
          indx[i] += 2;
          ft[i].nextStep = currentTime + (freq[i] = getElement(song[i], indx[i]));
          ft[i].stopTime = currentTime + (len[i]  = getElement(song[i], indx[i] + 1));
        }
      }
    }
  }
}
