#include <stdint.h>
#include <fmath.h>
#include <update_flags.h>
#include <defs.h>

#include <can.h>
#include <basic_ages_and_decays.h>
#include <torque_request_flags.h>
#include "gear_detector_data.h"
#include "asc_to_dash_rx.h"
#include "colt_mt_cvt_dash_control_data.h"
#include "engine_rpm_hires.h"

extern uint16_t dash_flash_runner;
extern uint8_t cvt_dash_data0;
extern uint8_t cvt_dash_data1;
extern uint8_t shift_light_pattern;
extern uint8_t asc_change_lamp;

extern uint16_t new_mode_idx;
extern uint16_t decays_x1_alt_mode_change_cel_flash_timer;
extern const uint16_t flash_alt_mode_change_cel_flash_time;
extern const uint16_t flash_alt_mode_change_cel_flash_time_slice;

static void update_dash_flash_runner()
{
	if (update_flags_main & UPDATE_FLAGS_10HZ) {
		dash_flash_runner = (dash_flash_runner + 1) % DASH_FLASH_MAX_SLICE_COUNT;
	}
}

static unsigned is_shift_light_needed()
{
	unsigned i;
	for (i = 0; i < SHIFT_LIGHT_STAGE_COUNT; ++i) {
		if (engine_rpm_hires < flash_shift_light_rpm_thresholds[i])
			break;
	}
	if (!i) {
		shift_light_pattern = 0;
		return 0;
	} else {
		shift_light_pattern = flash_shift_light_flash_patterns[i - 1][dash_flash_runner];
		return 1;
	}
}

extern const uint16_t flash_asc_lamp_startup_time;

static void  update_asc_off_enabled_decay()
{
	if (age_x1_ignition < flash_asc_lamp_startup_time) { //1 second on at ignition on to test the lamp, then start ceremony takes over
		asc_change_lamp = 1;
	} else if (asc_off_prev && !asc_off) {
		asc_change_lamp = 10;//1 second on if asc turned on
	} else if (!asc_off_prev && asc_off) {
		asc_change_lamp = 50;//5 seconds on if asc turned off
	} else if (update_flags_main & UPDATE_FLAGS_10HZ) {
		S_DEC(asc_change_lamp);
	}
}

const uint8_t flash_gear_to_cvt_dash_data[8] = {
	0x00, 0x20, 0x40, 0x60,
	0x80, 0xa0, 0xc0, 0xff
};

void update_cvt_dash_data()
{
	update_dash_flash_runner();
	update_asc_off_enabled_decay();

	if (asc_change_lamp) {
		cvt_dash_data0 = asc_off ? 0xe0 : 0x18;//D & Ds on
	} else if (is_shift_light_needed()) {
		cvt_dash_data0 = shift_light_pattern;
	} else {
		cvt_dash_data0 = 0;
	}

	if (decays_x1_alt_mode_change_cel_flash_timer) {
		uint_fast16_t l_timer = s_divu16(flash_alt_mode_change_cel_flash_time - decays_x1_alt_mode_change_cel_flash_timer,
			flash_alt_mode_change_cel_flash_time_slice);
		cvt_dash_data1 = flash_gear_to_cvt_dash_data[(l_timer % 2) ? (new_mode_idx + 1) : 0];
	} else {
		cvt_dash_data1 = flash_gear_to_cvt_dash_data[current_gear];

		if ((torque_request_flags & TORQUE_REQUEST_FLAGS_ASC_INTERVENTION) && flash_asc_flash_pattern[dash_flash_runner]) {
			cvt_dash_data1 = 0;
		}
	}
}


void can0_cvt_dash_update()
{
	can0_slot_tx_update(ENGINE_TO_CVT_DASH_TX_SLOT_INDEX, cvt_dash_data0, cvt_dash_data1, 0, 0, 0, 0, 0, 0);
}

void new_can0_40ms_tx()
{
	if (can0_flags & CAN0_FLAGS_TRANSMISSION_SUPPRESSED)
		return;

	can0_cvt_dash_update();
}
