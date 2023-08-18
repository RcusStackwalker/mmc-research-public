#include <stdint.h>

#include "gpio.h"
//#include "memaccess.h"
//#include "memory_map.h"
#include "basic_ages_and_decays.h"
#include "fmath.h"
#include "mode_selector.h"
#include "mode_selector_data.h"
#include <tps_variables.h>
#include <defs.h>

#define readu16(x) (x)
#define writeu16(v, x) do { x = (v); } while (0)

#define HYSTERESIS_FLAG(flag_var, _bit_mask, condition_var, off_value, on_value) \
do {									\
	uint_fast16_t var = readu16(flag_var);				\
	const uint_fast16_t bit_mask = _bit_mask;			\
	uint_fast16_t covar = readu16(condition_var);			\
	if (var & bit_mask) {						\
		if (off_value >= covar) writeu16(var & ~bit_mask, flag_var);	\
	} else {							\
		if (on_value < covar) writeu16(var | bit_mask, flag_var);		\
	}								\
} while (0)

extern uint16_t adc_byte_ac_pressure;
extern uint16_t mode_switch_delay;
extern uint16_t decays_x1_alt_mode_change_cel_flash_timer;
extern uint16_t persistent_alt_mode_index;
extern uint16_t mode_selector_flags;
extern uint16_t alt_mode_change_cel_flash_pattern;



extern void adc_convert_mode_input();

#define GET_ALT_MODE_INDEX (readu16(persistent_alt_mode_index) & 0xff)
#define SET_ALT_MODE_INDEX(v) writeu16((v) | ((~(v)) << 8), persistent_alt_mode_index)
static inline int ok_alt_mode_index()
{
	unsigned x = readu16(persistent_alt_mode_index);
	return (x & 0xff) == (((~x) >> 8) & 0xff);
}

#define OK_ALT_MODE_INDEX ok_alt_mode_index()

void update_mode_selector()
{
	uint16_t l_old_mode_index = GET_ALT_MODE_INDEX;
	uint16_t l_mode_changed = 0;
	if (!OK_ALT_MODE_INDEX) {
		SET_ALT_MODE_INDEX(0);
	}
	if (flash_reset_alt_mode_on_ignition_cycle && (readu16(age_x1_ignition) < 20)) {
		SET_ALT_MODE_INDEX(0);
	} else if ((readu16(age_x1_ignition) < 40)
	&& (readu16(tps_main_rcord) > flash_tps_alt_threshold)) {
		if (!l_old_mode_index) {
			SET_ALT_MODE_INDEX(1);
			l_mode_changed = 1;
		}
	}

	if (flash_adc_ac_pressure_master) {
		HYSTERESIS_FLAG(mode_selector_flags, 0x01, adc_byte_ac_pressure, flash_mode_selector_adc_ac_pressure_thresholds[0],flash_mode_selector_adc_ac_pressure_thresholds[1]);
		uint16_t l_new_mode_index = mode_selector_flags & 0x01 ? 1 : 0;
		if (l_old_mode_index != l_new_mode_index) {
			S_DEC(mode_switch_delay);
			if (!mode_switch_delay) {
				SET_ALT_MODE_INDEX(l_new_mode_index);
				l_mode_changed = 1;
			}
		} else {
			mode_switch_delay = flash_init_mode_switch_delay;
		}
	}

	if (l_mode_changed) {
		writeu16(flash_alt_mode_change_cel_flash_time, decays_x1_alt_mode_change_cel_flash_timer);
		writeu16(l_old_mode_index * 2 + GET_ALT_MODE_INDEX, alt_mode_change_cel_flash_pattern);
	}
		
}

uint16_t alt_mode_change_cel()
{
	uint16_t l_timer = readu16(decays_x1_alt_mode_change_cel_flash_timer);
	if (!l_timer)
		return 0;

	l_timer = s_divu16(flash_alt_mode_change_cel_flash_time - l_timer, flash_alt_mode_change_cel_flash_time_slice);
	return flash_mode_change_patterns[alt_mode_change_cel_flash_pattern][l_timer] ? 1 : 0;
}

uint_fast16_t altmap8u16(const void *const *desc)
{
	unsigned idx = GET_ALT_MODE_INDEX;
	if (idx >= MODE_COUNT) idx = 0;
	return map8u16(desc[idx]);
}

uint_fast16_t altmapu16(const void * const *desc)
{
	unsigned idx = GET_ALT_MODE_INDEX;
	if (idx >= MODE_COUNT) idx = 0;
	return mapu16(desc[idx]);
}

uint_fast16_t multiptru16a_dereferenced(const uint16_t *const *arr)
{
	unsigned idx = GET_ALT_MODE_INDEX;
	if (idx >= MODE_COUNT) idx = 0;
	return *arr[idx];
}

#if 0
uint_fast16_t test_disable_o2_feedback()
{
	return flash_alt_disable_o2_feedback[GET_ALT_MODE_INDEX] ? 1 : 0;
}
#endif

void new_adc_convert_mode_input()
{
	adc_convert_mode_input();
	update_mode_selector();
}

