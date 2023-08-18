#include <fmath.h>

#include "tephra_multimap.h"

#define ALT_MAPS_MODE (tephra_flags & 0x40)

extern uint8_t tephra_flags;

uint_fast16_t tephra_multimap8u16(const void *ptr[2])
{
	if (ALT_MAPS_MODE) {
		return map8u16(ptr[1]);
	} else {
		return map8u16(ptr[0]);
	}
}

uint_fast16_t tephra_multimapu16(const void *ptr[2])
{
	if (ALT_MAPS_MODE) {
		return mapu16(ptr[1]);
	} else {
		return mapu16(ptr[0]);
	}
}

