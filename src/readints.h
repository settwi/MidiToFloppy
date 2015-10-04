#ifndef ___READ_INTS_H
#define ___READ_INTS_H

#include <stdint.h>

uint8_t *readBigInt(uint32_t *readTo, uint8_t *buf, uint8_t times);

uint8_t *readVarQ(uint32_t *readTo, uint8_t *chunkPtr);

#endif
