#include "readevent.h"

// NUMDRIVES is defined in notelist.h
bool drivesOn[NUMDRIVES] = { false };

int8_t driveActivate(NoteList *n)
{
    for (uint8_t i = 0; i < NUMDRIVES; ++i) {
        if (!drivesOn[i]) {
            drivesOn[i] = true;
            n->channel = i;
            return 0;
        }
    }
    return -1;
}

int8_t driveFree(NoteList *n)
{
    if (n->channel < NUMDRIVES) {
        drivesOn[n->channel] = false;
        return 0;
    }
    return -1;
}

uint8_t *readEvent(uint8_t currentStatus, uint8_t *pos, bool runningStatus, MidiInfo *mi)
{
    // This orients the function to
    // work properly with a "running status" message.  
    
    if (runningStatus) --pos;
    
    int8_t rc = 0;
    uint8_t metaStatus = 0, note = 0, vel = 0,
            numer = 4, denom = 4, thirtySecondsPerQN = 8;
    uint32_t eventLength = 0;
    const char *notes[] = {
        "C", "C#", "D", "D#", "E", "F",
        "F#", "G", "G#", "A", "A#", "B" 
    };

    fprintf(mi->lf, "DT: %" PRIu32 " ", mi->currentDT);

    if (currentStatus == 0xFF) {
        metaStatus = *++pos;
        fprintf(mi->lf, "Meta - Status %X\n", metaStatus);
        if (metaStatus == 0x2F) {
            fprintf(mi->lf, "** End of Track **\n\n");
            return pos + 2;
        }

        // Read length of meta event...
        // and then skip to first byte of event
        pos = readVarQ(&eventLength, ++pos);
        ++pos;

        // All of these cases end on the last byte of
        // the respective event.
        switch (metaStatus) {
            case CHANNEL:
                // Switches channel number for format zero files.
                if (mi->fileMode == 0)
                    die(mi, "Format 0 channel switch. Not implemented");
                //else pos++;
                break;
            case TIMESIG:
                numer = *pos;
                denom = 1 << *++pos;
                thirtySecondsPerQN = *(pos += 2);
                mi->beatMultiplier = thirtySecondsPerQN / 8.0;
                fprintf(mi->lf,
                        "\nNew Beatmult: %2f"
                        "\nNew Timesig: %" PRIu8 "/%" PRIu8 "\n",
                        mi->beatMultiplier, numer, denom);
                ++pos;
                break;
            case TICKTIME:
                pos = readBigInt(&mi->usecsPerQN, pos, 3);
                mi->bpm = mi->beatMultiplier * ((size_t)60000000 / (size_t)mi->usecsPerQN);
                mi->tickTime = (mi->usecsPerQN / mi->PPQN) / mi->beatMultiplier;
                fprintf(mi->lf, "New Ticktime: %" PRIu32 "\nNew BPM: %" PRIu32 "\n",
                        mi->tickTime, mi->bpm);
                break;
            default:
                fprintf(mi->lf, "Skipping meta event %X\n", metaStatus);
                pos += eventLength;
        }

    }

    // TODO: refactor into function(s)?
    // Check for 0b1000xxxx with no extra bits on msb
    else if (currentStatus & NOTEOFF && !(currentStatus & 0x70)) {
        note = *++pos;
        pos += 2;  // discard velocity, and bump to next byte of dt.

        if (!mi->nl)
            die(mi, "Note off before note on");

        NoteList *timeNote = NoteList_find(mi->nl, note);

        if (!timeNote) {
            fprintf(mi->lf, "At note: %s %" PRIu8 " | ", notes[note%12], note);
            die(mi, "Died finding a note (note off)");
        }
        
        rc = driveFree(timeNote);
        if (rc != 0)
            die(mi, "driveFree");
        timeNote->length = mi->totalDeltaTime - timeNote->DT;
        fprintf(mi->lf, "Note %s%u off.\n", notes[note%12], note / 12 - 1);
    }

    // Check for 0b1001xxxx with no extra bits on msb
    else if (currentStatus & NOTEON && !(currentStatus & 0x60)) {
        note = *++pos;
        vel = *++pos;

        fprintf(mi->lf, "Note %s%u o%s. ",
                notes[note%12], note / 12 - 1, vel ? "n" : "ff");

        if (vel) {
            NoteList *currentNote = NoteList_add(mi->nl, note, mi->totalDeltaTime);

            if (!currentNote) die(mi, "Allocating added note");
            if (!mi->nl) mi->nl = currentNote;
            
            rc = driveActivate(currentNote);
            if (rc != 0)
                die(mi, "\ndriveActivate: Too many drives");

            fprintf(mi->lf, "Channel mod: %" PRIu8 "\n",
                    currentNote->channel);
        }
        else {
            fprintf(mi->lf, "\n");
            NoteList *timeNote = NoteList_find(mi->nl, note);
            if (!timeNote)
                die(mi, "Finding a not (NOTEON)");

            rc = driveFree(timeNote);
            if (rc != 0)
                die(mi, "driveFree");
            timeNote->length = mi->totalDeltaTime - timeNote->DT;
        }

        pos++;
    }
    else if (currentStatus == SYSEXBEG || currentStatus == SYSEXEND) {
        fprintf(mi->lf, "Skipping SysEx Event\n");
        pos = readVarQ(&eventLength, ++pos);
        // readVarQ returns on last byte of VarQ
        pos += eventLength + 1;
    }
    else {
        fprintf(mi->lf, "Ignoring status %X\n", currentStatus);

        /* These conditionals are cryptic; I know.
         * See a table of midi messages to figure out
         * how this operates.
         * Even I don't remember what each thing is...
         */
        if(0xF0 < currentStatus && currentStatus < 0xF8) {
            // These messages have 0 bytes of data
            if (0xF3 < currentStatus) pos++;
            // These have 2 bytes of data
            else if (currentStatus == 0xF2) pos += 3;
            // The rest have 1 byte of data
            else pos += 2;
        }
        // 2 bytes of data
        else if (currentStatus & 0xA0 && !(currentStatus & 0x40))
            pos += 3;
        // 1 byte of data
        else if (currentStatus & 0xC0) pos += 2;
        else
            die(mi, "Unknown status encountered!");
    }
    return pos;
}
