#include <fmath.h>
#include <maps_decl.h>
#include <maps_desc.h>
#include <defs.h>
#include "run_state_flags.h"

#include "boost_control_for_atmo_data.h"

extern uint16_t run_state_flags;
extern uint16_t engine_rpm;
extern uint16_t wastegate_base_duty;
extern uint16_t wastegate_base_duty_for_correction;
extern uint16_t iat;


#ifndef MMC_BOOST_CONTROL_H
#define MMC_BOOST_CONTROL_H

#define BCF_RPM_MIN_ON		0x01
#define BCF_RPM_MAX_ON		0x02
#define BCF_MASS_OVERFLOW	0x04
#define BCF_HIGH_OCTANE		0x08
#define BCF_OUT_OF_RPM_RANGE	0x10
#define BCF_BOOST_LIMP_OFF	0x20
#define BCF_COOLANT_OK		0x40
#define BCF_HIGH_GEAR		0x80

#define BCF_EGR_RELATED_COOLANT	0x8000

#endif /*MMC_BOOST_CONTROL_H*/

extern uint16_t boost_control_flags;
extern uint16_t wastegate_solenoid_duty;
extern uint16_t wastegate_duty_error;
extern uint16_t octane_level;
extern uint16_t coolant_temp_filtered;
extern uint16_t engine_rpm_8kmax;
extern uint16_t engine_rpm;
extern uint16_t sensor_faults;
extern uint16_t combustion_faults;
extern uint16_t gear_ratio;
extern uint16_t tps_main_rcord;
extern uint16_t decays_x2_wastegate_duty_error_update;
extern uint16_t wastegate_base_duty;
extern uint16_t map_engine_load8;
extern uint16_t map_engine_load;
extern uint16_t boost_target_load;
extern uint16_t tps_mapped_wastegate_duty_upward_correction_limit;
extern uint16_t iat_wastegate_duty_compensation;
extern uint16_t decays_x1_boost_cut;


void update_boost_control_flags()
{
	//HYSTERESIS_FLAG(boost_control_flags, BCF_MASS_OVERFLOW, maf_sensor_flow, flash_boost_control_map_fail_off, flash_boost_control_map_fail_on);
	HYSTERESIS_FLAG_CCONDA(boost_control_flags, BCF_HIGH_OCTANE, octane_level, flash_boost_control_octane_level_thresholds);
	HYSTERESIS_FLAG_CCONDA(boost_control_flags, BCF_COOLANT_OK, coolant_temp_filtered, flash_boost_control_coolant_temp_min_thresholds);
	//HYSTERESIS_FLAG(boost_control_flags, BCF_RPM_MAX_ON, engine_rpm_8kmax, flash_boost_control_rpm_max_off, flash_boost_control_rpm_max_on);
	HYSTERESIS_FLAG_CCONDA(boost_control_flags, BCF_RPM_MIN_ON, engine_rpm_8kmax, flash_boost_control_rpm_min_thresholds);
	if ((sensor_faults & 0x08)//maf fault
	|| (combustion_faults & 0x01)//knock present
	|| !(boost_control_flags & BCF_COOLANT_OK)
	|| !(boost_control_flags & BCF_HIGH_OCTANE)) {
		boost_control_flags |= BCF_BOOST_LIMP_OFF;
	} else {
		boost_control_flags &= ~BCF_BOOST_LIMP_OFF;
	}
/*
	if (!(boost_control_flags & BCF_BOOST_LIMP_OFF)
	&& ((boost_control_flags & BCF_RPM_MAX_ON)
	|| !(boost_control_flags & BCF_RPM_MIN_ON))) {
		boost_control_flags |= BCF_OUT_OF_RPM_RANGE;
	} else {
		boost_control_flags &= ~BCF_OUT_OF_RPM_RANGE;
	}
*/
	if (!(boost_control_flags & BCF_BOOST_LIMP_OFF)
	&& !(boost_control_flags & BCF_RPM_MIN_ON)) {
		boost_control_flags |= BCF_OUT_OF_RPM_RANGE;
	} else {
		boost_control_flags &= ~BCF_OUT_OF_RPM_RANGE;
	}

	if (gear_ratio < flash_boost_control_high_gear_ratio) {
		boost_control_flags |= BCF_HIGH_GEAR;
	} else {
		boost_control_flags &= ~BCF_HIGH_GEAR;
	}
}

#define BOOST_CONTROL_RPM_AXIS_SIZE 12
DECLARE_AXIS_WITH_DESC(flash_boost_control3d_rpm_axis,
	BOOST_CONTROL_RPM_AXIS_SIZE,
	"Engine RPM",
	"RPM") = {
	TEMP_AXIS_DST_X,
#ifdef ARCH_SH2
	.src = &engine_rpm,
#else
	.src = ENGINE_RPM_SDA,
#endif
	.size = BOOST_CONTROL_RPM_AXIS_SIZE,
	.data = { 0x180, 0x200, 0x280,
		0x300, 0x380, 0x400,
		0x480, 0x500, 0x580,
		0x600, 0x680, 0x700 }
};

#define BOOST_CONTROL_TPS_AXIS_SIZE 9
DECLARE_AXIS_WITH_DESC(flash_boost_control3d_tps_axis,
	BOOST_CONTROL_TPS_AXIS_SIZE,
	"TPS",
	"uint16") = {
	TEMP_AXIS_DST_Y,
#ifdef ARCH_SH2
	.src = &tps_main_rcord,
#else
	.src = TPS_MAIN_RCORD_SDA,
#endif
	.size = BOOST_CONTROL_TPS_AXIS_SIZE,
	.data = { 0x1a, 0x33, 0x4d,
		0x66, 0x80, 0x9a,
		0xb3, 0xcd, 0xe6 }
};

DECLARE_3DMAP8_WITH_DESC(flash_wastegate_base_duty_high_gear_3dmap8,
	BOOST_CONTROL_RPM_AXIS_SIZE,
	BOOST_CONTROL_TPS_AXIS_SIZE,
	"Boost Control",
	"Wastegate Base Duty - High Gear",
	"WGDuty",
	"DDflash_boost_control3d_tps_axis",
	"DDflash_boost_control3d_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.offset = 0,
	.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,
	.data = { },
};

DECLARE_3DMAP8_WITH_DESC(flash_wastegate_base_duty_low_gear_3dmap8,
	BOOST_CONTROL_RPM_AXIS_SIZE,
	BOOST_CONTROL_TPS_AXIS_SIZE,
	"Boost Control",
	"Wastegate Base Duty - Low Gear",
	"WGDuty",
	"DDflash_boost_control3d_tps_axis",
	"DDflash_boost_control3d_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.offset = 0,
	.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,
	.data = { },
};

DECLARE_3DMAP8_WITH_DESC(flash_boost_target_load_high_gear_3dmap8,
	BOOST_CONTROL_RPM_AXIS_SIZE,
	BOOST_CONTROL_TPS_AXIS_SIZE,
	"Boost Control",
	"Target Load - High Gear",
	"Load8",
	"DDflash_boost_control3d_tps_axis",
	"DDflash_boost_control3d_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.offset = 0,
	.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,
	.data = { },
};

DECLARE_3DMAP8_WITH_DESC(flash_boost_target_load_low_gear_3dmap8,
	BOOST_CONTROL_RPM_AXIS_SIZE,
	BOOST_CONTROL_TPS_AXIS_SIZE,
	"Boost Control",
	"Target Load - Low Gear",
	"Load8",
	"DDflash_boost_control3d_tps_axis",
	"DDflash_boost_control3d_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.offset = 0,
	.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,
	.data = { },
};


uint32_t calc_wastegate_duty()
{
	calc_axis(&flash_boost_control3d_rpm_axis);
	calc_axis(&flash_boost_control3d_tps_axis);

	uint32_t ret = boost_control_flags & BCF_HIGH_GEAR ? map8u16(&flash_wastegate_base_duty_high_gear_3dmap8) : map8u16(&flash_wastegate_base_duty_low_gear_3dmap8);
	//wastegate_base_duty = ret;//diagnostic purpose only


	if (run_state_flags & RUN_STATE_FLAGS_STALL) {
		ret = 0;
	} else {
		if (run_state_flags & RUN_STATE_FLAGS_CRANKING)
			return 0;
	} return ret;
}

#define BOOST_CONTROL_LOAD_ERROR_AXIS_SIZE 17

DECLARE_AXIS_WITH_DESC(flash_boost_control_load_error_axis,
	BOOST_CONTROL_LOAD_ERROR_AXIS_SIZE,
	"Load Error",
	"uint16") = {
	TEMP_AXIS_SRC_XDST,
	.size = 17,
	.data = {
		0,
		0x10, 0x20,
		0x30, 0x40,
		0x50, 0x60,
		0x70, 0x80,
		0x90, 0xa0,
		0xb0, 0xc0,
		0xd0, 0xe0,
		0xf0, 0xff
	}
};

DECLARE_2DMAP8_WITH_DESC(flash_wastegate_duty_vs_load_error_correction_2dmap8,
	BOOST_CONTROL_LOAD_ERROR_AXIS_SIZE,
	"Boost Control",
	"Integral WGDC Correction",
	"OffsetWGDC",
	"DDflash_boost_control_load_error_axis") = {
	TEMP_2DMAP_SRC,
	.offset = 0,
	.data = { 
		0x8a, 0x8a, 0x8a, 0x8a,
		0x8a, 0x84, 0x82, 0x81,
		0x80, 0x7f, 0x7e, 0x7c,
		0x76, 0x71, 0x6c, 0x6c,
		0x6c 
	}
};

DECLARE_2DMAP8_WITH_DESC(flash_wastegate_correction_vs_tps_limit_2dmap8,
	BOOST_CONTROL_TPS_AXIS_SIZE,
	"Boost Control",
	"Integral WGDC Correction Limit vs TPS",
	"OffsetWGDC",
	"DDflash_boost_control3d_tps_axis") = {
	TEMP_2DMAPY_SRC,
	.offset = 0,
	.data = { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x94, 0xa8, 0xa8 }
};

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
	"Boost Control",
	"Base WGDC vs IAT Correction",
	"OffsetWGDC",
	"DDflash_boost_control_iat_axis") = {
	TEMP_2DMAP_SRC,
	.data = { 0x1c, 0x4e, 0x6c, 0x80, 0x8a, 0x8a, 0x8a }
};


const uint16_t flash_wastegate_duty_error_max_downward_correction = 0;

void update_wastegate_duty_error(uint32_t base_duty)
{
	uint_fast16_t l_duty_error = wastegate_duty_error;

	if ((run_state_flags & RUN_STATE_FLAGS_NOT_RUNNING)
	|| (boost_control_flags & BCF_BOOST_LIMP_OFF)) {
		l_duty_error = 128;
		decays_x2_wastegate_duty_error_update = flash_init_wastegate_duty_error_update_decay;
	} else if (boost_control_flags & BCF_OUT_OF_RPM_RANGE) {//out of range
		decays_x2_wastegate_duty_error_update = flash_init_wastegate_duty_error_update_decay;
	} else if (!decays_x2_wastegate_duty_error_update) {


		decays_x2_wastegate_duty_error_update = flash_init_wastegate_duty_error_update_decay;

#ifdef MAP_ATMO_SENSOR
		temp_axis_src = s_16to8(s_sub16(map_engine_load8 + 32, boost_target_load + flash_boost_control_load_error_axis_offset) * 4);
#else
		temp_axis_src = s_16to8(s_sub16(map_engine_load / 4 + 32, boost_target_load + flash_boost_control_load_error_axis_offset) * 4);
#endif
		calc_axis(&flash_boost_control_load_error_axis);

		uint_fast16_t l_new_corr = s_sub16(l_duty_error + map8u16(&flash_wastegate_duty_vs_load_error_correction_2dmap8), 128);

		calc_axis(&flash_boost_control3d_tps_axis);

		uint_fast16_t l_tps_max_corr = map8u16(&flash_wastegate_correction_vs_tps_limit_2dmap8);//2d map
		//tps_mapped_wastegate_duty_upward_correction_limit = l_tps_max_corr;

		l_new_corr = mid16(l_new_corr, flash_wastegate_duty_error_max_downward_correction/*0*/, l_tps_max_corr);

		l_duty_error = s_sub16(mid16(s_sub16(base_duty + l_new_corr, 128), 0, 200), base_duty);
	}
	wastegate_duty_error = l_duty_error;
}


void update_boost_target_load()
{
	calc_axis(&flash_boost_control3d_rpm_axis);
	calc_axis(&flash_boost_control3d_tps_axis);

	boost_target_load = boost_control_flags & BCF_HIGH_GEAR ? map8u16(&flash_boost_target_load_high_gear_3dmap8) : map8u16(&flash_boost_target_load_low_gear_3dmap8);
}


void wastegate_solenoid_duty_update(uint32_t p_base_duty)
{
	uint_fast16_t l_duty;
	temp_axis_src = iat;
	calc_axis(&flash_boost_control_iat_axis);
	uint_fast16_t l_iat_comp = map8u16(&flash_wastegate_duty_compensation_vs_iat_2dmap8);
	//iat_wastegate_duty_compensation = l_iat_comp;
	if (!(boost_control_flags & (BCF_OUT_OF_RPM_RANGE | BCF_BOOST_LIMP_OFF))) {
		l_duty = s_sub16(s_sub16(l_iat_comp + p_base_duty, 128) + wastegate_duty_error, 128);
	} else if (run_state_flags & 0x11) {
		l_duty = p_base_duty;
	} else if (!decays_x1_boost_cut) {
		decays_x1_boost_cut = flash_init_boost_cut_decay;

		if (boost_control_flags & BCF_BOOST_LIMP_OFF) {//boost not desired
			l_duty = s_sub16(wastegate_solenoid_duty, 34);
		} else {
			l_duty = s_add16(wastegate_solenoid_duty, 34);
		}
	} else {
		l_duty = wastegate_solenoid_duty;
	}
#if !defined(WASTEGATE_SOLENOID_DUTY_MAX)
#define WASTEGATE_SOLENOID_DUTY_MAX 128
#endif

#if (WASTEGATE_SOLENOID_DUTY_MAX == 200)
	wastegate_solenoid_duty = mid16(l_duty, 0, 128);
#else
	wastegate_solenoid_duty = mid16(ps_mul_divu16(l_duty, WASTEGATE_SOLENOID_DUTY_MAX, 200), 0, WASTEGATE_SOLENOID_DUTY_MAX);
#endif
}

void boost_control()
{
	update_boost_control_flags();
	update_boost_target_load();
	uint_fast16_t duty = calc_wastegate_duty();
	update_wastegate_duty_error(duty);
	wastegate_solenoid_duty_update(duty);
}


