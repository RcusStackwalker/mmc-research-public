#include <stdint.h>
#include <fmath.h>
#include <gpio.h>
#include <run_state_flags.h>
#include <common_flags.h>
#include <basic_speed_variables.h>
#include <engine_rpm_variables.h>
#include <defs.h>

#include "gear_detector.h"
#include "gear_detector_data.h"

extern uint16_t decays_x1_gear_unstable;
extern uint8_t calculated_gear;
extern uint8_t current_gear;

#define readu8(x) (x)
#define writeu8(v, x) do { x = v; } while (0)
#define readu16(x) (x)
#define writeu16(v, x) do { x = v; } while (0)

static void update_gear_flags()
{
#ifdef MACHINE_Z27AGMT
	uint16_t l_gear_ratio = s16_divu32_16(readu16(can_vehicle_speed) << 14 , readu16(engine_rpm));;
#else
	uint16_t l_gear_ratio = s16_divu32_16(readu16(can_vehicle_speed) << 16 , readu16(engine_rpm));
#endif
	uint16_t l_cgear = readu8(calculated_gear);
	if ((l_cgear >= 1)
	&& (l_cgear <= 6)
	&& (l_gear_ratio > flash_gear_thresholds[l_cgear-1].low_out)
	&& (l_gear_ratio < flash_gear_thresholds[l_cgear-1].high_out)) {
		return;
	}
	unsigned i;
	l_cgear = 0;
	for (i = 0; i < itemsof(flash_gear_thresholds); ++i) {
		if ((l_gear_ratio > flash_gear_thresholds[i].low_in)
		&& (l_gear_ratio < flash_gear_thresholds[i].high_in)) {
			l_cgear = i + 1;
			break;
		}
	}
	writeu8(l_cgear, calculated_gear);
}

void update_current_gear()
{
	uint_fast8_t l_cgear_prev = readu8(calculated_gear);
	update_gear_flags();
	if (l_cgear_prev != readu8(calculated_gear)) {
		writeu16(flash_init_gear_unstable, decays_x1_gear_unstable);
	}

	if (!readu16(vehicle_movement_decay) || (readu16(run_state_flags) & RUN_STATE_FLAGS_NOT_RUNNING)) {
		writeu8(NEUTRAL_GEAR, current_gear);
	} else if (IS_CLUTCH_DEPRESSED) {
		writeu8(CLUTCHED_INDEFINITE_GEAR, current_gear);
	} else if (!readu16(decays_x1_gear_unstable)) {
		writeu8(readu8(calculated_gear), current_gear);
	}
}
