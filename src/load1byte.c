#include "fmath.h"

extern uint16_t map_engine_load;
extern uint8_t load1byte;

void update_load1byte()
{
	load1byte = s_16to8(map_engine_load / 4);
}
