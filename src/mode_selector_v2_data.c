#include "mode_selector_data.h"

#include <mode_selector.h>
#include <fmath.h>
#include <maps_decl.h>
#include <maps_desc.h>
#include <engine_rpm_hires.h>

const uint8_t flash_mode_change_patterns[4][16] = {
	{ 1, 1, 1, 1, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0, 0, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 0 },
	{ 1, 1, 0, 0, 1, 1, 0, 0 },
};

#define TIME_SLICE 10

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

const uint16_t flash_tps_alt_threshold = 150;
DECLARE_VALUE_DESC(flash_tps_alt_threshold,
	"Mode Selector Settings",
	"TPS Threshold For Alt Mode",
	"uint16");


const uint16_t flash_init_mode_switch_delay = 25;
DECLARE_VALUE_DESC(flash_init_mode_switch_delay,
	"Mode Selector Settings",
	"Mode Switch Delay",
	"uint16");

const uint16_t flash_mode_change_rpm_indication[2] =  {
	RPM_TO_HIRESTICKS(2500),
	RPM_TO_HIRESTICKS(5000),
};
DECLARE_ARRAY_DESC(flash_mode_change_rpm_indication,
	"Mode Selector Settings",
	"Mode Change Tachometer Position",
	"RPMhires",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"2\">\n"
	"<data>Main</data>\n"
	"<data>Alt</data>\n"
	"</table>");
