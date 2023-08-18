#include "memaccess.h"
#include <stdint.h>
#include "gpio.h"
#include "memory_map.h"

#define MIL_SET BIT_SET16(gpio1, GPIO1_MIL)
#define MIL_CLEAR BIT_CLEAR16(gpio1, GPIO1_MIL)
#define MIL_CONDITION(x) do { if (x) { MIL_SET; } else { MIL_CLEAR; } } while (0)

unsigned debug_mil_condition();
unsigned critical_mil_flash();

extern uint16_t flash_mil_ignition_enable_age_max;


#define KNOCK_MIL_LOW	0x01
#define KNOCK_MIL_MED	0x02
#define KNOCK_MIL_HIGH	0x04

extern const uint16_t flash_init_knock_mil_flash_timer[4];
extern const uint16_t flash_init_knock_mil_flash_decay;

extern const uint8_t flash_knock_mil_thresholds[6];
extern const uint16_t flash_knock_mil_load_min;
extern const uint16_t flash_knock_mil_tps_min;

extern const uint8_t flash_drop_knock_cel_on_low_tps_and_load;

#if 0
ROM_SECTION("knock_mil_condition_section") void regenerate_knock_cel(uint16_t state)
{
	if (state >= readu16(knock_mil_state)) {
		writeu16(state, knock_mil_state);
		writeu16(flash_init_knock_mil_flash_decay, decays_x1_knock_mil_flash);
	}
}
#endif

ROM_SECTION("knock_mil_condition_section") unsigned knock_mil_condition()
{
	uint_fast16_t okmf = readu16(knock_mil_flags);
	HYSTERESIS_FLAG(knock_mil_flags, KNOCK_MIL_LOW, knock_sum, flash_knock_mil_thresholds[0], flash_knock_mil_thresholds[1]);
	HYSTERESIS_FLAG(knock_mil_flags, KNOCK_MIL_MED, knock_sum, flash_knock_mil_thresholds[2], flash_knock_mil_thresholds[3]);
	HYSTERESIS_FLAG(knock_mil_flags, KNOCK_MIL_HIGH, knock_sum, flash_knock_mil_thresholds[4], flash_knock_mil_thresholds[5]);
	uint_fast16_t nkmf = readu16(knock_mil_flags);
	unsigned l_reset = ((okmf ^ nkmf) & nkmf) ? 1 : 0;

	if ((readu16(map_engine_load) < flash_knock_mil_load_min)
	&& (readu16(tps_main_rcord) < flash_knock_mil_tps_min)) {
		if (flash_drop_knock_cel_on_low_tps_and_load) {
			writeu16(0, decays_x1_knock_mil_flash);
			writeu16(0, knock_mil_state);
		} else if (!readu16(decays_x1_knock_mil_flash))
			writeu16(0, knock_mil_state);
	} else if (!readu16(decays_x1_knock_mil_flash)
	|| l_reset) {
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
		writeu16(state, knock_mil_state);
		if (!state)
			return 0;

		writeu16(flash_init_knock_mil_flash_decay, decays_x1_knock_mil_flash);
	}
	unsigned state = readu16(knock_mil_state);
	if (!state)
		return 0;

	if (!readu16(decays_x1_mil_flash_timer) || l_reset)
		writeu16(flash_init_knock_mil_flash_timer[state], decays_x1_mil_flash_timer);

	return readu16(decays_x1_mil_flash_timer) >= (flash_init_knock_mil_flash_timer[state] / 2) ? 1 : 0;
}

ROM_SECTION("update_mil_section") void update_mil()
{
	unsigned r10 = 0;
	unsigned l_is_flashing = 0;
	unsigned l_mil_on = 0;
	unsigned i;

	if (IS_BIT_SET16(sio0_protocol_flags, 0xc3)
	&& IS_BIT_SET16(sio0_state, 0x80))
		BIT_SET16(sio0_diagnostic_session_is_or_was_active, 0x80);

	if (!readu16(decays_x1_ignition)) {
		BIT_CLEAR16(sio0_diagnostic_session_is_or_was_active, 0x80);
	} /* else if (IS_BIT_SET16(debug_flags, 0x80)) {
		l_is_flashing = 1;
		l_mil_on = debug_mil_condition();
	} */ else if (readu16(age_x1_ignition) < flash_mil_ignition_enable_age_max * 20) {
		l_mil_on = 1;
	} else if (IS_BIT_SET(alt_inputs1_processed, GPINPUTS1_FIX_SPARK_5BTDC)) {
		l_mil_on = 1;
	} else {
		for (i = 0; i < DTC_FLAGS_ARRAY_SIZE; ++i) {
			if (!dtc_mil_active_errors[i]) continue;
			l_mil_on = 1;
			break;
		}
	}
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
		MIL_SET;
	} else {
		MIL_CLEAR;
	}
	if (!l_is_flashing && !readu16(knock_mil_state)) {
		writeu16(0, decays_x1_mil_flash_timer);
	}
}
