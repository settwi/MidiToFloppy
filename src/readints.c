#include "readints.h"

// Initialize your variables before using this function.
uint8_t *readBigInt(uint32_t *readTo, uint8_t *buf, uint8_t times)
{
	*readTo = 0;
    for (uint8_t *p = buf; p < buf + times; p++) {
        *readTo = (*readTo << 8) | (*p & 0xFF);
    }

    return buf + times;
}

// Returns p at last part of VarQ.
uint8_t *readVarQ(uint32_t *readTo, uint8_t *p)
{
    *readTo = 0;
    do {
        *readTo |= (*p & 0x7F);
        if (*p >= 0x80) *readTo <<= 7;
        else break;
    } while (++p);
    
    return p;
}
