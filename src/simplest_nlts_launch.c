#include <defs.h>
#include <stdint.h>
#include <fmath.h>
#include <basic_ages_and_decays.h>
#include <engine_rpm_variables.h>
#include <gpio.h>

#include "nlts/nlts_data.h"

extern uint16_t vehicle_movement_decay;
extern uint16_t revolution_limit;
extern uint16_t oneshot_crank_event_flags;
extern uint16_t shaft_period1_copy_dline0;
extern uint16_t fuel_map_target_afr;
extern uint16_t tps_main_rcord;

extern const uint16_t flash_launch_control_revolution_limit;
extern const uint16_t flash_nlts_revolution_limit;
extern const uint16_t flash_nlts_target_afr;
extern const uint16_t flash_nlts_cuts_holdoff_time;

void update_revolution_limit()
{
	uint_fast16_t l_base_limit = 0;
	if (age_x1_ignition < 20) {
		/**/
	} else if (!vehicle_movement_decay && IS_CLUTCH_DEPRESSED) {
		l_base_limit = flash_launch_control_revolution_limit;
	} else if ((nlts_state == NLTS_STATE_ON) && (nlts_flags & NLTS_FLAGS_SPARK_CUT)) {
		l_base_limit = flash_nlts_revolution_limit;
	}
	revolution_limit = l_base_limit;
}

uint_fast16_t get_coil_dwell_max_substituting_s_scale_base128(uint_fast16_t p_shaft_period, uint_fast16_t p_dwell_max_ratio)
{
	if (p_shaft_period < revolution_limit)
	{
		return 0;
	}

	return s_scale_base128(p_shaft_period, p_dwell_max_ratio);
}

#define BIT_SET_CONDITION(var, bit_mask, condition) do { \
	if (condition) { \
		var |= bit_mask; \
	} else { \
		var &= ~(bit_mask); \
	} \
} while (0)

#define IS_BIT_SWITCHON(old_var, var, bit_mask) \
((old_var ^ var) & var & (bit_mask))

#define nlts_apps_source (tps_main_rcord * 4)

static void update_nlts_flags()
{
	HYSTERESIS_FLAG(nlts_flags, NLTS_FLAGS_APPS_HIGH, nlts_apps_source, flash_nlts_app_thresholds);
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_CLUTCH_DEPRESSED, IS_CLUTCH_DEPRESSED);
#if 0
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_CLUTCH_PARTIAL_ENGAGEMENT,
		(nlts_state == NLTS_STATE_ON) && 
		((nlts_flags & NLTS_FLAGS_CLUTCH_PARTIAL_ENGAGEMENT)
		|| (decays_x1_nlts_active < s_sub16(flash_init_nlts_active_decay, flash_nlts_delta_holdoff))
		&& (engine_rpm_delta_neg > flash_nlts_rpm_delta_threshold)));
#else
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_CLUTCH_PARTIAL_ENGAGEMENT, 0);
#endif
#if 0
	BIT_SET_CONDITION(nlts_flags, NLTS_FLAGS_HOLDOFF_FUEL_CUT,
		(nlts_state == NLTS_STATE_ON)
		&& (decays_x1_nlts_active >= );
#endif
}

void update_nlts_state()
{
	uint_fast16_t l_old_nlts_flags = nlts_flags;
	update_nlts_flags();
	if (IS_BIT_SWITCHON(l_old_nlts_flags, nlts_flags, NLTS_FLAGS_CLUTCH_DEPRESSED)) {
		if ((nlts_flags & NLTS_FLAGS_APPS_HIGH)
		&& (nlts_flags & NLTS_FLAGS_RPM_HIGH)) {
			nlts_state = NLTS_STATE_ON;
			decays_x1_nlts_active = flash_init_nlts_active_decay;
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
		nlts_flags &= ~NLTS_FLAGS_CUTS;
		return;
	}

	if (IS_BIT_SWITCHON(l_old_nlts_flags, nlts_flags, NLTS_FLAGS_CLUTCH_PARTIAL_ENGAGEMENT)) {
		decays_x1_nlts_active = flash_init_nlts_active_decay_partial_engagement;
	}

	if (nlts_flags & NLTS_FLAGS_CLUTCH_PARTIAL_ENGAGEMENT) {
		nlts_flags &= ~NLTS_FLAGS_CUTS;
	} else {
		if (decays_x1_nlts_active < s_sub16(flash_init_nlts_active_decay, flash_nlts_cuts_holdoff_time)) {
			nlts_flags |= NLTS_FLAGS_SPARK_CUT;
		} else {
			nlts_flags &= ~NLTS_FLAGS_SPARK_CUT;
		}
	}
}

extern const void *const flash_fuel_map_load_axis;
extern const void *const flash_fuel_map_rpm_axis;
extern const void *const flash_launch_target_afr_3dmap8;

extern uint16_t get_fuel_map_load_source();

void new_trampoline_update_fuel_map_target_afr()
{
	update_fuel_map_target_afr();
	if (!vehicle_movement_decay && IS_CLUTCH_DEPRESSED) {
		temp_axis_src = get_fuel_map_load_source();
		calc_axis(&flash_fuel_map_load_axis);
		calc_axis(&flash_fuel_map_rpm_axis);
		fuel_map_target_afr = map8u16(&flash_launch_target_afr_3dmap8);
	} else if ((nlts_state == NLTS_STATE_ON) && (nlts_flags & NLTS_FLAGS_SPARK_CUT)) {
		fuel_map_target_afr = flash_nlts_target_afr;
	}
}
