#ifndef ___mary_H
#define ___mary_H

#include <stdint.h>
#include "midinote.h"

// Format is: note, length

const uint8_t maxChannel = 1;

const uint32_t PROGMEM mary0[] = {
	REST, 1953,		E_4, 451143,	
	D_4, 451143,	REST, 48825,		
	C_4, 451143,	REST, 48825,		
	D_4, 451143,	REST, 48825,		
	E_4, 451143,	REST, 48825,		
	E_4, 451143,	REST, 48825,		
	E_4, 902286,	REST, 97650,		
	D_4, 451143,	REST, 48825,		
	D_4, 451143,	REST, 48825,		
	D_4, 902286,	REST, 97650,		
	E_4, 451143,	REST, 48825,		
	G_4, 451143,	REST, 48825,		
	G_4, 902286,	REST, 97650,		
	E_4, 451143,	REST, 48825,		
	D_4, 451143,	REST, 48825,		
	C_4, 451143,	REST, 48825,		
	D_4, 451143,	REST, 48825,		
	E_4, 451143,	REST, 48825,		
	E_4, 451143,	REST, 48825,		
	E_4, 451143,	REST, 48825,		
	E_4, 451143,	REST, 48825,		
	D_4, 451143,	REST, 48825,		
	D_4, 451143,	REST, 48825,		
	E_4, 451143,	REST, 48825,		
	D_4, 451143,	REST, 48825,		
	C_4, 1902222,	
	DONE, DONE
};
const uint32_t PROGMEM mary1[] = {
	REST, 1953,		G_3, 1902222,	
	G_3, 1902222,	REST, 97650,
	G_3, 1902222,	REST, 97650,
	G_3, 1902222,	REST, 97650,
	G_3, 1902222,	REST, 97650,		
	G_3, 1902222,	REST, 97650,		
	G_3, 1902222,	REST, 97650,		
	E_3, 1902222,	
	DONE, DONE
};

const uint32_t *const mary[] = { mary0, mary1, nullptr, nullptr, };

#endif
