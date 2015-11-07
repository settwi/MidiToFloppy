#ifndef ___carolBells_H
#define ___carolBells_H

#include <stdint.h>
#include "midinote.h"

// Format is: note, length

const uint8_t maxChannel = 3;

const uint32_t PROGMEM carolBells0[] = {
	AS_4, 333312,	A_4, 166656,	
	AS_4, 166656,	G_4, 333312,	
	AS_4, 333312,	A_4, 166656,	
	AS_4, 166656,	G_4, 333312,	
	AS_4, 333312,	A_4, 166656,	
	AS_4, 166656,	G_4, 333312,	
	AS_4, 333312,	A_4, 166656,	
	AS_4, 166656,	G_4, 333312,	
	G_4, 999936,	F_4, 999936,	
	DS_4, 999936,	D_4, 999936,	
	AS_5, 333312,	A_5, 166656,	
	AS_5, 166656,	G_5, 333312,	
	AS_5, 333312,	A_5, 166656,	
	AS_5, 166656,	G_5, 333312,	
	AS_5, 333312,	A_5, 166656,	
	AS_5, 166656,	G_5, 333312,	
	AS_5, 333312,	A_5, 166656,	
	AS_5, 166656,	G_5, 333312,	
	D_6, 333312,	C_6, 166656,	
	D_6, 166656,	AS_5, 333312,	
	D_6, 333312,	C_6, 166656,	
	D_6, 166656,	AS_5, 333312,	
	D_6, 333312,	C_6, 166656,	
	D_6, 166656,	AS_5, 333312,	
	D_5, 333312,	G_3, 333312,	
	AS_4, 333312,	AS_4, 666624,	
	AS_4, 333312,	G_4, 666624,	
	G_4, 333312,	G_4, 666624,	
	G_4, 333312,	G_4, 999936,	
	D_3, 999936,	D_3, 666624,	
	D_3, 333312,	D_3, 999936,	
	D_3, 666624,	D_3, 333312,	
	F_3, 999936,	DS_3, 999936,	
	D_3, 999936,	C_3, 999936,	
	G_2, 3999744,	G_2, 999936,	
	DONE, DONE
};
const uint32_t PROGMEM carolBells1[] = {
	REST, 3999744,    AS_4, 333312,	
	A_4, 166656,	AS_4, 166656,	
	G_4, 333312,	AS_4, 333312,	
	A_4, 166656,	AS_4, 166656,	
	G_4, 333312,	AS_4, 333312,	
	A_4, 166656,	AS_4, 166656,	
	G_4, 333312,	AS_4, 333312,	
	A_4, 166656,	AS_4, 166656,	
	G_4, 333312,	DS_3, 999936,	
	G_3, 999936,	DS_3, 999936,	
	G_3, 999936,	G_3, 999936,	
	G_3, 999936,	G_3, 999936,	
	G_3, 333312,	DS_4, 333312,	
	G_3, 333312,	AS_3, 666624,	
	AS_3, 333312,	AS_4, 666624,	
	AS_4, 333312,	AS_3, 666624,	
	AS_3, 333312,	AS_3, 999936,	
	FS_3, 999936,	A_3, 666624,	
	G_3, 333312,	FS_3, 999936,	
	A_3, 666624,	G_3, 333312,	
	G_3, 999936,	G_3, 999936,	
	G_3, 999936,	G_3, 999936,	
	G_3, 3999744,	G_3, 999936,	
	DONE, DONE
};
const uint32_t PROGMEM carolBells2[] = {
	REST, 7999488,		C_4, 999936,	
	D_4, 999936,	C_4, 999936,	
	D_4, 999936,	D_4, 999936,	
	E_4, 999936,	F_4, 999936,	
	E_4, 333312,	C_5, 166656,	
	D_5, 166656,	D_4, 333312,	
	D_4, 666624,	D_4, 333312,	
	AS_3, 666624,	AS_3, 333312,	
	DS_4, 666624,	DS_4, 333312,	
	D_4, 999936,	D_4, 999936,	
	E_4, 333312,	FS_4, 333312,	
	G_4, 333312,	D_4, 999936,	
	E_4, 333312,	FS_4, 333312,	
	G_4, 333312,	D_4, 999936,	
	C_4, 999936,	F_4, 999936,	
	DS_4, 999936,	AS_4, 333312,	
	A_4, 166656,	AS_4, 166656,	
	G_4, 333312,	AS_4, 333312,	
	A_4, 166656,	AS_4, 166656,	
	G_4, 333312,	AS_4, 333312,	
	A_4, 166656,	AS_4, 166656,	
	G_4, 333312,	AS_4, 333312,	
	A_4, 166656,	AS_4, 166656,	
	G_4, 333312,	G_4, 999936,	
	DONE, DONE
};
const uint32_t PROGMEM carolBells3[] = {
	REST, 7999488,		G_5, 333312,	
	G_5, 333312,	REST, 666624,		
	G_5, 333312,	REST, 666624,		
	G_5, 333312,	REST, 666624,		
	AS_5, 333312,	REST, 333312,		
	G_5, 333312,	AS_5, 333312,	
	REST, 333312,		G_5, 333312,	
	AS_5, 333312,	REST, 333312,		
	G_5, 333312,	AS_4, 333312,	
	REST, 333312,		G_4, 333312,	
	G_4, 666624,	G_4, 333312,	
	D_4, 666624,	D_4, 333312,	
	DONE, DONE
};

const uint32_t *const carolBells[] = { carolBells0, carolBells1, carolBells2, carolBells3, };

#endif