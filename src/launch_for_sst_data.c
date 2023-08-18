#include <stdint.h>
#include <fmath.h>
#include <maps_decl.h>
#include <maps_desc.h>

#define CATEGORY_NAME "Simple Launch for 0uch by Rcus"

#define FUEL_MAP_RPM_AXIS_SIZE 16
#define FUEL_MAP_LOAD_AXIS_SIZE 21

DECLARE_AXIS_DESC_EX(flash_fuel_map_rpm_axis, "Engine RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_fuel_map_load_axis, "Load", "Load");

DECLARE_3DMAP8_WITH_DESC(flash_launch_afr_lean_limit_3dmap8,
	FUEL_MAP_RPM_AXIS_SIZE,
	FUEL_MAP_LOAD_AXIS_SIZE,
	CATEGORY_NAME,
	"AFR Lean Limit",
	"AFR",
	"DXflash_fuel_map_load_axis",
	"DXflash_fuel_map_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.xsize = FUEL_MAP_RPM_AXIS_SIZE,
	.data = { 128, 192 }
};

DECLARE_3DMAP8_WITH_DESC(flash_launch_spark_advance_limit_3dmap8,
	FUEL_MAP_RPM_AXIS_SIZE,
	FUEL_MAP_LOAD_AXIS_SIZE,
	CATEGORY_NAME,
	"Spark Advance Limit",
	"Timing",
	"DXflash_fuel_map_load_axis",
	"DXflash_fuel_map_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.offset = 20,
	.xsize = FUEL_MAP_RPM_AXIS_SIZE,
	.data = { 0, 1 }
};

const uint16_t flash_launch_speed_threshold = 4 * 30;
DECLARE_VALUE_DESC(flash_launch_speed_threshold,
	CATEGORY_NAME,
	"Speed Threshold",
	"VehicleSpeedFreq");
