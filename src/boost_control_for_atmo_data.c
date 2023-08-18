#include "boost_control_for_atmo_data.h"


const uint16_t flash_boost_control_octane_level_thresholds[2] = { 154, 192 };
const uint16_t flash_boost_control_rpm_min_thresholds[2] = { 61, 64 };
const uint16_t flash_boost_control_coolant_temp_min_thresholds[2] = { 65, 70 };//25 degrees
const uint16_t flash_init_wastegate_duty_error_update_decay = 8;
const uint16_t flash_boost_control_high_gear_ratio = 0x850;
const uint16_t flash_init_boost_cut_decay = 7;
const uint16_t flash_boost_control_load_error_axis_offset = 0;
