#include "mode_selector_data.h"

#include <mode_selector.h>
#include <fmath.h>
#include <maps_decl.h>
#include <maps_desc.h>

const uint8_t flash_mode_change_patterns[4][16] = {
	{ 1, 1, 1, 1, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0, 0, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 0 },
	{ 1, 1, 0, 0, 1, 1, 0, 0 },
};

#define TIME_SLICE 10

const uint8_t flash_alt_disable_o2_feedback[MODE_COUNT] = { 0 };
const uint8_t flash_alt_mode_ac_switch = 0;
const uint8_t flash_reset_alt_mode_on_ignition_cycle = 1;
DECLARE_VALUE_DESC(flash_reset_alt_mode_on_ignition_cycle,
	"Mode Selector Settings",
	"Reset Mode On Ignition Cycle",
	"uint8");

const uint16_t flash_alt_mode_change_cel_flash_time = TIME_SLICE * 8;
#if 0
DECLARE_VALUE_DESC(flash_alt_mode_change_cel_flash_time,
	"Mode Selector Settings",,,,
	"CEL Indication - Time Slice",
	"uint16");
#endif
const uint16_t flash_alt_mode_change_cel_flash_time_slice = TIME_SLICE;
const uint16_t flash_m_depressed_threshold = 500;

const uint16_t flash_tps_alt_threshold = 150;
DECLARE_VALUE_DESC(flash_tps_alt_threshold,
	"Mode Selector Settings",
	"TPS Threshold For Alt Mode",
	"uint16");


const uint8_t flash_adc_ac_pressure_master = 0;
DECLARE_VALUE_DESC(flash_adc_ac_pressure_master,
	"Mode Selector Settings",
	"Use ADC 0F for mode switch",
	"uint8");
const uint16_t flash_init_mode_switch_delay = 25;
DECLARE_VALUE_DESC(flash_init_mode_switch_delay,
	"Mode Selector Settings",
	"Mode Switch Delay",
	"uint16");
const uint16_t flash_mode_selector_adc_ac_pressure_thresholds[2] = { 100, 150 };
DECLARE_VALUE_DESC(flash_mode_selector_adc_ac_pressure_thresholds,
	"Mode Selector Settings",
	"ADC0F (ADC AC Pressure Unused) Mode Selector Voltage Thresholds",
	"uint16");

