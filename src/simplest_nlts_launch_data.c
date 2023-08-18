#include <stdint.h>
#include <maps_desc.h>
#include <maps_decl.h>

const uint16_t flash_launch_control_revolution_limit = 0x3da;
DECLARE_VALUE_DESC(flash_launch_control_revolution_limit,
	"Launch Control & NLTS",
	"Launch Control RPM Limit",
	"RPMLimit");

const uint16_t flash_nlts_revolution_limit = 0x3da;
DECLARE_VALUE_DESC(flash_nlts_revolution_limit,
	"Launch Control & NLTS",
	"NLTS RPM Limit",
	"RPMLimit");

const uint16_t flash_nlts_target_afr = 192;
DECLARE_VALUE_DESC(flash_nlts_target_afr,
	"Launch Control & NLTS",
	"NLTS AFR",
	"AFR16");

const uint16_t flash_nlts_cuts_holdoff_time = 4;

const uint16_t flash_nlts_app_thresholds[2] = { 250, 300 };
DECLARE_ARRAY_DESC(flash_nlts_app_thresholds,
	"Launch Control & NLTS",
	"APPS Threshold",
	"uint16",
	"<table name=\"X\" type=\"Static X Axis\" elements=\"2\">"
	"<data>Off</data>"
	"<data>On</data>"
	"</table>");

const uint16_t flash_init_nlts_active_decay = 120;
DECLARE_VALUE_DESC(flash_init_nlts_active_decay, "Launch Control & NLTS", "NLTS Active Time Limit", "Time");


#define FUEL_MAP_RPM_AXIS_SIZE 14
#define FUEL_MAP_LOAD_AXIS_SIZE 9

DECLARE_AXIS_DESC_EX(flash_fuel_map_rpm_axis, "Engine RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_fuel_map_load_axis, "Load", "Load");

DECLARE_3DMAP8_WITH_DESC(flash_launch_target_afr_3dmap8,
	FUEL_MAP_RPM_AXIS_SIZE,
	FUEL_MAP_LOAD_AXIS_SIZE,
	"Launch Control & NLTS",
	"Launch Control AFR",
	"AFR",
	"DXflash_fuel_map_load_axis",
	"DXflash_fuel_map_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.xsize = FUEL_MAP_RPM_AXIS_SIZE,
	.data = { 128, 192 }
};
