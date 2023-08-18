#include <defs.h>
#include <stdint.h>
#include <fmath.h>
#include <basic_ages_and_decays.h>
#include <engine_rpm_variables.h>
#include <gpio.h>

#include "nlts/nlts_data.h"

extern uint16_t map_engine_load;

extern const uint16_t flash_maf_fault_revolution_period_limit;
extern const uint16_t flash_revolution_period_limit;
extern const uint16_t flash_launch_control_revolution_limit;
extern const uint16_t flash_init_overrev_cycle_decay[2];
extern const uint16_t flash_overrev_kill_spark_cycles[2];
extern const uint16_t flash_spark_overrev_protection_limit;
extern const uint8_t flash_simple_standing_revolution_limit_enabled;
extern const uint16_t flash_revolution_limit_spark_decay_cycles_per_tick[2];

extern uint16_t vehicle_movement_decay;
extern uint16_t revolution_limit;
extern uint16_t sensor_faults;
extern uint16_t shaft_period1_copy_dline0;
extern uint16_t run_state_extended_flags;

extern uint16_t overrev_cycle_decay;
extern uint16_t overrev_spark_limit;
extern uint16_t init_overrev_spark_limit;
extern uint16_t overrev_spark_limit_dec_step;
extern uint16_t oneshot_crank_event_flags;

extern const void *const flash_revolution_limit_rpm_axis;
extern const void *const flash_revolution_limit_load_axis;
extern const void *const flash_post_fuel_cut_enrichment_launch_3dmap8;
extern const void *const flash_post_fuel_cut_enrichment_nlts_3dmap8;
extern const void *const flash_revolution_limit_spark_limit_launch_2dmap8;
extern const void *const flash_revolution_limit_spark_limit_nlts_2dmap8;
extern const void *const flash_revolution_limit_spark_regeneration_launch_2dmap8;
extern const void *const flash_revolution_limit_spark_regeneration_nlts_2dmap8;

#define MAX(x,y) (x < y ? y : x)


void update_revolution_limit()
{
	if (age_x1_ignition < 20) {
		overrev_cycle_decay = 0;
		overrev_spark_limit = 0;
		init_overrev_spark_limit = 0;
		overrev_spark_limit_dec_step = 255;
	} else {
		temp_axis_src = engine_rpm;
		calc_axis(&flash_revolution_limit_rpm_axis);
		init_overrev_spark_limit = s_mul16(flash_revolution_limit_spark_decay_cycles_per_tick[vehicle_movement_decay ? 1 : 0],
			 map8u16(vehicle_movement_decay
				? &flash_revolution_limit_spark_limit_nlts_2dmap8
				: &flash_revolution_limit_spark_limit_launch_2dmap8));
		overrev_spark_limit_dec_step = map8u16(vehicle_movement_decay
			? &flash_revolution_limit_spark_regeneration_nlts_2dmap8
			: &flash_revolution_limit_spark_regeneration_launch_2dmap8);
	}

	uint_fast16_t l_base_limit = sensor_faults & 0x08 ? flash_maf_fault_revolution_period_limit : flash_revolution_period_limit;
	if (!vehicle_movement_decay && IS_CLUTCH_DEPRESSED && flash_simple_standing_revolution_limit_enabled) {
		revolution_limit = MAX(flash_launch_control_revolution_limit, l_base_limit);
		return;
	}
#ifdef NLTS_MODULE_ENABLED
	if ((nlts_state == NLTS_STATE_ON) && (nlts_flags & NLTS_FLAGS_FUEL_CUT)) {
		uint_fast16_t l_nlts_limit = s16_divu32_16(1920000, nlts_target_rpm);
		revolution_limit = MAX(l_nlts_limit, l_base_limit);
		return;
	}
#endif

	revolution_limit = l_base_limit;
}

void update_run_state_extended_flags_overrev()
{
#ifdef REVLIMIT_FUELCUT_DISABLED
	if (shaft_period1_copy_dline0 < (sensor_faults & 0x08 ? flash_maf_fault_revolution_period_limit : flash_revolution_period_limit)) {
		run_state_extended_flags |= 0x20;
	} else {
		run_state_extended_flags &= ~0x20;
	}
	if (shaft_period1_copy_dline0 < revolution_limit) {
		overrev_cycle_decay = flash_init_overrev_cycle_decay[vehicle_movement_decay ? 1 : 0];
		overrev_spark_limit = init_overrev_spark_limit;
	} else {
		unsigned l_decay = overrev_cycle_decay;
		S_DEC(overrev_cycle_decay);
	}
#else
	if (shaft_period1_copy_dline0 < revolution_limit) {
		run_state_extended_flags |= 0x20;
		overrev_cycle_decay = flash_init_overrev_cycle_decay[vehicle_movement_decay ? 1 : 0];
		overrev_spark_limit = init_overrev_spark_limit;
	} else {
		run_state_extended_flags &= ~0x20;
		unsigned l_decay = overrev_cycle_decay;
		S_DEC(overrev_cycle_decay);
	}
#endif
}

uint16_t new_test_substitute_spark_advance_int(uint16_t p0)
{
	if (!overrev_cycle_decay) {
		overrev_spark_limit = s_sub16(overrev_spark_limit, overrev_spark_limit_dec_step);
	}
	uint_fast16_t limit = s_divu16(overrev_spark_limit, flash_revolution_limit_spark_decay_cycles_per_tick[vehicle_movement_decay ? 1 : 0]);
	if (p0 < limit) {
		return limit;
	}
	if (p0 > limit + 10) {
		overrev_spark_limit = 0;
	}
	return p0;
}

#if defined(ARCH_M32R)
void kill_spark()
{
	if (overrev_cycle_decay > s_sub16(flash_init_overrev_cycle_decay[vehicle_movement_decay ? 1 : 0], flash_overrev_kill_spark_cycles[vehicle_movement_decay ? 1 : 0])) {
		oneshot_crank_event_flags |= 0x1000;
	}
}
#elif defined(ARCH_SH2)
uint_fast16_t get_coil_dwell_max_substituting_s_scale_base128(uint_fast16_t p_shaft_period, uint_fast16_t p_dwell_max_ratio)
{
	//if (
}
#else
#error "Unknown ARCH_"
#endif

void new_tacho_reset()
{
	kill_spark();
	tacho_reset();
}

#ifdef REVLIMIT_FUELCUT_DISABLED
#warning "Revolution limit fuel cut disabled - disabling enrichment"
#elif defined(OVERREV_FUEL_ENRICHMENT_DISABLED)
#warning "disabled fuel enrichment - disabling enrichment"
#else


void update_post_fuel_cut_enrichment()
{
	extern uint16_t post_fuel_cut_enrichment;
	if (!overrev_spark_limit) {
		post_fuel_cut_enrichment = 128;
	} else {
		temp_axis_src = engine_rpm;
		calc_axis(&flash_revolution_limit_rpm_axis);
		temp_axis_src = map_engine_load;
		calc_axis(&flash_revolution_limit_load_axis);
		post_fuel_cut_enrichment = s_add16(128, map8u16(vehicle_movement_decay
			? &flash_post_fuel_cut_enrichment_nlts_3dmap8
			: &flash_post_fuel_cut_enrichment_launch_3dmap8));
	}
}

#endif
