#include <stdint.h>
#include <fmath.h>
#include <maps_decl.h>
#include <maps_desc.h>

extern uint16_t engine_rpm;
extern uint8_t current_gear;
extern uint16_t tps_target;
extern uint16_t tps_target_correction;
extern uint16_t boost_target_load;
extern uint16_t run_state_flags;
extern uint16_t mut_actuator_tests0;
extern uint16_t wastegate_base_duty;
extern uint16_t wastegate_base_duty_for_correction;
extern uint16_t iat;

extern const void *const flash_boost_control_rpm_axis;
extern const void *const flash_boost_control_tps_axis;

#define GEAR_AXIS_SIZE 6

DECLARE_AXIS_WITH_DESC(flash_boost_control_gear_axis,
	GEAR_AXIS_SIZE,
	"Gear",
	"uint16") = {
	TEMP_AXIS_SRC_YDST,
	.size = GEAR_AXIS_SIZE,
	.data = { 0, 1, 2, 3, 4, 5 }
};

#define BOOST_CONTROL_RPM_AXIS_SIZE 18
#define BOOST_CONTROL_TPS_AXIS_SIZE 9

DECLARE_AXIS_DESC_EX(flash_boost_control_rpm_axis, "Engine RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_boost_control_tps_axis, "Throttle", "Throttle_Main - Stored Minimum Throttle %");

#define DECLARE_BOOST_TARGET_LOAD_MAP(symbol, username)				\
	DECLARE_3DMAP8_WITH_DESC(symbol,					\
		BOOST_CONTROL_RPM_AXIS_SIZE,					\
		GEAR_AXIS_SIZE,						\
		"MT Rcus Moded Boost",						\
		username,							\
		"Load8",							\
		"DDflash_boost_control_gear_axis",				\
		"DXflash_boost_control_rpm_axis") = {				\
		TEMP_3DMAP_SRC,							\
		.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,				\
		.data = { 80 }							\
	}

#define DECLARE_COEFFICIENT_MAP(symbol, username)				\
	DECLARE_3DMAP8_WITH_DESC(symbol,					\
		BOOST_CONTROL_RPM_AXIS_SIZE,					\
		BOOST_CONTROL_TPS_AXIS_SIZE,					\
		"MT Rcus Moded Boost",						\
		username,							\
		"Percent128",							\
		"DXflash_boost_control_tps_axis",				\
		"DXflash_boost_control_rpm_axis") = {				\
		TEMP_3DMAP_SRC,							\
		.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,				\
		.data = { 64, 128 }						\
	}

#define DECLARE_WGDC_MAP(symbol, username)					\
	DECLARE_3DMAP8_WITH_DESC(symbol,					\
		BOOST_CONTROL_RPM_AXIS_SIZE,					\
		GEAR_AXIS_SIZE,						\
		"MT Rcus Moded Boost",						\
		username,							\
		"WGDuty",							\
		"DDflash_boost_control_gear_axis",				\
		"DXflash_boost_control_rpm_axis") = {				\
		TEMP_3DMAP_SRC,							\
		.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,				\
		.data = { 100, 200 }						\
	}
	

DECLARE_BOOST_TARGET_LOAD_MAP(flash_boost_target_load_normal_3dmap8, "Target Load - Main");
DECLARE_BOOST_TARGET_LOAD_MAP(flash_boost_target_load_sport_3dmap8, "Target Load - Alt");
DECLARE_COEFFICIENT_MAP(flash_boost_target_load_coefficient_3dmap8, "RPM x TPS Target Load Correction");
DECLARE_COEFFICIENT_MAP(flash_wgdc_coefficient_3dmap8, "RPM x TPS Base WGDC Correction");
DECLARE_WGDC_MAP(flash_base_wgdc_normal_3dmap8, "Base Wastegate Duty - Main");
DECLARE_WGDC_MAP(flash_base_wgdc_sport_3dmap8, "Base Wastegate Duty - Alt");

#define BOOST_CONTROL_IAT_AXIS_SIZE 7

DECLARE_AXIS_WITH_DESC(flash_boost_control_iat_axis,
	BOOST_CONTROL_IAT_AXIS_SIZE,
	"IAT",
	"TempC") = {
	TEMP_AXIS_SRC_XDST,
	.size = BOOST_CONTROL_IAT_AXIS_SIZE,
	.data = { 0x08, 0x21, 0x31, 0x3f, 0x4e, 0x60, 0x7d }
};

DECLARE_2DMAP8_WITH_DESC(flash_wastegate_duty_compensation_vs_iat_2dmap8,
	BOOST_CONTROL_IAT_AXIS_SIZE,
	"MT Rcus Moded Boost",
	"Base WGDC vs IAT Correction",
	"OffsetWGDC",
	"DDflash_boost_control_iat_axis") = {
	TEMP_2DMAP_SRC,
	.data = { 0x1c, 0x4e, 0x6c, 0x80, 0x8a, 0x8a, 0x8a }
};

static const void *const flash_boost_target_loads[3] = {
	&flash_boost_target_load_normal_3dmap8,
	&flash_boost_target_load_sport_3dmap8,
};


void new_update_boost_target_load()
{
	uint_fast16_t l_load_base;
	uint_fast16_t l_load_coefficient;
	calc_axis(&flash_boost_control_rpm_axis);

	temp_axis_src = current_gear;
	calc_axis(&flash_boost_control_gear_axis);

	l_load_base = tephra_multimap8u16(flash_boost_target_loads);

	temp_axis_src = s_sub16(tps_target, tps_target_correction / 4);
	calc_axis(&flash_boost_control_tps_axis);

	l_load_coefficient = map8u16(&flash_boost_target_load_coefficient_3dmap8);

	boost_target_load = ps_scale_base128(l_load_base, l_load_coefficient);
}

static const void *const flash_base_wgdcs[2] = {
	&flash_base_wgdc_normal_3dmap8,
	&flash_base_wgdc_sport_3dmap8,
};


uint16_t new_calc_wastegate_reactive_duty()
{
	uint_fast16_t l_wgdc_base;
	uint_fast16_t l_wgdc_coefficient;
	uint_fast16_t l_wgdc_iat_correction;
	calc_axis(&flash_boost_control_rpm_axis);

	temp_axis_src = current_gear;
	calc_axis(&flash_boost_control_gear_axis);

	l_wgdc_base = tephra_multimap8u16(flash_base_wgdcs);

	temp_axis_src = s_sub16(tps_target, tps_target_correction / 4);
	calc_axis(&flash_boost_control_tps_axis);

	l_wgdc_coefficient = map8u16(&flash_wgdc_coefficient_3dmap8);

	temp_axis_src = iat;
	calc_axis(&flash_boost_control_iat_axis);


	wastegate_base_duty = s_sub16(ps_scale_base128(l_wgdc_base, l_wgdc_coefficient) + map8u16(&flash_wastegate_duty_compensation_vs_iat_2dmap8), 128);
	wastegate_base_duty_for_correction = wastegate_base_duty;


	if (run_state_flags & 0x10) {
		return mut_actuator_tests0 & 0x40 ? 200 : 0;
	} else if (run_state_flags & 0x01) {
		return 0;
	} else {
		return wastegate_base_duty;
	}
}
