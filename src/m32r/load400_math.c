#include <stdint.h>

uint32_t ps_scale32_base512(uint32_t x, uint16_t y)
{
	uint32_t high = (x >> 16) * y;
	uint32_t low = (x & 0xffff) * y;

	if (high >> 25)
		return 0xffffffff;

	return (high << (16 - 9)) + ((low + 256) >> 9);

}
