#include <fmath.h>

#include "sst_multimap.h"

#define SST_MODE_SUPERSPORT (sst_mode_flags & 0x4400)
#define SST_MODE_SPORT (sst_mode_flags & 0x2200)

extern uint16_t sst_mode_flags;

uint_fast16_t sst_multimap8u16(const void *ptr[3])
{
	if (SST_MODE_SUPERSPORT) {
		return map8u16(ptr[2]);
	} else if (SST_MODE_SPORT) {
		return map8u16(ptr[1]);
	} else {
		return map8u16(ptr[0]);
	}
}

uint_fast16_t sst_multimapu16(const void *ptr[3])
{
	if (SST_MODE_SUPERSPORT) {
		return mapu16(ptr[2]);
	} else if (SST_MODE_SPORT) {
		return mapu16(ptr[1]);
	} else {
		return mapu16(ptr[0]);
	}
}
