#include <stdint.h>

extern uint16_t atshift_current_gear;
extern uint16_t atshift_target_gear;
extern uint16_t agpins1_processed;

extern uint16_t indicator_counter;

extern const uint16_t flash_manual_mode_indicator_off_gear_index;
extern const uint16_t flash_manual_mode_blink_off_time;
extern const uint16_t flash_indicator_max;

uint16_t get_calculated_gear_indication()
{
	uint_fast16_t l_gear;
	if (++indicator_counter >= flash_indicator_max)
	{
		indicator_counter = 0;
	}
	if (agpins1_processed & 0x0100) {
		 l_gear = atshift_target_gear;
		//blink or noblink?
		//blink with space?
		if (indicator_counter < flash_manual_mode_blink_off_time)
		{
			l_gear = flash_manual_mode_indicator_off_gear_index;
		}
	} else {
		 l_gear = atshift_current_gear;
		//blink in drive mode?
		//blink with D
	}
	return l_gear;
}
