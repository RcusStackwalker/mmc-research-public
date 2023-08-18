#include <fmath.h>

extern uint16_t age_x1_ignition;
extern uint16_t engine_rpm_hires;

extern const uint16_t flash_start_ceremony_time;

extern const void *const flash_start_ceremony_time_axis;
extern const void *const flash_engine_rpm_start_ceremony_2dmap16;

extern uint16_t new_mode_idx;
extern uint16_t decays_x1_alt_mode_change_cel_flash_timer;
extern const uint16_t flash_mode_change_rpm_indication[];


void update_reset_engine_rpm_hires()
{
	if (decays_x1_alt_mode_change_cel_flash_timer)
	{
		engine_rpm_hires = flash_mode_change_rpm_indication[new_mode_idx];
	}
	if (age_x1_ignition < flash_start_ceremony_time)
	{
		temp_axis_src = age_x1_ignition;
		calc_axis(&flash_start_ceremony_time_axis);
		engine_rpm_hires = mapu16(&flash_engine_rpm_start_ceremony_2dmap16);
	}
	else
	{
		engine_rpm_hires = 0;
	}
}

void new_reset_engine_rpm_state()
{
	reset_engine_rpm_state();
	update_reset_engine_rpm_hires();
}
