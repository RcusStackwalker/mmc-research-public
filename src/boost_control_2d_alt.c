#include <stdint.h>
#include <maps_decl.h>
#include <maps_desc.h>
#include <common_flags.h>
#include <basic_speed_variables.h>
#include <boost_control_variables.h>
#include <boost_control_2d_alt_data.h>

extern const void *const flash_boost_control_rpm_axis;
DECLARE_AXIS_DESC_EX(flash_boost_control_rpm_axis, "Engine RPM", "RPM");
extern const uint16_t flash_boost_control_gear_ratio_threshold;
extern const uint16_t flash_boostdown_target_load;
extern const uint16_t flash_boostdown_wgdc;

extern uint16_t egr_flags;
extern const uint16_t boostdown_ratio;

extern void update_boost_control_flags();
extern void update_wastegate_duty_error(uint16_t p_base_duty);
extern void wastegate_solenoid_duty_update(uint16_t p_base1_duty, uint16_t p_base2_duty);

void new_update_boost_target_load()
{
	calc_axis(&flash_boost_control_rpm_axis);
	uint16_t l_base_load = altmap8u16(flash_boost_control_gear_ratio_threshold < gear_ratio
		? flash_boost_target_load_low_gear_2dmultimap8
		: flash_boost_target_load_high_gear_2dmultimap8);

	if ((egr_flags & 0x02)
	&& (flash_boostdown_target_load < l_base_load)) {
		l_base_load = flash_boostdown_target_load + ps_scale_base256(l_base_load - flash_boostdown_target_load, boostdown_ratio);
	}
	boost_target_load = l_base_load;
}

uint_fast16_t new_calc_wastegate_duty()
{
	calc_axis(&flash_boost_control_rpm_axis);
	uint16_t l_base_duty = altmap8u16(flash_boost_control_gear_ratio_threshold < gear_ratio
		? &flash_base_wastegate_duty_low_gear_2dmultimap8
		: &flash_base_wastegate_duty_high_gear_2dmultimap8);

	if ((egr_flags & 0x02)
	&& (flash_boostdown_wgdc < l_base_duty)) {
		l_base_duty = flash_boostdown_wgdc + ps_scale_base256(l_base_duty - flash_boostdown_wgdc, boostdown_ratio);
	}
	wastegate_base_duty = l_base_duty;

	if (run_state_flags & 0x10) {
		return mut_actuator_tests0 & 0x40 ? 200 : 0;
	} else if (run_state_flags & 0x01) {
		return 0;
	}
	return l_base_duty;
}

void new_boost_control()
{
	update_boost_control_flags();
	new_update_boost_target_load();
	uint_fast16_t ret = new_calc_wastegate_duty();
	update_wastegate_duty_error(ret);
	wastegate_solenoid_duty_update(ret, 0);
}
