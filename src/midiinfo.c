#include "midiinfo.h"

void MidiInfo_init(FILE *mf, FILE *lf, FILE *out, struct MidiInfo *mi)
{
	mi->fileMode =
	mi->channel =
	mi->numTracks =
	mi->divisions =
	mi->currentDT = 
	mi->totalDeltaTime = 0;
	mi->beatMultiplier = 1;
	mi->bpm = 120;
	mi->PPQN = 96;
	mi->usecsPerQN = 500000;
	mi->tickTime = 5208;
	
	mi->mf = mf;
	mi->lf = lf;
	mi->out = out;
	mi->nl = NULL;
}

