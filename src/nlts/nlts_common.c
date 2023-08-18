#include "nlts_data.h"
#include "stdint.h"
#include "fmath.h"
#include "gpio.h"
#include "defs.h"
#include <engine_rpm_variables.h>
#include <basic_speed_variables.h>
#include <tps_variables.h>

#define nlts_apps_source (tps_main_rcord * 4)

extern uint16_t alt_inputs3_processed;
extern uint16_t temp_axis_src;

#define MAX(_x,_y) ({ unsigned x = (_x); unsigned y = (_y); \
	x < y ? y : x; })

#define HYSTERESIS_FLAG(flag_var, _bit_mask, condition_var, conditions) \
do {									\
	uint_fast16_t var = flag_var;				\
	const uint_fast16_t bit_mask = _bit_mask;			\
	uint_fast16_t covar = condition_var;			\
	if (var & bit_mask) {						\
		if (conditions[0] >= covar) flag_var = var & ~bit_mask; \
	} else {							\
		if (conditions[1] < covar) flag_var = var | bit_mask;		\
	}								\
} while (0)


#define BIT_SET_CONDITION(var, bit_mask, condition) do { \
	if (condition) { \
		var |= bit_mask; \
	} else { \
		var &= ~(bit_mask); \
	} \
} while (0)

#define IS_BIT_SWITCHON(old_var, var, bit_mask) \
((old_var ^ var) & var & (bit_mask))

#ifdef NLTS_SIMPLE

#else

#include "../gear_detector.h"
#include "../gear_detector_data.h"

static void update_nlts_vehicle_speed()
{
#if 0
#if defined(NLTS_USE_ABS_REAR_AXLE_SPEED)
	nlts_speed = scale_can_vehicle_speed(canrx_rear_axle_speed, 250);
#elif defined(NLTS_USE_ABS_FRONT_AXLE_SPEED)
	nlts_speed = canrx_front_axle_speed;
#else
	nlts_speed = s_32to16(vehicle_speed * 256);
#endif

	nlts_speed_filtered = aprxu16_255(nlts_speed_filtered, nlts_speed, flash_nlts_speed_averaging_rate);
#else
	nlts_speed_filtered = aprxu16_255(nlts_speed_filtered, can_vehicle_speed, flash_nlts_speed_averaging_rate);
#endif
}


static uint16_t get_gear_engine_rpm(unsigned p_gear)
{
	return s16_divu32_16(nlts_speed_filtered << 8, flash_nlts_gear_ratios[p_gear]);
}

#endif

extern const void *const flash_nlts_rpm_axis;
extern const void *const flash_nlts_apps_axis;
extern const void *const flash_nlts_fuelcut_holdoff_3dmap8;

static void update_nlts_flags()
{
	HYSTERESIS_FLAG(nlts_flags, NLTS_FLAGS_APPS_HIGH, accel_pedal_position_scaled_corrected_smoothed, flash_nlts_app_thresholds);
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_CLUTCH_DEPRESSED, IS_CLUTCH_DEPRESSED);
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_GEAR_DOWN_RPM, engine_rpm < flash_nlts_gear_down_rpm_max);
#ifdef NLTS_SIMPLE
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_GEAR_HIGH, gear_ratio < flash_nlts_gear_ratio_high);
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_CURRENT_GEAR_CORRECT, 0);
#else
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_GEAR_HIGH, 0);
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_CURRENT_GEAR_CORRECT, calculated_gear != 0);
#endif;
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_CLUTCH_PARTIAL_ENGAGEMENT,
		(nlts_state == NLTS_STATE_ON) && 
		((nlts_flags & NLTS_FLAGS_CLUTCH_PARTIAL_ENGAGEMENT)
		|| (decays_x1_nlts_active < s_sub16(flash_init_nlts_active_decay, flash_nlts_delta_holdoff))
		&& (engine_rpm_delta_neg > flash_nlts_rpm_delta_threshold)));
}


void update_nlts_target_torque_limit()
{
	uint_fast16_t l_old_nlts_flags = nlts_flags;
#ifdef NLTS_SIMPLE
#else
	update_nlts_vehicle_speed();
#endif
	update_nlts_flags();
	if (IS_BIT_SWITCHON(l_old_nlts_flags, nlts_flags, NLTS_FLAGS_CLUTCH_DEPRESSED)) {
		if (nlts_flags & NLTS_FLAGS_APPS_HIGH) {
			nlts_state = NLTS_STATE_ON;
			decays_x1_nlts_active = flash_init_nlts_active_decay;
			if (nlts_flags & NLTS_FLAGS_GEAR_DOWN_RPM) {
				if (nlts_flags & NLTS_FLAGS_GEAR_HIGH) {
					nlts_target_rpm = ps_mul_divu16(engine_rpm, 256, flash_nlts_rpm_ratio_high) + flash_nlts_rpm_overshoot;
				} else {
					nlts_target_rpm = engine_rpm + flash_nlts_rpm_overshoot;
				}
			} else {
				nlts_target_rpm = s_scale_base256(engine_rpm, (nlts_flags & NLTS_FLAGS_GEAR_HIGH) ? flash_nlts_rpm_ratio_high : flash_nlts_rpm_ratio_low) + flash_nlts_rpm_overshoot;
			}
		} else {
			nlts_state = NLTS_STATE_UNLIMITED;
		}
	} else if (IS_BIT_SWITCHON(nlts_flags, l_old_nlts_flags, NLTS_FLAGS_CLUTCH_DEPRESSED)) {
		nlts_state = NLTS_STATE_OFF;
	}
	if ((nlts_state == NLTS_STATE_ON) && !decays_x1_nlts_active) {
		nlts_state = NLTS_STATE_UNLIMITED;
	}
	if ((nlts_state == NLTS_STATE_ON) && !(nlts_flags & NLTS_FLAGS_APPS_HIGH)) {
		nlts_state = NLTS_STATE_UNLIMITED;
	}
	if (nlts_state != NLTS_STATE_ON) {
		decays_x1_nlts_active = 0;
		nlts_target_rpm = engine_rpm;
		nlts_rpm_error = 32768;
		nlts_flags &= ~NLTS_FLAGS_FUEL_CUT;
		return;
	}

	if (IS_BIT_SWITCHON(l_old_nlts_flags, nlts_flags, NLTS_FLAGS_CLUTCH_PARTIAL_ENGAGEMENT)) {
		decays_x1_nlts_active = flash_init_nlts_active_decay_partial_engagement;
	}

	if (nlts_flags & NLTS_FLAGS_CLUTCH_PARTIAL_ENGAGEMENT) {
		nlts_target_rpm = engine_rpm;
		nlts_rpm_error = 32768;
		nlts_flags &= ~NLTS_FLAGS_FUEL_CUT;
	} else {
		nlts_rpm_error = s_32to16(s_sub32(engine_rpm + 32768, nlts_target_rpm));

		temp_axis_src = engine_rpm;
		calc_axis(&flash_nlts_rpm_axis);
		temp_axis_src = nlts_apps_source;
		calc_axis(&flash_nlts_apps_axis);

		if (decays_x1_nlts_active < s_sub16(flash_init_nlts_active_decay, map8u16(&flash_nlts_fuelcut_holdoff_3dmap8))) {
			nlts_flags |= NLTS_FLAGS_FUEL_CUT;
		} else {
			nlts_flags &= ~NLTS_FLAGS_FUEL_CUT;
		}
	}
}
