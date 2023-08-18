#include <stdint.h>
#include <fmath.h>
#include <update_flags.h>

#include "shift_light.h"

#include "engine_rpm_hires.h"

extern volatile uint8_t P0DATA;
extern volatile uint8_t P10DATA;
extern uint16_t shift_light_flasher_runner;

#define BIT_CONDITION(var, mask, cond) do {		\
	if (cond) {					\
		var |= (mask);				\
	} else {					\
		var &= ~(mask);				\
	}						\
} while (0)

void update_shift_light()
{
	if (!flash_shift_light_control_mode)
		return;
	if (update_flags_main & UPDATE_FLAGS_10HZ) {
		uint_fast16_t l_runner = shift_light_flasher_runner + 1;
		shift_light_flasher_runner = l_runner % MIN(flash_shift_light_slice_count, SHIFT_LIGHT_MAX_SLICE_COUNT);
	}
	unsigned i;
	for (i = 0; i < SHIFT_LIGHT_STAGE_COUNT; ++i) {
		if (engine_rpm_hires < flash_shift_light_rpm_thresholds[i])
			break;
	}
	
	unsigned l_on = i ? flash_shift_light_flash_patterns[i - 1][shift_light_flasher_runner] : 0;
	pushi();
	switch (flash_shift_light_control_mode) {
	case 1: //o2 front heater
		BIT_CONDITION(P0DATA, 0x40, l_on);
		break;
	case 2: //o2 rear heater
		BIT_CONDITION(P0DATA, 0x20, l_on);
		break;
	case 3: //fuel pressure solenoid
		BIT_CONDITION(P10DATA, 0x20, l_on);
		break;
	}
	popi();
}
