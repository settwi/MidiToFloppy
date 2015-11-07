#include "playsong.h"
  
void playSong(const uint32_t *const *song)
{
  if (!song) return;
  
  WaitTime wt[4] = { };

  uint32_t indx[4] = { 0 };

  uint32_t freq[] = {
    song[0] ? getElement(song[0], 0) : DONE,
    song[1] ? getElement(song[1], 0) : DONE,
    song[2] ? getElement(song[2], 0) : DONE,
    song[3] ? getElement(song[3], 0) : DONE,
  };
  
  uint32_t len[] = {
    song[0] ? getElement(song[0], 1) : DONE,
    song[1] ? getElement(song[1], 1) : DONE,
    song[2] ? getElement(song[2], 1) : DONE,
    song[3] ? getElement(song[3], 1) : DONE,
  };

  uint64_t currentTime = 0;
  
  while (!(isDone(freq[0], len[0]) && isDone(freq[1], len[1]) &&
           isDone(freq[2], len[2]) && isDone(freq[3], len[3]))) {
    for (uint8_t d = 0; d < 4; ++d) {
      currentTime = (uint64_t)micros();

      if (!isDone(freq[d], len[d])) {
          if (wt[d].nextStep < currentTime) {

            if (freq[d] != REST) pulse(d);
            wt[d].nextStep = currentTime + (freq[d] = (uint64_t)(getElement(song[d], indx[d])));
          }

        if (!wt[d].stopTime) {
          wt[d].stopTime = currentTime + (len[d] = (uint64_t)(getElement(song[d], indx[d] + 1)));
        }

        if (wt[d].stopTime < currentTime) {
          indx[d] += 2;
          wt[d].nextStep = currentTime + (freq[d] = (uint64_t)(getElement(song[d], indx[d])));
          wt[d].stopTime = currentTime + (len[d]  = (uint64_t)(getElement(song[d], indx[d] + 1)));
        }
      }
    }
  }
}
