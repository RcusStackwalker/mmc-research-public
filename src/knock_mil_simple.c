#include "defs.h"
#include <stdint.h>
#include "gpio.h"
#include <tps_variables.h>
#include <run_state_flags.h>

#define readu16(x) (x)
#define writeu16(v, x) do { x = (v); } while (0)

#define KNOCK_MIL_LOW	0x01
#define KNOCK_MIL_MED	0x02
#define KNOCK_MIL_HIGH	0x04

extern const uint16_t flash_init_knock_mil_flash_timer[4];
extern const uint16_t flash_init_knock_mil_flash_decay;

extern const uint8_t flash_knock_mil_thresholds[6];
extern const uint16_t flash_knock_mil_load_min;
extern const uint16_t flash_knock_mil_tps_min;

extern const uint8_t flash_drop_knock_cel_on_low_tps_and_load;

extern uint16_t knock_mil_flags;
extern uint16_t knock_mil_state;
extern uint16_t decays_x1_knock_mil_flash;
extern uint16_t decays_x1_mil_pulse_timer;
#ifdef KNOCK_CEL_MODE_CHANGE_INDICATION
extern uint16_t decays_x1_alt_mode_change_cel_flash_timer;
#endif

extern uint16_t knock_sum;

extern uint16_t map_engine_load;

extern uint16_t gpio1;
extern uint16_t run_state_flags;

/*mil_flash_timer renamed mil_pulse_timer*/

static unsigned knock_mil_condition()
{
	uint_fast16_t okmf = knock_mil_flags;
	if (run_state_flags & RUN_STATE_FLAGS_NOT_RUNNING) {
		knock_mil_flags = 0;
		knock_mil_state = 0;
		decays_x1_knock_mil_flash = 0;
		decays_x1_mil_pulse_timer = 0;
	}
	HYSTERESIS_FLAG(knock_mil_flags, KNOCK_MIL_LOW, knock_sum, flash_knock_mil_thresholds[0], flash_knock_mil_thresholds[1]);
	HYSTERESIS_FLAG(knock_mil_flags, KNOCK_MIL_MED, knock_sum, flash_knock_mil_thresholds[2], flash_knock_mil_thresholds[3]);
	HYSTERESIS_FLAG(knock_mil_flags, KNOCK_MIL_HIGH, knock_sum, flash_knock_mil_thresholds[4], flash_knock_mil_thresholds[5]);
	uint_fast16_t nkmf = knock_mil_flags;
	unsigned l_reset = ((okmf ^ nkmf) & nkmf) ? 1 : 0;

	if ((map_engine_load < flash_knock_mil_load_min)
	&& (tps_main_rcord < flash_knock_mil_tps_min)) {
		if (flash_drop_knock_cel_on_low_tps_and_load) {
			writeu16(0, decays_x1_knock_mil_flash);
			writeu16(0, knock_mil_state);
		} else if (!decays_x1_knock_mil_flash)
			writeu16(0, knock_mil_state);
	} else if (!decays_x1_knock_mil_flash || l_reset) {
		unsigned state;
		if (nkmf & KNOCK_MIL_HIGH) {
			state = 3;
		} else if (nkmf & KNOCK_MIL_MED) {
			state = 2;
		} else if (nkmf & KNOCK_MIL_LOW) {
			state = 1;
		} else {
			state = 0;
		}
		knock_mil_state = state;
		if (state)
			writeu16(flash_init_knock_mil_flash_decay, decays_x1_knock_mil_flash);
	}
	unsigned state = readu16(knock_mil_state);
	if (!state)
		return 0;

	if (!readu16(decays_x1_mil_pulse_timer) || l_reset)
		writeu16(flash_init_knock_mil_flash_timer[state], decays_x1_mil_pulse_timer);

	return readu16(decays_x1_mil_pulse_timer) >= (flash_init_knock_mil_flash_timer[state] / 2) ? 1 : 0;
}

static void fixup_mil()
{
	unsigned l_is_flashing = 0;
	unsigned l_mil_on = 0;

#ifdef KNOCK_CEL_MODE_CHANGE_INDICATION
	if (readu16(decays_x1_alt_mode_change_cel_flash_timer)) {
		l_mil_on = alt_mode_change_cel();
		l_is_flashing = 1;
	}
#endif
	if (!l_is_flashing && !l_mil_on) {
		l_mil_on = knock_mil_condition();
	}
	if (l_mil_on) {
		gpio1 ^= GPIO1_MIL;
	}
	if (!l_is_flashing && !readu16(knock_mil_state)) {
		writeu16(0, decays_x1_mil_pulse_timer);
	}
}

void new_update_mil()
{
	update_mil();
	fixup_mil();
}
