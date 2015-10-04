#include "readticks.h"

void readTicks(MidiInfo *mi)
{
    bool runningStatus = false;
    uint8_t currentStatus = 0, previousStatus = 0,
            buf[4] = { 0 }, *trackBuf = NULL;
    uint16_t track = 0;
    uint32_t trackLength = 0;
    // Each track chunk.
    // At least one, so do-while used.
    do {
        if (trackBuf) free(trackBuf);
        fread(buf, 1, 4, mi->mf);

        // Hacky? Nah.
        if (strncmp((char *)buf, "MTrk", 4)) {
            die(mi, "Cannot find track chunk. Aborting");
        }
        
        // Assemble track length from four bytes.
        fread(buf, 1, 4, mi->mf);
        readBigInt(&trackLength, buf, 4);

        // Reduce file I/O overhead.
        // sizeof seems silly here... uint8_t has 8 bits == 1 byte.
        trackBuf = malloc(sizeof(uint8_t) * trackLength);
        if (!trackBuf)
            die(mi, "Allocating trackBuf");

        fread(trackBuf, trackLength, 1, mi->mf);

        // Each MTrk event.
        uint8_t *pos = trackBuf;
        while(pos < trackBuf + trackLength) {
            mi->currentDT =
            currentStatus = 0;
            
            pos = readVarQ(&mi->currentDT, pos);
            mi->totalDeltaTime += mi->currentDT;
            currentStatus = *++pos;

            // Running status check
            if ((runningStatus = (currentStatus < 0x80))) {
                fprintf(mi->lf,
                        "RUNNING STATUS\nCurrent: %u\nPrevious: %u\n",
                        currentStatus, previousStatus);
                currentStatus = previousStatus;
            }

            // Passed by address in case of 0-velocity NOTEON message
            pos = readEvent(currentStatus, /*previousStatus,*/
                            pos, runningStatus, mi);

            previousStatus = currentStatus;
        }
        if (trackBuf) {
            free(trackBuf);
            trackBuf = NULL;
        }
    } while (++track < mi->numTracks);

    fprintf(mi->lf, "** End of Read **\n");
}